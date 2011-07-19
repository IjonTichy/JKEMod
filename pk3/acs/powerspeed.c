#include "zcommon.acs"

#library "powerfade"

// faderange(int red1, int green1, int blue1, fixed amount1, int red2,
//           int green2, int blue2, fixed amount2, fixed seconds)
//
// fadeto (int red, int green, int blue, fixed amount, fixed seconds);

script 649 (void) clientside
{
    FadeTo(256, 0, 64, 1.0, 0.0625);
    Delay(35);
    while (1)
    {
        if (!CheckInventory("PowerWeaponLevel2"))
        {
            FadeTo(0, 0, 0, 0.0, 1.0);
            break;
        }
        FadeTo(256, 0, 128, 0.35, 0.5);
        Delay(18);

        if (!CheckInventory("PowerWeaponLevel2"))
        {
            FadeTo(0, 0, 0, 0.0, 1.0);
            break;
        }
        FadeTo(192, 0, 128, 0.3,  0.5);
        Delay(18);

        if (!CheckInventory("PowerWeaponLevel2"))
        {
            FadeTo(0, 0, 0, 0.0, 1.0);
            break;
        }
        FadeTo(224, 0, 96, 0.25, 0.5);
        Delay(18);

        if (!CheckInventory("PowerWeaponLevel2"))
        {
            FadeTo(0, 0, 0, 0.0, 1.0);
            break;
        }
        FadeTo(192, 0, 96, 0.3, 0.5);
        Delay(18);

        if (!CheckInventory("PowerWeaponLevel2"))
        {
            FadeTo(0, 0, 0, 0.0, 1.0);
            break;
        }
        FadeTo(160, 0, 128, 0.3, 0.5);
        Delay(18);

        if (!CheckInventory("PowerWeaponLevel2"))
        {
            FadeTo(0, 0, 0, 0.0, 1.0);
            break;
        }
        FadeTo(192, 0, 128, 0.25, 0.5);
        Delay(18);
    }
}
