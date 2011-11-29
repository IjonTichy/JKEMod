lol = """\
        TNT1 A 1 A_Explode({}, {})
"""

lolFile = open("tmp.txt", "w")

lolRate1 = int(8192 / (35 * 5) )
lolRate2 = int(512 / (35 * 5) )

for i in range(0, 35*5):
    lolWrite = lol.format(8192 - (i * lolRate1), 2048 - (i * lolRate2) )
    lolFile.write(lolWrite)

lolFile.close()
