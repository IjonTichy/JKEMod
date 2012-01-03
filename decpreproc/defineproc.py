#!/usr/bin/env python3

__all__ = ("DefineProc",)

import re, os
from collections import namedtuple
from . import lineproc
from pathwalker import pathwalker

CONSTNAME   = "[a-zA-Z_][a-zA-Z0-9_]+"
RE_END      = "(?:\s*(?://.+)?)?"

class ifdefItem(object):
    def __init__(self, type, value, flipped=False):
        self.type  = type
        self.value = value
        self.flipped = flipped

    def flip(self):
        self.type    = not self.type
        self.flipped = not self.flipped
        
        return self.flipped
    
    def __repr__(self):
        return "{}({})".format(self.__class__.__name__, ", ".join(str(x) for x in (self.type, self.value, self.flipped)))


class DefineProc(lineproc.LineProc):
    DEFINERE    = re.compile(r"^#define\s+(" + CONSTNAME + r")\s+(.+?)" + RE_END + "$")
    DEFINERE2   = re.compile(r"^#define\s+(" + CONSTNAME + r")" + RE_END + "$")
    IFDEFRE     = re.compile(r"^#if(n?)def\s+(" + CONSTNAME + r")" + RE_END + "$")
    ENDIFRE     = re.compile(r"^#endif" + RE_END + "$")
    ELSERE      = re.compile(r"^#else" + RE_END + "$")
    CONSTRE     = re.compile(r"(\\?\$)(?:(" + CONSTNAME + r")|\{(" + CONSTNAME + r")\})")
    
    def __init__(self):
        super().__init__()
        self.defRE      = self.__class__.DEFINERE
        self.defRE2     = self.__class__.DEFINERE2
        self.conRE      = self.__class__.CONSTRE
        self.ifdefRE    = self.__class__.IFDEFRE
        self.elseRE     = self.__class__.ELSERE
        self.endifRE    = self.__class__.ENDIFRE
        self.consts     = {}
        self.defStack   = []

    def process(self, line, lineno):
        myProcs = [self.processIfDef, self.processEndIf, self.processElse, self.processCheckIf, self.processDefine, self.processNormal]
        
        for proc in myProcs:
            ret = proc(line, lineno)
            
            if ret and ret != line:
                return ret

        return line

    def processDefine(self, line, lineno):
        
        for re in [self.defRE, self.defRE2]:
            match = re.match(line)
        
            if match:
                break
        else:
            return
        
        if re.groups == 1:
            newConst, newRepl = match.group(1), None
        else:
            newConst, newRepl = match.group(1), match.group(2)

        if newConst not in self.consts:
            
            if newRepl is not None:
                newRepl = self.processNormal(newRepl, 0)

            self.consts[newConst] = newRepl
            return lineproc.NOLINE
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
        
        print(newIfDef)

        return lineproc.NOLINE

    def processEndIf(self, line, lineno):
        match = self.endifRE.match(line)

        if not match:
            return

        if len(self.defStack) > 0:
            self.defStack.pop()
        else:
            raise lineproc.LineProcError("{}: unbalanced #if(n)def's and #endif's (line {})".format(self.__class__.__name__, lineno))
        
        return lineproc.NOLINE
    
    def processElse(self, line, lineno):
        match = self.elseRE.match(line)
        
        if not match:
            return
        
        lastDef = self.defStack[-1]

        if lastDef.flipped:
            raise lineproc.LineProcError("{}: multiple #else's for one #if(n)def (line {})".format(self.__class__.__name__, lineno))
        
        lastDef.flip()
        
        print(lastDef)
        return lineproc.NOLINE

    def processCheckIf(self, line, lineno):
        
        for ifdef in self.defStack:
            
            if ifdef.type == True:
                success = ifdef.value in self.consts
            else:
                success = ifdef.value not in self.consts

            if not success:
                return lineproc.NOLINE
    
    def processEnd(self):
        
        if len(self.defStack) > 0:
            raise lineproc.LineProcError("{}: unbalanced #if(n)def's and #endif's (EOF)".format(self.__class__.__name__))
