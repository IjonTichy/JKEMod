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
    classes[pln] = which - 1;

    if (GetCVar("sv_cheats") == 1)
    {
        Print(s:"Use \"puke -878\" to get all your class' weapons\n(only when sv_cheats is 1)");
    }
}


script 683 (int slot, int dropped)
{
    int pln = PlayerNumber();
    int found;
    int ret;
    int wep;
    int ammo1; int ammo2;

    int oAmo1; int oAmo2;
    int cAmo1; int cAmo2;
    int dAmo1; int dAmo2;
    int sAmo1; int sAmo2;
    int oMax1; int oMax2;

    int check1; int check2; int check3; int check4;
    int x; int y; int z;
    int i;

    if (GetCVar("sv_weaponstay"))
    {
        ret |= WEAPONSTAYON;
    }

    slot -= 1;

    found = classes[pln];

    if (found == -1)
    {
        ret |= NOCLASS;
    }

    if (classWeps[found][slot][0] == "None")
    {
        SetResultValue(ret);
        terminate;
    }

    if (ret & NOCLASS)
    {
        // Tichy: for some reason, without sv_weaponstay on, this always prints
        //Print(s:"something broke - no classes found\nReport the weapon you picked up and the class you're using to Ijon Tichy (gztichy@lavabit.com)");
        SetResultValue(ret);
        terminate;
    }

    ammo1 = classWeps[found][slot][WEPCOUNT+1];
    ammo2 = classWeps[found][slot][WEPCOUNT+2];

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


        if (!check1)
        {
            GiveInventory(wep, 1);
            ret |= GAVEWEAPON;
        }
        else if (!check2 || dropped)
        {
            if (check3 || check4)
            {
                GiveInventory(wep, 1);
                ret |= GAVEWEAPON;
            }
        }
    }

    check1 = GAVEWEAPON;

    if (ret & check1 == check1)
    {
        wep = classWeps[found][slot][WEPCOUNT];

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
    }

    SetResultValue(ret);
}


script 878 (void)
{
    int i; int w;

    int a1;  int a2;
    int ca1; int ca2;

    int plc = classes[PlayerNumber()];

    if (GetCVar("sv_cheats") != 0 || GameType() == 0)
    {
        GiveInventory("Backpack", 1);

        for (i = 0; i < SLOTCOUNT; i++)
        {
            w  = classWeps[plc][i][0];
            a1 = classWeps[plc][i][2];
            a2 = classWeps[plc][i][3];

            if (w != "None")
            {
                GiveInventory(w, 1);
            }

            if (a1 != "None")
            {
                ca1 = CheckInventory(a1);
                GiveInventory(a1, GetAmmoCapacity(a1) - ca1);
            }

            if (a2 != "None")
            {
                ca2 = CheckInventory(a2);
                GiveInventory(a2, GetAmmoCapacity(a2) - ca2);
            }
        }

        if (GameType() == 0)
        {
            terminate;
        }
    }

    PrintBold(n:0, s:"\c- is being a cheater by calling script 878!");

    if (GetCVar("sv_cheats") == 0)
    {
        ClearInventory();
        Delay(105);
        PrintBold(s:"As such, ", n:0, s:"\c- has lost his/her/its entire inventory.");
    }
    else
    {
        Delay(105);
        PrintBold(s:"But sv_cheats is true, so who cares?");
    }
}
