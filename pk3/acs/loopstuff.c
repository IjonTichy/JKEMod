#include "zcommon.acs"
#library "loopstuff"


int dead[32];
int inGame[32];

script 759 OPEN
{
    if (GetCVar("compat_clientssendfullbuttoninfo") == 0)
    {
        ConsoleCommand("compat_clientssendfullbuttoninfo 1");
        Log(s:"compat_clientssendfullbuttoninfo must be on for the mod to work properly");
    }
}

script 760 (void)   /* generic button signaler */
{
    int pln = PlayerNumber();
    int buttons;
    while (!dead[pln] && inGame[pln])
    {
        buttons = GetPlayerInput(-1, MODINPUT_BUTTONS);
        if (buttons & BT_ATTACK)
        {
            GiveInventory("MainFired", 1);
        }
        else
        {
            TakeInventory("MainFired", 16);
        }

        if (buttons & BT_ALTATTACK)
        {
            GiveInventory("AltFired", 1);
        }
        else
        {
            TakeInventory("AltFired", 16);
        }

        Delay(1);
    }
}


script 761 ENTER
{
    TakeInventory("PlayerDead", 1); // y'know, assuming you have it
    inGame[PlayerNumber()] = 1;
    dead[PlayerNumber()] = 0;
    ACS_ExecuteAlways(760, 0, 0,0,0);
    ACS_ExecuteAlways(730, 0, 0,0,0);

    // best to assume we don't have it than assume we do
    GiveInventory("ReloadButtonOn", 1);
    GiveInventory("ReloadButtonOff", 1);
}

script 762 DEATH
{
    GiveInventory("PlayerDead", 1);
    inGame[PlayerNumber()] = 1;
    dead[PlayerNumber()] = 1;
}

script 763 (int pln) DISCONNECT
{
    dead[PlayerNumber()] = 0;
    inGame[PlayerNumber()] = 0;
}

script 764 RESPAWN
{
    TakeInventory("PlayerDead", 1);
    inGame[PlayerNumber()] = 1;
    dead[PlayerNumber()] = 0;
    ACS_ExecuteAlways(760, 0, 0,0,0);
    ACS_ExecuteAlways(730, 0, 0,0,0);
}


script 730 (void)
{
    int pln = PlayerNumber();
    int check;

    while (!dead[pln] && inGame[pln])
    {
        if (!CheckInventory("IAmAMage") )
        {
            terminate;
        }
        Delay(1);
        check += 1;

        if (check % 10 == 0)
        {
            GiveInventory("HellFistCounter", 1);
        }

        if ((check % 10) == 0 && CheckInventory("PowerWeaponLevel2"))
        {
            GiveInventory("JKEMana", 1);
        }


        if (check % 20 == 0 && !CheckInventory("PowerWeaponLevel2"))
        {
            GiveInventory("JKEMana", 1);
        }

        if (check % 20 == 0)
        {
            check = 0;
        }

    }
}
