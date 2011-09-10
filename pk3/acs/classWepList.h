#define CLASSCOUNT 3
#define SLOTCOUNT  8
#define WEPCOUNT   2

int classItems[CLASSCOUNT] =
{
    "BDWClassItem",
    "SMClassItem",
    "JKEGuyClassItem"
};

int classWeps[CLASSCOUNT][SLOTCOUNT][WEPCOUNT+2] =
{
    {
        {" B-Fist ",            " B-Chainsaw ",        "BDWClass1Message", "None"},
        {" B-Pistol ",          " B-Pistol ",          "BDWClass2Message", "Clip"},
        {" B-Shotgun ",         " B-Super Shotgun ",   "BDWClass3Message", "Shell"},
        {" B-Chaingun ",        " B-Chaingun ",        "BDWClass4Message", "Clip"},
        {" B-Rocket Launcher ", " B-Rocket Launcher ", "BDWClass5Message", "RocketAmmo"},
        {" B-Plasma Rifle ",    " B-Plasma Rifle ",    "BDWClass6Message", "Cell"},
        {" B-BFG9000 ",         " B-BFG9000 ",         "BDWClass7Message", "Cell"},
        {" D-1000 ",            " D-1000 ",            "BDWClass8Message", "Cell"}
    },
    {
        {" S-Knife ",           " S-Knife ",           "SMClass1Message", "None"},
        {" S-Enforcer ",        " S-Enforcer ",        "SMClass2Message", "Clip"},
        {" S-Shotgun ",         " S-Shotgun ",         "SMClass3Message", "Shell"},
        {" S-Chaingun ",        " S-Chaingun ",        "SMClass4Message", "Clip"},
        {" S-Cluster Bomber ",  " S-Cluster Bomber ",  "SMClass5Message", "RocketAmmo"},
        {" S-Plasma Beam ",     " S-Plasma Beam ",     "SMClass6Message", "Cell"},
        {" Y23H ",              " Y23H ",              "SMClass7Message", "Cell"},
        {" S-Ionstrike ",       " S-Ionstrike ",       "SMClass8Message", "Cell"}
    },
    {
        {" J-Fists ",           " J-Fists ",           "JKEGuyClass1Message", "None"},
        {" J-Dual Pistols ",    " J-Dual Pistols ",    "JKEGuyClass2Message", "Clip"},
        {" J-Shotgun ",         " J-Super Shotgun ",   "JKEGuyClass3Message", "Shell"},
        {" J-Uzi ",             " Heavy Chaingun ",    "JKEGuyClass4Message", "Clip"},
        {" J-Rocket Launcher ", " Fragment Launcher ", "JKEGuyClass5Message", "RocketAmmo"},
        {" J-Plasma Rifle ",    " Karasawa ",          "JKEGuyClass6Message", "Cell"},
        {" Molecule Shooter ",  " Molecule Shooter ",  "JKEGuyClass7Message", "Cell"},
        {" BFG7000 ",           " BFG7000 ",           "JKEGuyClass8Message", "Cell"}
    }
};
