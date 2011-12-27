#!/usr/bin/env python3

__all__ = ("DefineProc",)

import re, os
from . import lineproc
from pathwalker import pathwalker

CONSTNAME = "[a-zA-Z_][a-zA-Z0-9_]+"

class DefineProc(lineproc.LineProc):
    DEFINERE = re.compile(r"^#define\s+(" + CONSTNAME + r")\s+(.+?)$")
    CONSTRE  = re.compile(r"(\\?\$)(?:(" + CONSTNAME + r")|\{(" + CONSTNAME + r")\})")
    
    def __init__(self):
        super().__init__()
        self.defRE      = self.__class__.DEFINERE
        self.conRE      = self.__class__.CONSTRE
        self.consts     = {}

    def process(self, line, lineno):
        ret = self.processDefine(line, lineno)
        
        if ret != line:
            return ret
        else:
            return self.processNormal(line, lineno)
    
    def processDefine(self, line, lineno):
        match = self.defRE.match(line)

        if not match:
            return line
        
        newConst, newRepl = match.group(1), match.group(2)

        if newConst not in self.consts:
            self.consts[newConst] = newRepl
            return "//" + line
        else:
            raise lineproc.LineProcError("{}:  \"{}\" defined more than once (line {})".format(self.__class__.__name__, newConst, lineno))

    def processNormal(self, line, lineno):
        
        match = self.conRE.search(line)
        
        if not match:
            return line
        
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
