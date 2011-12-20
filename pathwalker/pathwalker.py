#!/usr/bin/python3

import os

from . import filetree

class NotDirError(Exception): pass


class PathWalker(object):
    """Walk paths."""

    def __init__(self, myDir):

        self.dir = myDir

    @property
    def dir(self):
        return self.__dir

    @dir.setter
    def dir(self, new):

        new = os.path.abspath(new)

        if not os.path.isdir(new):
            raise NotDirError()

        self.__dir = new

    def walk(self, fFilter=None, dFilter=None, abs=False, hidden=False):

        return self.__walk(self.dir, fFilter, dFilter, abs, hidden)

    def __walk(self, start, fFilter, dFilter, abs, hidden):


        fils = []
        dirs = []

        cDir = os.path.abspath(start) + "/"

        ret = filetree.FileTree(cDir, [], [])

        for i in os.listdir(cDir):

            if i.startswith(".") and not hidden:
                continue

            i = cDir + i

            if abs:
                j = i
            else:
                j = os.path.basename(i)

            if os.path.isdir(i):

                if dFilter is not None:

                    if dFilter(i):
                        dirs.append(self.__walk(i, fFilter, dFilter, abs, hidden) )
                else:
                    dirs.append(self.__walk(i, fFilter, dFilter, abs, hidden) )

            else:

                if fFilter is not None:

                    if fFilter(i):
                        fils.append(j)
                else:
                    fils.append(j)

        ret.files = sorted(fils)
        ret.dirs  = sorted(dirs)

        return ret


