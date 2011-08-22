#!/usr/bin/python3

import sys
import os
import shutil
import collections

from pad import pad
from pathwalker.classes import pathwalker

PROGNAME = os.path.basename(sys.argv[0])
USAGE = "usage: {0} <oldnames> <newnames> <dir>".format(PROGNAME)

checkStrs = ["\"{0}\""]
checkStrs2 = ["actor {0}:", "model {0}", "actor {0} :"]

def isText(x):
    return x.endswith(".txt")

def main(onFile, nnFile, wDir):

    bDir = wDir + "~"

    if os.path.exists(bDir):
        if input("delete {0} (y/n)? ".format(bDir) ).lower() in ["1", "y"]:
            shutil.rmtree(bDir)
        else:
            errorAndExit("{0} already exists".format(bDir) )

    shutil.copytree(wDir, bDir)

    on = open(onFile)
    nn = open(nnFile)

    oldNames = []
    newNames = []
    oldNamesL = []
    newNamesL = []

    fileDict = collections.defaultdict(lambda: [False, ""])

    try:
        walker = pathwalker.PathWalker(wDir)
    except pathwalker.NotDirError:
        usageAndExit("directory doesn't exist")

    for old, new in zip(on, nn):

        if old:
            oldNames.append(old.rstrip("\n").strip('"').lower())
            oldNamesL.append(old.rstrip("\n").strip('"').lower())

        if new:
            newNames.append(new.rstrip("\n").strip('"'))
            newNamesL.append(new.rstrip("\n").strip('"').lower())

    if len(oldNames) != len(newNames):
        raise ValueError("old name count and new name count MUST be the same")

    nameTrans  = dict(zip(oldNames,  newNames)  )
    nameTransL = dict(zip(oldNamesL, newNamesL) )

    for name in nameTrans:
        pName  = pad(name, padChar='"')
        pName2 = pad(nameTrans[name], padChar='"')
        print("{0:<20} -> {1}".format(pName, pName2) )

    txtFiles = walker.walk(isText, abs=True)

    txtFiles = txtFiles.flattenFiles()

    for txt in txtFiles:

        cFile = open(txt)

        for line in cFile:

            testLine = line.rstrip("\n").lower()
            line = line.rstrip("\n")

            for n in nameTransL:

                fName = "\"{0}\"".format(nameTrans[n])


                for s in checkStrs:

                    s2 = s.format(n)
                    s3 = s.format(nameTrans[n])
                    l = len(s2)

                    if s2 in testLine:

                        print(testLine)

                        p = testLine.find(s2)
                        line = line[:p] + s3 + line[p+l:]

                        print(line)
                        fileDict[txt][0] = True
                        break

                for s in checkStrs2:

                    s2 = s.format(n)
                    s3 = s.format(fName)
                    l = len(s2)

                    if s2 in testLine:

                        print(testLine)


                        p = testLine.find(s2)
                        line = line[:p] + s3 + line[p+l:]

                        print(line)
                        fileDict[txt][0] = True
                        break

            fileDict[txt][1] = "".join([fileDict[txt][1], line + "\n"])

    fileDict[txt][1] += "\n"

    for txt in sorted(fileDict):

        if fileDict[txt][0]:
            cFile = open(txt, "w")
            cFile.write(fileDict[txt][1])
            cFile.flush()
            cFile.close()







def usageAndExit(reason):
    print("{0}: {1}".format(PROGNAME, reason) )
    print(USAGE)
    sys.exit()

def errorAndExit(reason):
    print("ERROR: {1}".format(PROGNAME, reason) )
    sys.exit(1)


if __name__ == "__main__":

    if len(sys.argv) < 2:
        usageAndExit("no old name file")

    if len(sys.argv) < 3:
        usageAndExit("no new name file")

    if len(sys.argv) < 4:
        usageAndExit("no working directory")

    main(*sys.argv[1:4])
