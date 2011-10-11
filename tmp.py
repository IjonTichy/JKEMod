#!/usr/bin/env python3

lol = """\
actor JKE{0}Pickup: JKEClassPickupSpawner replaces {0}
{{
    +NOINTERACTION

    States
    {{
        Spawn:
          TNT1 A 0
          TNT1 A 0 A_JumpIf(ACS_ExecuteWithResult(684) == 1, "DropSpawn")
          goto NormSpawn

        DropSpawn:
          TNT1 A 0 A_SpawnItemEx("JKEClass{1}Drop{2}", 0, 0, 0, momx, momy, momz)
          stop

        NormSpawn:
          TNT1 A 0 A_SpawnItemEx("JKEClass{1}Pickup{2}", 0, 0, 0, momx, momy, momz)
          stop
    }}
}}

"""


tmpList = [["Chainsaw"], ["Pistol"], ["Shotgun", "SuperShotgun"],
           ["Chaingun", "Minigun"], ["RocketLauncher", "GrenadeLauncher"],
           ["PlasmaRifle", "Railgun"], ["BFG9000"], ["BFG10k"]]

tmpFile = open("tmp.txt", "w")

for n, i in enumerate(tmpList):
    n += 1

    for m, j in enumerate(i):

        if m == 0:
            m = ""
        else:
            m += 1

        tmpFile.write(lol.format(j, n, m) )
