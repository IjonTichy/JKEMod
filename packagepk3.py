#!/usr/bin/env python3

import sys, os, shutil, zipfile
from subprocess import Popen, PIPE

import which
from pathwalker import pathwalker

NUMBERS     = "0123456789"

MAKE_ACT    = "make"
TEST_ACT    = "test"
PACKAGE_ACT = "package"

USAGE = "usage: {} [{}] <args>".format(os.path.basename(sys.argv[0]), "|".join([MAKE_ACT, TEST_ACT, PACKAGE_ACT]))

ACS_EXTS    = ("c", "acs")
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
    
    print(USAGE)
    sys.exit(code)



NO_ARGS     = 4
NO_PK3      = 5
NO_ACC      = 6
NO_VERSION  = 7

PK3NAME     = os.path.basename(os.path.realpath("."))

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
    ACC_DIR = os.path.realpath(".")
else:
    ACC_DIR = which.which("acc")

    if ACC_DIR is None:
        errorExit(NO_ACC, "no acc in PATH or PWD")
    else:
        ACC_DIR = ACC_DIR.rpartition("/")[0]



def playPK3(pk3, binary=SKULLTAG, *args):
    
    if binary is None:
        errorExit(1, "no binary")
    
    pk3 = os.path.realpath(pk3)
    
    if not os.path.isfile(pk3):
        errorExit(1, "somehow, {} doesn't exist")

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
 
    assert os.path.isfile(file), "must provide name of actual file"
    
    oldDir = os.getcwd()
    
    newFile = file.rpartition(".")[:2] + ("o",)
    newFile = "".join(newFile)
    
    newFile2 = file2.rpartition(".")[:2] + ("o",)
    newFile2 = "".join(newFile2)
    
    os.chdir(ACC_DIR)
    accProc = Popen(["./acc", file, newFile], stdout=PIPE, stderr=PIPE)
    os.chdir(oldDir)

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
    pk3Files    = pk3Walk.walk(abs=1).flattenFiles(rel=1)
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
            
            if file.rsplit(".", 1)[1] in ACS_EXTS:  # ACS
                objFile = compileACS(file)
                pk3Zip.write(objFile, objFile.lstrip("./"))


            pk3Zip.write(file, file.lstrip("./"))
    
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

#######
##
#   MAIN CODE
##
###


choices = {MAKE_ACT: makePK3, TEST_ACT: testPK3, PACKAGE_ACT: packagePK3}

def main(*args, **kwargs):
    
    if len(args) < 2:
        usageExit(NO_ARGS, "not enough arguments")

    action = args[1].lower()
    aArgs  = args[2:]
    
    choices[action](aArgs)


if __name__ == "__main__":
    main(*sys.argv)
