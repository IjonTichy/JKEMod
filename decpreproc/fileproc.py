#!/usr/bin/env python3

__all__ = ("FileProc", "processFile")

from . import lineproc


class FileProc(object):
    
    def __init__(self, lineprocs):
        self.lineprocs = lineprocs


    def process(self, string):
        lines = string.split("\n")
        ret = []

        for i, line in enumerate(lines):
            try:
                tmp = line
                
                for proc in self.lineprocs:
                    tmp = proc.processLines(tmp, i)
                
                    if tmp == lineproc.NOLINE:
                        raise lineproc.NoLineException
            
            except lineproc.NoLineException:
                continue
            else:
                ret.append(tmp)

        return "\n".join(ret)


def processFile(file, procs):
    string = open(file, "r").read()

    fileProc = FileProc(procs)
    ret = fileProc.process(string)

    return ret
