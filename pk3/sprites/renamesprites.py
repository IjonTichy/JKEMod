#!/usr/bin/python3

import shutil, os

ls = os.listdir('.')
playersprites = []

for image in ls:
    if image.startswith('CSSN'):
        newname = 'SNCS' + image[4:]
        playersprites.append((image, newname))

for (oldname, newname) in playersprites:
    shutil.move(oldname, newname)
