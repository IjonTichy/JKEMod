#include "zcommon.acs"
#library "mousecheck"


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

script 760 (void)   /* generic attack/alt attack handler */
{
    int pln = PlayerNumber();
    int buttons;
    while (!dead[pln] && inGame[pln])
    {
        buttons = GetPlayerInput(-1, MODINPUT_BUTTONS);
        if (buttons & BT_ATTACK)
        { GiveInventory("MainFired", 1); }
        else
        { TakeInventory("MainFired", 16); }

        if (buttons & BT_ALTATTACK)
        { GiveInventory("AltFired", 1); }
        else
        { TakeInventory("AltFired", 16); }

        Delay(1);
    }
}

script 761 ENTER
{
    TakeInventory("PlayerDead", 1); // y'know, assuming you have it
    inGame[PlayerNumber()] = 1;
    dead[PlayerNumber()] = 0;
    ACS_ExecuteAlways(760, 0, 0,0,0);
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
}
