#!/usr/bin/env python3

__all__ = ("LineProcError", "LineProc")

class NOLINE(object): pass
class LineProcError(Exception): pass
class NoLineException(Exception): pass

class LineProc(object):
    
    def __init__(self):
        pass
    
    def processLines(self, lines, lineno):
        ret = []
        
        for line in lines.split("\n"):
            result = self.process(line, lineno)
            
            if result == NOLINE:
                return NOLINE
            
            ret.append(result)
        
        return "\n".join(ret)

    def process(self, line, lineno):
        return line

    def processEnd(self):
        pass
