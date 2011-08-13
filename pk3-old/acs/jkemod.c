#library "jkemod"
#include "zcommon.acs"

script 900 (int trigger)  // freeze the player
{
    SetPlayerproperty(0, trigger, 0);
}

Script 901 (int line)
{
    switch (line)
    {
      case 0:
        Print(s:"Missile launcher mode");
        break;

      case 1:
        Print(s:"Shotgun ice launcher mode");
        break;

      case 2:
        Print(s:"Fire spread launcher mode");
        break;
    }
}

Script 902 (int speed)
{
    SetActorProperty(0, APROP_Speed, speed);
}
