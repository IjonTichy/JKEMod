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


script 683 (int slot, int dropped)
{
    int pln = PlayerNumber();
    int found;
    int ret;
    int wep;
    int ammo1; int ammo2; int ammo3;

    int oAmo1; int oAmo2; int oAmo3;
    int cAmo1; int cAmo2; int cAmo3;
    int dAmo1; int dAmo2; int dAmo3;

    int sAmo1; int sAmo2; int sAmo3;

    int oMax1; int oMax2; int oMax3;

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

    ammo1 = classWeps[found][slot][WEPCOUNT+1];
    ammo2 = classWeps[found][slot][WEPCOUNT+2];
    ammo3 = classWeps[found][slot][WEPCOUNT+3];

    if (dropped)
    {
        if (ammo1 != "None")
        {
            oMax1 = GetAmmoCapacity(ammo1);
            oAmo1 = CheckInventory(ammo1);
            SetAmmoCapacity(ammo1, oMax1*4);

            if (oAmo1 == oMax1)
            {
                sAmo1 = 1;
            }
        }

        if (ammo2 != "None")
        {
            oMax2 = GetAmmoCapacity(ammo2);
            oAmo2 = CheckInventory(ammo2);
            SetAmmoCapacity(ammo2, oMax2*4);

            if (oAmo2 == oMax2)
            {
                sAmo2 = 2;
            }
        }

        if (ammo3 != "None")
        {
            oMax3 = GetAmmoCapacity(ammo3);
            oAmo3 = CheckInventory(ammo3);
            SetAmmoCapacity(ammo3, oMax3*4);

            if (oAmo3 == oMax3)
            {
                sAmo3 = 3;
            }
        }
    }

    for (i = 0; i < WEPCOUNT; i++)
    {
        wep  =  classWeps[found][slot][i];

        if (wep == "None")
        {
            continue;
        }

        check1 = CheckInventory(wep);
        check2 = ret & WEAPONSTAYON;

        if (ammo1 == "None" || sAmo1)
        { check3 = 1 - sAmo1;}
        else { check3 = CheckInventory(ammo1) < GetAmmoCapacity(ammo1); }

        if (ammo2 == "None" || sAmo2)
        { check4 = 0; }
        else { check4 = CheckInventory(ammo2) < GetAmmoCapacity(ammo2); }

        if (ammo3 == "None" || sAmo3)
        { check5 = 0; }
        else { check5 = CheckInventory(ammo3) < GetAmmoCapacity(ammo3); }

        if (!check1)
        {
            GiveInventory(wep, 1);
            ret |= GAVEWEAPON;
        }
        else if (!check2 || dropped)
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

    if (dropped)
    {
        if (ammo1 != "None")
        {
            cAmo1 = CheckInventory(ammo1);
            dAmo1 = cAmo1 - oAmo1;
            TakeInventory(ammo1, dAmo1 / 2);
            SetAmmoCapacity(ammo1, oMax1);
            cAmo1 = CheckInventory(ammo1);

            if (cAmo1 > oMax1)
            {
                TakeInventory(ammo1, cAmo1 - oMax1);
            }
        }

        if (ammo2 != "None")
        {
            cAmo2 = CheckInventory(ammo2);
            dAmo2 = cAmo2 - oAmo2;
            TakeInventory(ammo2, dAmo2 / 2);
            SetAmmoCapacity(ammo2, oMax2);
            cAmo1 = CheckInventory(ammo1);

            if (cAmo2 > oMax2)
            {
                TakeInventory(ammo2, cAmo2 - oMax2);
            }
        }

        if (ammo3 != "None")
        {
            cAmo3 = CheckInventory(ammo3);
            dAmo3 = cAmo3 - oAmo3;
            TakeInventory(ammo3, dAmo3 / 2);
            SetAmmoCapacity(ammo3, oMax3);
            cAmo1 = CheckInventory(ammo1);

            if (cAmo3 > oMax3)
            {
                TakeInventory(ammo3, cAmo3 - oMax3);
            }
        }
    }

    SetResultValue(ret);
}