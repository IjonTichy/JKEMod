#include "zcommon.acs"
#library "classWeapons"

#include "classWepList.h"

#define GAVEWEAPON      1
#define WEAPONSTAYON    2
#define NOCLASS         4

global int 6:classes[];


script 682 (int which)
{
    int pln = PlayerNumber();
    classes[pln] = which;
}


script 683 (int slot)
{
    int pln = PlayerNumber();
    int found;
    int ret;
    int wep; int ammo;
    int check; int check2;
    int x; int y; int z;
    int i;

    if (GetCVar("sv_weaponstay"))
    {
        ret |= WEAPONSTAYON;
    }

    slot -= 1;

    found = classes[pln] - 1;

    if (found == -1)
    {
        ret |= NOCLASS;
    }

    /*if (found & MULTIPLECLASSES)
    {
        Print(s:"something broke - classes ", d:found, s:" and ", d:i, " found");
        terminate;
    }*/
    if (ret & NOCLASS)
    {
        Print(s:"something broke - no classes found");
        terminate;
    }

    for (i = 0; i < WEPCOUNT; i++)
    {
        wep  = classWeps[found][slot][i];
        ammo = classWeps[found][slot][WEPCOUNT+1];

        check = !CheckInventory(wep);
        check2 = !(ret & WEAPONSTAYON) && (CheckInventory(ammo) < GetAmmoCapacity(ammo) );

        if (check || check2)
        {
            GiveInventory(wep, 1);
            ret |= GAVEWEAPON;
        }
    }

    check = GAVEWEAPON;

    if (ret & check == check)
    {
        wep = classWeps[found][slot][2];

        x = GetActorX(0);
        y = GetActorY(0);
        z = GetActorZ(0) + 4.0;

        Spawn(wep, x, y, z);
    }

    SetResultValue(ret);
}
