#!/usr/bin/env python3

__all__ = ("DefineProc",)

import re, os
from collections import namedtuple
from . import lineproc
from pathwalker import pathwalker

CONSTNAME   = "[a-zA-Z_][a-zA-Z0-9_]+"
RE_END      = "(?:\s+//.+?)?"

ifdefItem   = namedtuple("ifdefItem", "type value")

class DefineProc(lineproc.LineProc):
    DEFINERE = re.compile(r"^#define\s+(" + CONSTNAME + r")\s+(.+?)" + RE_END + "$")
    IFDEFRE  = re.compile(r"^#if(n?)def\s+(" + CONSTNAME + r")" + RE_END + "$")
    ENDIFRE  = re.compile(r"^#endif" + RE_END + "$")
    CONSTRE  = re.compile(r"(\\?\$)(?:(" + CONSTNAME + r")|\{(" + CONSTNAME + r")\})")
    
    def __init__(self):
        super().__init__()
        self.defRE      = self.__class__.DEFINERE
        self.conRE      = self.__class__.CONSTRE
        self.ifdefRE    = self.__class__.IFDEFRE
        self.endifRE    = self.__class__.ENDIFRE
        self.consts     = {}
        self.defStack   = []

    def process(self, line, lineno):
        myProcs = [self.processIfDef, self.processEndIf, self.processCheckIf, self.processDefine, self.processNormal]
        
        for proc in myProcs:
            ret = proc(line, lineno)
            
            if ret and ret != line:
                return ret

        return line

    def processDefine(self, line, lineno):
        match = self.defRE.match(line)
        
        if not match:
            return
        
        newConst, newRepl = match.group(1), match.group(2)

        if newConst not in self.consts:
            
            newRepl = self.processNormal(newRepl, 0)

            self.consts[newConst] = newRepl
            return "//" + line
        else:
            raise lineproc.LineProcError("{}:  \"{}\" defined more than once (line {})".format(self.__class__.__name__, newConst, lineno))


    def processNormal(self, line, lineno):

        match = self.conRE.search(line)
        
        if not match:
            return

        matches = list(self.conRE.finditer(line) )
        ret = self.conRE.split(line)[::1 + self.conRE.groups]
        
        for i, match in enumerate(matches):
            
            if match.group(2):  # matched $derp
                constName = match.group(2)
            else:               # matched ${derp}
                constName = match.group(3)


            if "\\" in match.group(1):
                if constName in self.consts:
                    ins = match.group(0)[1:]
                else:
                    ins = match.group(0)

            elif constName in self.consts:
                ins = self.consts[constName]
            
            else:
                ins = match.group(0)

            ret.insert((2*i) + 1, ins)

        return "".join(ret)
    
    def processIfDef(self, line, lineno):
        match = self.ifdefRE.match(line)
        
        if not match:
            return
        
        newIfDef = ifdefItem(not match.group(1), match.group(2)) 
        self.defStack.append(newIfDef)
        
        return "//" + line

    def processEndIf(self, line, lineno):
        match = self.endifRE.match(line)

        if not match:
            return

        if len(self.defStack) > 0:
            self.defStack.pop()
        else:
            raise lineproc.LineProcError("{}: unbalanced #if(n)def's and #endif's (line {})".format(self.__class__.__name__, lineno))
        
        return "//" + line

    def processCheckIf(self, line, lineno):
        
        for ifdef in self.defStack:
            
            if ifdef.type == True:
                success = ifdef.value in self.consts
            else:
                success = ifdef.value not in self.consts

            if not success:
                return "//" + line
    
    def processEnd(self):
