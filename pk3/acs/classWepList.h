#define CLASSCOUNT 5
#define SLOTCOUNT  8
#define WEPCOUNT   2

int classItems[CLASSCOUNT] =
{
    "BDWClassItem",
    "SMClassItem",
    "JKEGuyClassItem"
};

int classWeps[CLASSCOUNT][SLOTCOUNT][WEPCOUNT+4] =
{
    {
        {" B-Fists ",           " B-Chainsaw ",        "BDWClass1Message",      "None",    "None", "None"},
        {" B-Pistol ",          " B-Pistol ",          "BDWClass2Message",      "Clip",    "None", "None"},
        {" B-Shotgun ",         " B-Super Shotgun ",   "BDWClass3Message",      "Shell",   "None", "None"},
        {" B-Chaingun ",        " B-Chaingun ",        "BDWClass4Message",      "Clip",    "None", "None"},
        {" B-Rocket Launcher ", " B-Rocket Launcher ", "BDWClass5Message",      "RocketAmmo", "None", "None"},
        {" B-Plasma Rifle ",    " B-Plasma Rifle ",    "BDWClass6Message",      "Cell",    "None", "None"},
        {" B-BFG9000 ",         " B-BFG9000 ",         "BDWClass7Message",      "Cell",    "None", "None"},
        {" D-1000 ",            " D-1000 ",            "BDWClass8Message",      "Cell",    "None", "None"}
    },
    {
        {" S-Knife ",           " S-Knife ",           "SMClass1Message",       "None",    "None", "None"},
        {" S-Enforcer ",        " S-Enforcer ",        "SMClass2Message",       "Clip",    "None", "None"},
        {" S-Shotgun ",         " S-Shotgun ",         "SMClass3Message",       "Shell",   "None", "None"},
        {" S-Chaingun ",        " S-Chaingun ",        "SMClass4Message",       "Clip",    "None", "None"},
        {" S-Cluster Bomber ",  " S-Cluster Bomber ",  "SMClass5Message",       "RocketAmmo", "None", "None"},
        {" S-Plasma Beam ",     " S-Plasma Beam ",     "SMClass6Message",       "Cell",    "None", "None"},
        {" Y23H ",              " Y23H ",              "SMClass7Message",        "Cell",   "None", "None"},
        {" S-Ionstrike ",       " S-Ionstrike ",       "SMClass8Message",       "Cell",    "None", "None"}
    },
    {
        {" J-Fists ",           " J-Fists ",           "JKEGuyClass1Message",   "None",    "None", "None"},
        {" J-Pistol ",          " J-Pistol ",          "JKEGuyClass2Message",   "Clip",    "None", "None"},
        {" J-Shotgun ",         " J-Super Shotgun ",   "JKEGuyClass3Message",   "Shell",   "None", "None"},
        {" J-Uzi ",             " Heavy Chaingun ",    "JKEGuyClass4Message",   "Clip",    "None", "None"},
        {" J-Rocket Launcher ", " Fragment Launcher ", "JKEGuyClass5Message",   "RocketAmmo", "ExplosiveAmmo", "None"},
        {" J-Plasma Rifle ",    " Karasawa ",          "JKEGuyClass6Message",   "Cell",    "None", "None"},
        {" Molecule Shooter ",  " Molecule Shooter ",  "JKEGuyClass7Message",   "Cell",    "None", "None"},
        {" BFG7000 ",           " BFG7000 ",           "JKEGuyClass8Message",   "Cell",    "None", "None"}
    },
    {
        {" L-Ripper ",          " Ripper ",            "LeandroClass1Message",  "None",    "None", "None"},
        {" L-Dual Pistols ",    " L-Dual Pistols ",    "LeandroClass2Message",  "Clip",    "None", "None"},
        {" L-Striker ",         " L-Quadshot ",        "LeandroClass3Message",  "Shell",   "None", "None"},
        {" L-Spitfirer ",       " L-Minigun ",         "LeandroClass4Message",  "Clip",    "MinigunAmmo", "ExplosiveAmmo"},
        {" L-Multigun ",        " L-Multigun ",        "LeandroClass5Message",  "ExplosiveAmmo", "None", "None"},
        {" L-Plasma Driver ",   " L-PlasmaDriver ",    "LeandroClass6Message",  "Cell",    "None", "None"},
        {" Rail Repeater ",     " Rail Repeater ",     "LeandroClass7Message",  "Cell",    "None", "None"},
        {" Powerful ",          " Powerful ",          "LeandroClass8Message",  "GravityAmmo", "None", "None"}
    },
    {
        {" Hellfist ",          " Hellfist ",          "SorcererClass1Message", "None",    "None", "None"},
        {" Tri-Staff ",         " Tri-Staff ",         "SorcererClass2Message", "JKEMana", "None", "None"},
        {"None",                "None",                "SorcererClass3Message", "JKEMana", "None", "None"},
        {"None",                "None",                "SorcererClass4Message", "JKEMana", "None", "None"},
        {" Black Magic ",       " Black Magic ",       "SorcererClass5Message", "JKEMana", "None", "None"},
        {" Fire Gloves ",       " Fire Gloves ",       "SorcererClass6Message", "FireAmmo", "JKEMana", "None"},
        {"None",                "None",                "SorcererClass7Message", "JKEMana", "None", "None"},
        {"None",                "None",                "SorcererClass8Message", "JKEMana", "None", "None"}
    }
};
