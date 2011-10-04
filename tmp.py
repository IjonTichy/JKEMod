#!/usr/bin/python3

tmp = """
pointlight [name]{0}
{{
    color [r] [g] [b]
    size {1}
}}
"""

MAX = 6
LIGHTMULT = 12

NAME = "YellowPlasmaGlow"

RED   = 255
GREEN = 255
BLUE  = 0

MAXA = MAX + 1
REDA, GREENA, BLUEA = (i/255.0 for i in (RED, GREEN, BLUE) )

lol = open("tmp.txt", "w")

for i in (("name", NAME), ("r", REDA), ("g", GREENA), ("b", BLUEA)):
    tag = "[{0}]".format(i[0])
    var = i[1]
    tmp = tmp.replace(tag, str(var) )



for i in range(0, MAXA):
    lol.write(tmp.format(i, LIGHTMULT*(i+1) ) )
