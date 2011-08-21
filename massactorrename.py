#!/usr/bin/python3

import sys
import os
import collections

from pathwalker.classes import pathwalker

PROGNAME = os.path.basename(sys.argv[0])
USAGE = "usage: {0} <oldnames> <newnames> <dir>".format(PROGNAME)

checkStrs = ["\"{0}\""]
checkStrs2 = ["actor {0}:", "model {0}", "actor {0} :"]

def isText(x):
    return x.endswith(".txt")

def main(onFile, nnFile, wDir):

    on = open(onFile)
    nn = open(nnFile)

    oldNames = []
    newNames = []
    oldNamesL = []
    newNamesL = []

    fileDict = collections.defaultdict(str)

    try:
        walker = pathwalker.PathWalker(wDir)
    except pathwalker.NotDirError:
        usageAndExit("directory doesn't exist")

    for old, new in zip(on, nn):

        if old:
            oldNames.append(old[:-1].strip('"').lower())
            oldNamesL.append(old[:-1].strip('"').lower())

        if new:
            newNames.append(new[:-1].strip('"'))
            newNamesL.append(new[:-1].strip('"').lower())

    if len(oldNames) != len(newNames):
        raise ValueError("old name count and new name count MUST be the same")

    nameTrans  = dict(zip(oldNames,  newNames)  )
    nameTransL = dict(zip(oldNamesL, newNamesL) )

    txtFiles = walker.walk(isText, abs=True)

    txtFiles = txtFiles.flattenFiles()

    for txt in txtFiles:

        cFile = open(txt)

        for line in cFile:

            testLine = line[:-1].lower()
            line = line[:-1]

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
                        break

            fileDict[txt] = "\n".join([fileDict[txt], line])

    for txt in sorted(fileDict):
        cFile = open(txt, "w")
        cFile.write(fileDict[txt])
        cFile.close()







def usageAndExit(reason):
    print("{0}: {1}".format(PROGNAME, reason) )
    print(USAGE)
    sys.exit()


if __name__ == "__main__":

    if len(sys.argv) < 2:
        usageAndExit("no old name file")

    if len(sys.argv) < 3:
        usageAndExit("no new name file")

    if len(sys.argv) < 4:
        usageAndExit("no working directory")

    main(*sys.argv[1:4])
