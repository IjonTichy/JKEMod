#!/usr/bin/env python3

import sys, os, shutil, zipfile, tempfile
from subprocess import Popen, PIPE

import which
from pathwalker import pathwalker
from decpreproc import *

LINEPROCS   = [defineproc.DefineProc(), includeproc.IncludeDirProc()]

NUMBERS     = "0123456789"

MAKE_ACT    = "make"
TEST_ACT    = "test"
PACKAGE_ACT = "package"
HELP_ACT    = "help"

USAGE = "usage: {} [{}] <args>".format(os.path.basename(sys.argv[0]), "|".join([MAKE_ACT, TEST_ACT, PACKAGE_ACT, HELP_ACT]))

USAGE_FULL = """
- make: Builds a PK3 from the files in the pk3/ directory, with the name being
  that of the current directory.

- test [port=skulltag] <args>: Runs 'make', and then runs 'port' with the PK3,
  along with any arguments you choose.

- package [version]: Runs 'make', with 'version' at the end of the name, copies
  it to a ZIP with the same name, and copies the PK3 to "$HOME/.zdoom" if the
  directory exists.

- help: Prints this.

Examples:
  # PWD is /home/derp/derpPK3
  packagepk3.py make  # derpPK3.pk3
  packagepk3.py test skulltag -file nuts
  packagepk3.py package 1_5  # derpPK3_1_5.pk3, derpPK3_1_5.zip,
                             # /home/derp/.zdoom/derpPK3_1_5.pk3
  # PWD is /home/derp/derpWAD
  packagepk3.py package 1_5  # derpWAD1_5.pk3, derpWAD1_5.zip,
                             # /home/derp/.zdoom/derpWAD1_5.pk3
"""

DECORATE_EXTS   = ("dec",)
ACS_EXTS        = ("c", "acs")
ACS_OBJ_EXTS    = ("o",)

ACC_ERROR   = "**** ERROR ****"

DEFAULT_ARGS = ["-warp 01"]

def warn(reason):
    print("warning:", reason, file=sys.stderr)


def errorExit(code = 1, reason = None):
    if reason:
        print("ERROR:", reason, file=sys.stderr)

    sys.exit(code)

def usageExit(code = 1, reason = None):
    if reason:
        print("error:", reason, file=sys.stderr)

    usage()
    sys.exit(code)

def usage():
    print(USAGE)

def usageFull():
    usage()
    print(USAGE_FULL)

NO_ARGS, NO_PK3, NO_ACC, NO_VERSION, ACC_FAIL, NO_BINARY = range(4, 10)

PK3NAME = os.path.basename(os.path.realpath("."))

WAD_DIR = os.environ["HOME"] + "/.zdoom"

if not os.path.isdir(WAD_DIR):
    warn("{} does not exist - no pk3 auto-installation will be done".format(WAD_DIR))
    WAD_DIR = None

zdoomExe = "zdoom" + (".exe" if sys.platform[:3] == "win" else "")
skulltagExe = "skulltag" + (".exe" if sys.platform[:3] == "win" else "")

if which.is_exe(zdoomExe):
    ZDOOM = os.path.realpath(zdoomExe)
else:
    ZDOOM = which.which(zdoomExe)

    if ZDOOM is None:
        warn("no zdoom in PATH or PWD")

if which.is_exe(skulltagExe):
    SKULLTAG = os.path.realpath(skulltagExe)
else:
    SKULLTAG = which.which(skulltagExe)

    if SKULLTAG is None:
        warn("no skulltag in PATH or PWD")


if which.is_exe("acc"):
    ACC = os.path.realpath("acc")
else:
    ACC = which.which("acc")

    if ACC is None:
        ACC_DIR = None
        errorExit(NO_ACC, "no acc in PATH or PWD")
    else:
        ACC_DIR = ACC.rpartition("/")[0]



def playPK3(pk3, binary=SKULLTAG, *args):

    if binary is None:
        errorExit(1, "no binary")

    pk3 = os.path.realpath(pk3)

    if not os.path.isfile(pk3):
        errorExit(NO_BINARY, "somehow, {} doesn't exist")

    if not args:
        args = DEFAULT_ARGS
    elif isinstance(args, str):
        args = [i for i in args.split(" ") if i]
    else:
        args = list(args)

    pk3Game = Popen([binary, "-file {}".format(pk3)] + args)
    pk3Game.wait()

    return 0


def compileACS(file):
    file2 = file
    file = os.path.realpath(file)

    if not os.path.isfile(file):
        errorExit(ACC_FAIL, "must provide name of actual file")

    newFile = file.rpartition(".")[:2] + ("o",)
    newFile = "".join(newFile)

    newFile2 = file2.rpartition(".")[:2] + ("o",)
    newFile2 = "".join(newFile2)

    accProc = Popen([ACC, "-i", ACC_DIR, file, newFile], stdout=PIPE, stderr=PIPE)

    accOut, accErr = (i.decode().split("\n") for i in accProc.communicate())

    if ACC_ERROR in accErr:
        reasonLines = accErr[accErr.index(ACC_ERROR)+1:]
        reason = "\n".join(reasonLines)

        raise RuntimeError(reason)

    return newFile2


def makePK3(aArgs):
    if not os.path.isdir("pk3"):
        errorExit(NO_PK3, "no pk3/ directory")

    pk3Walk = pathwalker.PathWalker('pk3')

    oldDir = os.getcwd()
    os.chdir("pk3")

    pk3Name     = "{}.pk3".format(PK3NAME)
    pk3Name2    = "../{}.pk3".format(PK3NAME)
    pk3Zip      = zipfile.ZipFile(pk3Name2, "w")
    pk3Files    = pk3Walk.walk(abs=1, fFilter=lambda x: not x.endswith("*.o")).flattenFiles(rel=1)
    pk3Total    = len(pk3Files)
    nLen        = 0

    print("making... ", end="")

    try:
        for i, file in enumerate(pk3Files):
            j = i + 1

            oLen = nLen
            perc = "{}%".format(int( ( (j / pk3Total) * 100) ) )
            nLen = len(perc)

            print(("\b"*oLen) + perc, end="")

            sys.stdout.flush()
            
            fPath, fName = os.path.realpath(file).rsplit("/", 1)
            fExt = file.rsplit(".", 1)[1]

            zipFName = file.lstrip("./")

            if fExt in DECORATE_EXTS:  # DECORATE
                prevDir = os.getcwd()

                os.chdir(fPath)

                dTmpName = tempfile.mkstemp(prefix="dec")[1]
                dTmp     = open(dTmpName, "w")
                
                dTmp.write(fileproc.processFile(fName, LINEPROCS))
                dTmp.close()
                
                os.chdir(prevDir)

                pk3Zip.write(dTmpName, zipFName)
            
            elif fExt in ACS_OBJ_EXTS:  # ACS .o - will be handled later
                pass

            elif fExt in ACS_EXTS:  # ACS
                objFile = compileACS(file)
                pk3Zip.write(objFile, objFile.lstrip("./"))
                pk3Zip.write(file, zipFName)
            
            else:
                pk3Zip.write(file, zipFName)

    except KeyboardInterrupt:
        print( ("\b" * (nLen + 2)) + "aborted.")
        os.remove(pk3Name2)
        sys.exit(127)

    except RuntimeError as exc:
        print()
        errorExit(1, "\n" + exc.args[0])

    pk3Zip.close()
    os.chdir(oldDir)
    print( ("\b" * nLen) + "done.")

    return pk3Name

def testPK3(aArgs):
    pk3 = makePK3([])
    playPK3(pk3, *aArgs)


def packagePK3(aArgs):

    if len(aArgs) < 1:
        usageExit(NO_VERSION, "no version supplied")

    pk3 = makePK3([])

    print("renaming... ", end="")
    sys.stdout.flush()

    pk3Name = os.path.basename(pk3)
    pk3Base = pk3Name.rsplit(".", 1)[0]

    zipBase = [pk3Base, aArgs[0]]

    if pk3Base[-1] in NUMBERS:
        zipBase = "_".join(zipBase)
    else:
        zipBase = "".join(zipBase)

    zipName  = "{}.zip".format(zipBase)
    pk3Name2 = "{}.pk3".format(zipBase)

    shutil.move(pk3, pk3Name2)
    print("done.")

    print("packaging... ", end="")
    sys.stdout.flush()


    pk3Zip = zipfile.ZipFile(zipName, "w")

    for file in (pk3Name2, "README", "README.txt", "CHANGELOG", "CHANGELOG.txt"):
        if os.path.isfile(file):
            pk3Zip.write(file, file)

    pk3Zip.close()

    print(zipName)

    if WAD_DIR is not None:
        pk3Name3 = WAD_DIR + "/" + pk3Name2

        print("copying {} to {}... ".format(pk3Name2, pk3Name3), end="")
        sys.stdout.flush()

        shutil.copy(pk3Name2, pk3Name3)
        print("done.")

def printHelp(aArgs):
    usageFull()


choices = {MAKE_ACT: makePK3, TEST_ACT: testPK3, PACKAGE_ACT: packagePK3,
            HELP_ACT: printHelp}

#######
##
#   MAIN CODE
##
###

def main(*args, **kwargs):

    if len(args) < 2:
        usageExit(NO_ARGS, "not enough arguments")

    action = args[1].lower()
    aArgs  = args[2:]

    if action in choices:
        choices[action](aArgs)
    else:
        usageExit(127, "not a valid command")

if __name__ == "__main__":
    main(*sys.argv)
