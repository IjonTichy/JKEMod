#!/usr/bin/python3

import collections

class FileTree(object):
    """The tree object used by PathWalker."""

    def __init__(self, dir, files, dirs):

        self.dir   = dir
        self.files = files
        self.dirs  = dirs

    @property
    def dir(self):
        return self.__dir
    @dir.setter
    def dir(self, new):

        if not isinstance(new, str):
            raise ValueError("not a string type")

        self.__dir = new

    @property
    def files(self):
        return self.__files

    @files.setter
    def files(self, new):

        if not isinstance(new, collections.MutableSequence):
            raise ValueError("not a mutable sequence")

        self.__files = new

    @property
    def dirs(self):
        return self.__dirs

    @dirs.setter
    def dirs(self, new):

        if not isinstance(new, collections.MutableSequence):
            raise ValueError("not a mutable sequence")

        self.__dirs = new


    def flattenFiles(self, rel=0, repl="./"):
        return self.__flattenFiles(rel, self.dir, repl)

    def __flattenFiles(self, rel, baseDir, repl):
        ret = []

        if len(self.files) != 0:
            firstFile = self.files[0]

            if firstFile.startswith(baseDir) and bool(rel):
                ret = [i.replace(baseDir, repl, 1) for i in self.files]
            else:
                ret = self.files

        for d in self.dirs:
            ret += d.__flattenFiles(rel, baseDir, repl)

        return ret

    def flattenDirs(self):

        ret = []

        for d in self.dirs:
            ret.append(d.dir)

        for d in self.dirs:
            ret += d.flattenDirs()

        return ret


    def __repr__(self):
        return "{0}({1}, {2}, {3})".format(self.__class__.__name__,
                            repr(self.dir), repr(self.files), repr(self.dirs) )


    def __getitem__(self, key):

        if key in (0, "dir"):
            return self.dir

        elif key in (1, "files"):
            return self.files

        elif key in (2, "dirs"):
            return self.dirs

        else:
            raise ValueError("{0} not in {1}".format(key, self.__class__.__name__) )

    def __lt__(self, other):
        return self.dir < other.dir
