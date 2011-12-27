#!/usr/bin/env python3

__all__ = ("IncludeProc", "IncludeDirProc")

import re, os
from . import lineproc
from pathwalker import pathwalker

class IncludeProc(lineproc.LineProc):
    INCLUDERE = re.compile("^#include\s+\"(.+?)\"$")

    def __init__(self):
        super().__init__()
        self.incRE      = self.__class__.INCLUDERE 
        
    def process(self, line, lineno):
        match = self.incRE.match(line)

        if not match:
            return line
        
        wDir = match.group(1)
        
        if not os.path.isfile(wDir):
            raise lineproc.LineProcError("{}: \"{}\" is not a file (line {})".format(self.__class__.__name__, wDir, lineno) )

        fText = open(wDir, "r").read()

        if not fText.endswith("\n"):
            fText += "\n"

        return fText



class IncludeDirProc(lineproc.LineProc):
    INCLUDERE = re.compile("^#include\s+{(.+?)}$")
    WALKFUNC  = lambda x: x.lower().endswith(".dec")

    def __init__(self):
        super().__init__()
        self.incRE      = self.__class__.INCLUDERE 
        self.walkFunc   = self.__class__.WALKFUNC
        
    def process(self, line, lineno):
        match = self.incRE.match(line)

        if not match:
            return line
        
        wDir = match.group(1)
        
        if not wDir.endswith("/"):
            wDir += "/"

        if not os.path.isdir(wDir):
            raise lineproc.LineProcError("{}: \"{}\" is not a directory (line {})".format(self.__class__.__name__, wDir, lineno) )

        walker = pathwalker.PathWalker(wDir)

        walked = walker.walk(fFilter=self.walkFunc, abs=True)
        wFiles = walked.flattenFiles(rel=True, repl=wDir)

        ret = []

        for file in wFiles:
            ret.append("#include \"{}\"".format(file))
        
        return "\n".join(ret)
