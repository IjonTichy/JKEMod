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
    int wep;
    int ammo1; int ammo2; int ammo3;
    int check1; int check2; int check3; int check4; int check5;
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
        wep  =  classWeps[found][slot][i];
        ammo1 = classWeps[found][slot][WEPCOUNT+1];
        ammo2 = classWeps[found][slot][WEPCOUNT+2];
        ammo3 = classWeps[found][slot][WEPCOUNT+3];

        if (wep == "None")
        {
            continue;
        }

        check1 = CheckInventory(wep);
        check2 = ret & WEAPONSTAYON;

        if (ammo1 == "None")
        { check3 = 1; }
        else { check3 = CheckInventory(ammo1) < GetAmmoCapacity(ammo1); }

        if (ammo2 == "None")
        { check4 = 0; }
        else { check4 = CheckInventory(ammo2) < GetAmmoCapacity(ammo2); }

        if (ammo3 == "None")
        { check5 = 0; }
        else { check5 = CheckInventory(ammo3) < GetAmmoCapacity(ammo3); }

        if (!check1)
        {
            GiveInventory(wep, 1);
            ret |= GAVEWEAPON;
        }
        else if (!check2)
        {
            if (check3 || check4 || check5)
            {
                GiveInventory(wep, 1);
                ret |= GAVEWEAPON;
            }
        }
    }

    check1 = GAVEWEAPON;

    if (ret & check1 == check1)
    {
        wep = classWeps[found][slot][2];

        x = GetActorX(0);
        y = GetActorY(0);
        z = GetActorZ(0) + 4.0;

        Spawn(wep, x, y, z);
    }

    SetResultValue(ret);
}
