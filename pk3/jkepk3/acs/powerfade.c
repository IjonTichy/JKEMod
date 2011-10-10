#include "zcommon.acs"

#library "powerfade"

script 648 (int mode)
{
    int check;

    switch (mode)
    {
    case 0:
        if (CheckInventory("AmmosphereLock"))
        {
            break;
        }

        GiveInventory("AmmosphereLock", 1);

        while (1)
        {
            check += 1;
            delay(2);

            if (!CheckInventory("AmmoIndicator"))
            {
                break;
            }


            GiveInventory("Clip", 1);
            GiveInventory("Cell", 1);

            GiveInventory("BerettaAmmo", 1);
            GiveInventory("M249Ammo", 1);
            GiveInventory("MinigunAmmo", 1);


            GiveInventory("JKEMana", 1);
            GiveInventory("FlameAmmo", 1);

            if (check % 2 == 0)
            {
                GiveInventory("FireAmmo", 1);
                GiveInventory("BallestaAmmo", 1);
                GiveInventory("DevastatorAmmo", 1);

                GiveInventory("JKEGas", 1);
            }

            if (check % 6 == 0)
            {
                GiveInventory("Shell", 1);
                GiveInventory("EtherealAmmo", 1);

                GiveInventory("RocketAmmo", 1);
                GiveInventory("ExplosiveAmmo", 1);

                GiveInventory("BeamAmmo", 1);
                GiveInventory("JSniperAmmo", 1);
            }

            if (check % 35 == 0)
            {
                GiveInventory("MedikitAmmo", 1);
            }

            if (check % 210 == 0)
            {
                check = 0;
            }
        }
        TakeInventory("AmmosphereLock", 1);
        break;

    case 1:
        if (CheckInventory("AmmosphereLock2"))
        {
            break;
        }

        GiveInventory("AmmosphereLock2", 1);

        while (1)
        {
            check += 1;
            delay(6);

            if (!CheckInventory("AmmoIndicator2"))
            {
                break;
            }


            GiveInventory("Clip", 1);
            GiveInventory("Cell", 1);

            GiveInventory("BerettaAmmo", 1);
            GiveInventory("M249Ammo", 1);
            GiveInventory("MinigunAmmo", 1);


            GiveInventory("JKEMana", 1);
            GiveInventory("FlameAmmo", 1);

            if (check % 2 == 0)
            {
                GiveInventory("FireAmmo", 1);
                GiveInventory("BallestaAmmo", 1);
                GiveInventory("DevastatorAmmo", 1);

                GiveInventory("JKEGas", 1);
            }

            if (check % 6 == 0)
            {
                GiveInventory("Shell", 1);
                GiveInventory("EtherealAmmo", 1);

                GiveInventory("RocketAmmo", 1);
                GiveInventory("ExplosiveAmmo", 1);

                GiveInventory("BeamAmmo", 1);
                GiveInventory("JSniperAmmo", 1);
            }

            if (check % 35 == 0)
            {
                GiveInventory("MedikitAmmo", 1);
            }

            if (check % 210 == 0)
            {
                check = 0;
            }
        }
        TakeInventory("AmmosphereLock2", 1);
        break;
    }
}

// faderange(int red1, int green1, int blue1, fixed amount1, int red2,
//           int green2, int blue2, fixed amount2, fixed seconds)
//
// fadeto (int red, int green, int blue, fixed amount, fixed seconds);

script 649 (int mode) clientside
{
    switch (mode)
    {
    case 0:
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
        break;


    case 1:
        while (1)
        {
            if (!CheckInventory("AmmoIndicator"))
            {
                FadeTo(0, 0, 0, 0.0, 1.0);
                break;
            }
            FadeTo(0,  0,  255, 0.35, 0.5);
            Delay(18);

            if (!CheckInventory("AmmoIndicator"))
            {
                FadeTo(0, 0, 0, 0.0, 1.0);
                break;
            }
            FadeTo(0,  0,  192, 0.30, 0.5);
            Delay(18);

            if (!CheckInventory("AmmoIndicator"))
            {
                FadeTo(0, 0, 0, 0.0, 1.0);
                break;
            }
            FadeTo(64, 64, 192, 0.30, 0.5);
            Delay(18);

            if (!CheckInventory("AmmoIndicator"))
            {
                FadeTo(0, 0, 0, 0.0, 1.0);
                break;
            }
            FadeTo(64,  64,  255, 0.35, 0.5);
            Delay(18);

            if (!CheckInventory("AmmoIndicator"))
            {
                FadeTo(0, 0, 0, 0.0, 1.0);
                break;
            }
            FadeTo(64,  0,  224, 0.30, 0.5);
            Delay(18);

            if (!CheckInventory("AmmoIndicator"))
            {
                FadeTo(0, 0, 0, 0.0, 1.0);
                break;
            }
            FadeTo(32,  32,  255, 0.25, 0.5);
            Delay(18);
        }
        break;
    }
}
