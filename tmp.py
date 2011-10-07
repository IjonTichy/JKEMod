#!/usr/bin/python3

tmp1 = """
pointlight [name]{0}
{{
    color [r] [g] [b]
    size {1}
}}
"""

tmp2 = """
pointlight [name]{0}
{{
    color {1} {2} {3}
    size [s]
}}
"""

MAX = 30
LIGHTMULT = 8

STEPS = 13

NAME = "MultigunRocketGlow"

RED   = 255
GREEN = 231
BLUE  = 201

SIZE = 144

MAXA = MAX + 1
REDA, GREENA, BLUEA = (round(i/255.0, 2) if (i > 1) else i for i in (RED, GREEN, BLUE) )

TAGS = (("name", NAME),
        ("s", SIZE),
        #("r", REDA),
        #("g", GREENA),
        #("b", BLUEA)
       )

lol = open("tmp.txt", "w")

tmp = tmp2

for i in TAGS:
    tag = "[{0}]".format(i[0])
    var = i[1]
    tmp = tmp.replace(tag, str(var) )



for i in range(STEPS, 0, -1):

    j = i / float(STEPS)

    newR = round(REDA   * j, 2)
    newG = round(GREENA * j, 2)
    newB = round(BLUEA  * j, 2)

    lol.write(tmp.format(i, newR, newG, newB) )
