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
        {" B-Fists ",           "None",                 "BDWClass1Message",      "None",    "None", "None"},
        {" B-Pistol ",          "None",                 "BDWClass2Message",      "Clip",    "None", "None"},
        {" B-Shotgun ",         " B-Super Shotgun ",    "BDWClass3Message",      "Shell",   "None", "None"},
        {" B-Chaingun ",        "None",                 "BDWClass4Message",      "Clip",    "None", "None"},
        {" B-Rocket Launcher ", "None",                 "BDWClass5Message",      "RocketAmmo", "None", "None"},
        {" B-Plasma Rifle ",    "None",                 "BDWClass6Message",      "Cell",    "None", "None"},
        {" B-BFG9000 ",         "None",                 "BDWClass7Message",      "Cell",    "None", "None"},
        {" D-1000 ",            "None",                 "BDWClass8Message",      "Cell",    "None", "None"}
    },
    {
        {" S-Knife ",           "None",                 "SMClass1Message",       "None",    "None", "None"},
        {" S-Enforcer ",        "None",                 "SMClass2Message",       "Clip",    "None", "None"},
        {" S-Shotgun ",         "None",                 "SMClass3Message",       "Shell",   "None", "None"},
        {" S-Chaingun ",        "None",                 "SMClass4Message",       "Clip",    "None", "None"},
        {" S-Cluster Bomber ",  "None",                 "SMClass5Message",       "RocketAmmo", "None", "None"},
        {" S-Plasma Beam ",     "None",                 "SMClass6Message",       "Cell",    "None", "None"},
        {" Y23H ",              "None",                 "SMClass7Message",       "Cell",    "None", "None"},
        {" S-Ionstrike ",       "None",                 "SMClass8Message",       "Cell",    "None", "None"}
    },
    {
        {" J-Fists ",           "None",                 "JKEGuyClass1Message",   "None",    "None", "None"},
        {" J-Pistol ",          "None",                 "JKEGuyClass2Message",   "Clip",    "None", "None"},
        {" J-Shotgun ",         " J-Super Shotgun ",    "JKEGuyClass3Message",   "Shell",   "None", "None"},
        {" J-Uzi ",             " Heavy Chaingun ",     "JKEGuyClass4Message",   "Clip",    "None", "None"},
        {" J-Rocket Launcher ", " Fragment Launcher ",  "JKEGuyClass5Message",   "RocketAmmo", "ExplosiveAmmo", "None"},
        {" J-Plasma Rifle ",    " Karasawa ",           "JKEGuyClass6Message",   "Cell",    "None", "None"},
        {" Molecule Shooter ",  "None",                 "JKEGuyClass7Message",   "Cell",    "None", "None"},
        {" BFG7000 ",           "None",                 "JKEGuyClass8Message",   "Cell",    "None", "None"}
    },
    {
        {" L-Ripper ",          "None",                 "LeandroClass1Message",  "None",    "None", "None"},
        {" L-Dual Pistols ",    "None",                 "LeandroClass2Message",  "Clip",    "None", "None"},
        {" L-Striker ",         "None",                 "LeandroClass3Message",  "Shell",   "None", "None"},
        {" L-Spitfirer ",       "None",                 "LeandroClass4Message",  "Clip",    "MinigunAmmo", "ExplosiveAmmo"},
        {" L-Multigun ",        "None",                 "LeandroClass5Message",  "ExplosiveAmmo", "None", "None"},
        {" L-Plasma Driver ",   "None",                 "LeandroClass6Message",  "Cell",    "None", "None"},
        {" Rail Repeater ",     "None",                 "LeandroClass7Message",  "Cell",    "None", "None"},
        {" Powerful ",          "None",                 "LeandroClass8Message",  "GravityAmmo", "None", "None"}
    },
    {
        {" Hellfist ",          "None",                 "SorcererClass1Message", "None",    "None", "None"},
        {" Tri-Staff ",         "None",                 "SorcererClass2Message", "JKEMana", "None", "None"},
        {" Ethereal Crossbow ", "None",                 "SorcererClass3Message", "EtherealAmmo", "None", "None"},
        {" Tri-Staff ",         "None",                 "SorcererClass4Message", "JKEMana", "None", "None"},
        {" Black Magic ",       "None",                 "SorcererClass5Message", "JKEMana", "None", "None"},
        {" Fire Gloves ",       "None",                 "SorcererClass6Message", "FireAmmo", "JKEMana", "None"},
        {"None",                "None",                 "SorcererClass7Message", "JKEMana", "None", "None"},
        {"None",                "None",                 "SorcererClass8Message", "JKEMana", "None", "None"}
    }
};
