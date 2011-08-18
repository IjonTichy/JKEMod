#library "jkemod"
#include "zcommon.acs"

int multigunStrings[3] = {
    "Missiles",
    "Ice shards",
    "Flame grenades"};

script 900 (int trigger)  // (un)freeze the player
{
    SetPlayerProperty(0, trigger, 0);
}

script 901 (void)
{
    int curMode = CheckInventory("MultigunMode");
    int newMode = (curMode + 1) % 3;

    TakeInventory("MultigunMode", 0x7FFFFFFF);
    GiveInventory("MultigunMode", newMode);
    Print(s:multigunStrings[newMode]);
}

script 902 (int speedInt, int speedFrac)
{
    int speed = (speedInt << 16) + ((speedFrac << 16) / 100);
    SetActorProperty(0, APROP_Speed, speed);
}
