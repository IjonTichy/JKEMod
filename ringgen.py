import math

baseStr = "BAL1 C 0 A_SpawnItemEx(\"FragmentShard\", 0, 0, 0, {0}, 0, {1}, {2})"

RING_AMOUNT = 20


for i in range(0, 360//20):
    for j in range(-2, 3, 1):
        print(baseStr.format(80*math.cos(math.radians(j*5) ), 80*math.sin(math.radians(j*5) ), i*20) )
