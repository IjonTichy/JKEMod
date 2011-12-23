#library "jkemod"
#include "zcommon.acs"

#include "commonFuncs.h"

int multigunStrings[3] = {
    "Missiles",
    "Ice shards",
    "Flame grenades",
};

script 872 (int num) // generic number printer
{
    PrintBold(d:num);
}

script 873 (int which, int arg1, int arg2)  // get inventory
{
    switch (which)
    {
        case 0:
            if (arg1 == 0)
            {
                arg1 = 1;
            }
            int charge = CheckInventory("TristaffCharge");
            SetResultValue(charge * arg1);
            break;

        case 1:
            int ret = CheckInventory("JKEMana");
            ret /= arg1;

            SetResultValue(middle(1, ret, GetAmmoCapacity("TriStaffCharge") ) );
            break;
    }
}

script 874 (int trigger)  // (un)freeze the player
{
    SetPlayerProperty(0, trigger, 0);
}

script 875 (void)
{
    int curMode = CheckInventory("MultigunMode");
    int newMode = (curMode + 1) % 3;

    TakeInventory("MultigunMode", 0x7FFFFFFF);
    GiveInventory("MultigunMode", newMode);
    Print(s:multigunStrings[newMode]);
}

script 876 (int argInt, int argFrac, int which)
{
    int arg = (argInt << 16) + ((argFrac << 16) / 100);

    ACS_ExecuteAlways(877, 0, arg, which, 0);
}

script 877 (int arg, int which)
{
    switch (which)
    {
        case 0:
            SetActorProperty(0, APROP_Speed, arg);
            break;

        case 1:
            SetActorProperty(0, APROP_JumpZ, arg);
            break;

        case 2:
            SetActorProperty(0, APROP_RenderStyle, STYLE_None);
            SetActorProperty(0, APROP_NoTarget, 1);
            GiveInventory("InvisOn", 1);
            SetPlayerProperty(0, 1, 1);
            break;

        case 3:
            SetActorProperty(0, APROP_RenderStyle, STYLE_Normal);
            SetActorProperty(0, APROP_NoTarget, 0);
            GiveInventory("InvisOff", 1);
            SetPlayerProperty(0, 0, 1);
            break;

        case 4:
            SetActorProperty(0, APROP_DamageFactor, arg);
            break;

        case 5:
            arg >>= 16;
            SetActorProperty(0, APROP_SpawnHealth, arg);
            SetActorProperty(0, APROP_Health, arg);
            break;
    }
}
