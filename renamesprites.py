#!/usr/bin/python3

import sys
import os
import shutil

assert len(sys.argv) > 2, "not enough arguments"

oldStart = sys.argv[1]
newStart = sys.argv[2]

if len(sys.argv) > 3:
    wDir = sys.argv[3]
else:
    wDir = "."

ls = os.listdir(wDir)
playersprites = []

for image in ls:
    if image.startswith(oldStart):
        newname = newStart + image[len(oldStart):]
        playersprites.append((image, newname))

for (oldname, newname) in playersprites:
    shutil.move(oldname, newname)
