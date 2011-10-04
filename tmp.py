#!/usr/bin/python3

tmp = """
pointlight [name]{0}
{{
    color [r] [g] [b]
    size {1}
}}
"""

MAX = 20
LIGHTMULT = 8

NAME = "FGFireballGlow"

RED   = 1.0
GREEN = 0.7
BLUE  = 0.2

MAXA = MAX + 1
REDA, GREENA, BLUEA = (i/255.0 if (i > 1) else i for i in (RED, GREEN, BLUE) )

lol = open("tmp.txt", "w")

for i in (("name", NAME), ("r", REDA), ("g", GREENA), ("b", BLUEA)):
    tag = "[{0}]".format(i[0])
    var = i[1]
    tmp = tmp.replace(tag, str(var) )



for i in range(0, MAXA):
    lol.write(tmp.format(i, LIGHTMULT*(i+1) ) )
