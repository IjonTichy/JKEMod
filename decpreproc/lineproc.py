#!/usr/bin/env python3

__all__ = ("LineProcError", "LineProc")

class LineProcError(Exception): pass

class LineProc(object):
    
    def __init__(self):
        pass
    
    def processLines(self, lines, lineno):
        ret = []

        for line in lines.split("\n"):
            ret.append(self.process(line, lineno))
        
        return "\n".join(ret)

    def process(self, line, lineno):
        return line

    def processEnd(self):
        pass
