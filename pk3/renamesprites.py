#!/usr/bin/python3

import shutil, os

ls = os.listdir('.')
playersprites = []

for image in ls:
    if image.startswith('MAN3'):
        newname = 'JMAN' + image[4:]
        playersprites.append((image, newname))

for (oldname, newname) in playersprites:
    shutil.move(oldname, newname)
