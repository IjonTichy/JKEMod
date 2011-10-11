lol = """\
        BFE1 B 0 A_CustomMissile("RipperMoleculeDebris",    0, 0, {},{} CMF_AIMDIRECTION|CMF_TRACKOWNER, 0)
        BFE1 B 0 A_CustomMissile("ExplosiveMoleculeDebris", 0, 0, {},{} CMF_AIMDIRECTION|CMF_TRACKOWNER, 0)
"""

lolFile = open("tmp.txt", "w")


for i in range(0, 360, 10):

    len1 = " " * (3-len(str(i  ) ) )
    len2 = " " * (3-len(str(i+5) ) )

    lolFile.write(lol.format(i, len1, i+5, len2) )

lolFile.close()
