#define CLASSCOUNT 6
#define SLOTCOUNT  16
#define WEPCOUNT 1

int classWeps[CLASSCOUNT][SLOTCOUNT][WEPCOUNT+3] =
{
    {
        {" B-Fists ",           "BDWClass1Message",      "None", "None"},
        {" B-Chainsaw ",        "BDWClass1Message2",     "None", "None"},

        {" B-Pistol ",          "BDWClass2Message",      "Clip", "None"},
        {" B-Pistols ",         "BDWClass2Message2",     "Clip", "None"},

        {" B-Shotgun ",         "BDWClass3Message",      "Shell", "None"},
        {" B-Super Shotgun ",   "BDWClass3Message2",     "Shell", "None"},

        {" B-Chaingun ",        "BDWClass4Message",      "Clip", "None"},
        {" B-Chaingun ",        "BDWClass4Message",      "Clip", "None"},

        {" B-Rocket Launcher ", "BDWClass5Message",      "RocketAmmo", "None"},
        {" B-Rocket Launcher ", "BDWClass5Message",      "RocketAmmo", "None"},

        {" B-Plasma Rifle ",    "BDWClass6Message",      "Cell", "None"},
        {" B-Plasma Rifle ",    "BDWClass6Message",      "Cell", "None"},

        {" B-BFG9000 ",         "BDWClass7Message",      "Cell", "None"},
        {"None",                "None",                  "None", "None"},

        {" D-1000 ",            "BDWClass8Message",      "Cell", "None"},
        {"None",                "None",                  "None", "None"},

    },
    {
        {" S-Knife ",           "SMClass1Message",       "None", "None"},
        {"None",                "None",                  "None", "None"},

        {" S-Enforcer ",        "SMClass2Message",       "Clip", "None"},
        {" S-Enforcer ",        "SMClass2Message",       "Clip", "None"},

        {" S-Shotgun ",         "SMClass3Message",       "Shell", "None"},
        {" S-Shotgun ",         "SMClass3Message",       "Shell", "None"},

        {" S-Chaingun ",        "SMClass4Message",       "Clip", "None"},
        {" S-Chaingun ",        "SMClass4Message",       "Clip", "None"},

        {" S-Cluster Bomber ",  "SMClass5Message",       "RocketAmmo", "None"},
        {" S-Cluster Bomber ",  "SMClass5Message",       "RocketAmmo", "None"},

        {" S-Plasma Beam ",     "SMClass6Message",       "Cell", "None"},
        {" S-Plasma Beam ",     "SMClass6Message",       "Cell", "None"},

        {" Y23H ",              "SMClass7Message",       "Cell", "None"},
        {"None",                "None",                  "None", "None"},

        {" S-Ionstrike ",       "SMClass8Message",       "Cell", "None"},
        {"None",                "None",                  "None", "None"},
    },
    {
        {" J-Fists ",           "JKEGuyClass1Message",   "None", "None"},
        {"None",                "None",                  "None", "None"},

        {" J-Pistol ",          "JKEGuyClass2Message",   "Clip", "None"},
        {" J-Pistol ",          "JKEGuyClass2Message",   "Clip", "None"},

        {" J-Shotgun ",         "JKEGuyClass3Message",   "Shell", "None"},
        {" J-Super Shotgun ",   "JKEGuyClass3Message2",  "Shell", "None"},

        {" J-Uzi ",             "JKEGuyClass4Message",   "Clip", "None"},
        {" Heavy Chaingun ",    "JKEGuyClass4Message2",  "Clip", "None"},

        {" J-Rocket Launcher ", "JKEGuyClass5Message",   "RocketAmmo", "None"},
        {" Fragment Launcher ", "JKEGuyClass5Message2",  "ExplosiveAmmo", "None"},

        {" J-Plasma Rifle ",    "JKEGuyClass6Message",   "Cell", "None"},
        {" Karasawa ",          "JKEGuyClass6Message2",  "Cell", "None"},

        {" Molecule Shooter ",  "JKEGuyClass7Message",   "Cell", "None"},
        {"None",                "None",                  "None", "None"},

        {" BFG7000 ",           "JKEGuyClass8Message",   "Cell",    "None"},
        {"None",                "None",                  "None", "None"},
    },
    {
        {"None",                "None",                  "None", "None"},
        {" L-Ripper ",          "LeandroClass1Message",  "None", "None"},

        {" Dual Berettas ",     "LeandroClass2Message",  "Clip", "None"},
        {" Dual Berettas ",     "LeandroClass2Message",  "Clip", "None"},

        {" L-Striker ",         "LeandroClass3Message",  "Shell", "None"},
        {" L-Quadshot ",        "LeandroClass3Message2", "Shell", "None"},

        {" L-Spitfirer ",       "LeandroClass4Message",  "Clip", "ExplosiveAmmo"},
        {" L-Minigun ",         "LeandroClass4Message2", "MinigunAmmo", "None"},

        {" L-Multigun ",        "LeandroClass5Message",  "ExplosiveAmmo", "None"},
        {" L-Multigun ",        "LeandroClass5Message",  "ExplosiveAmmo", "None"},

        {" L-Plasma Driver ",   "LeandroClass6Message",  "Cell", "None"},
        {" L-Plasma Driver ",   "LeandroClass6Message",  "Cell", "None"},

        {" Rail Repeater ",     "LeandroClass7Message",  "Cell", "None"},
        {"None",                "None",                  "None", "None"},

        {" Powerful ",          "LeandroClass8Message",  "GravityAmmo", "None"},
        {"None",                "None",                  "None", "None"},
    },
    {
        {" Hellfist ",          "SorcererClass1Message", "None", "None"},
        {"None",                "None",                  "None", "None"},

        {" Sapphire Wand ",     "SorcererClass2Message", "JKEMana", "None"},
        {" Sapphire Wand ",     "SorcererClass2Message", "JKEMana", "None"},

        {" Ethereal Crossbow ", "SorcererClass3Message", "EtherealAmmo", "None"},
        {" Ethereal Crossbow ", "SorcererClass3Message", "EtherealAmmo", "None"},

        {" Tri-Staff ",         "SorcererClass4Message", "JKEMana", "None"},
        {" Tri-Staff ",         "SorcererClass4Message", "JKEMana", "None"},

        {" Black Magic ",       "SorcererClass5Message", "JKEMana", "None"},
        {"None",                "None",                  "None", "None"},

        {" Wand of Flames ",    "SorcererClass6Message", "FlameAmmo", "None"},
        {"None",                "None",                  "None", "None"},

        {" Fire Gloves ",       "SorcererClass7Message", "FireAmmo", "JKEMana"},
        {"None",                "None",                  "None", "None"},

        {" Skeleton Orb ",      "SorcererClass8Message", "JKEMana", "None"},
        {"None",                "None",                  "None", "None"},
    },
    {
        {" Quake Fist ",        "QuakeClass1Message", "None", "None"},
        {"None",                "None",               "None", "None"},

        {" Quake SG ",          "QuakeClass2Message", "QuakeShell", "None"},
        {" Quake SG ",          "QuakeClass2Message", "QuakeShell", "None"},

        {" Quake SSG ",         "QuakeClass4Message", "QuakeShell", "None"},
        {" Quake NG ",          "QuakeClass3Message", "QuakeNails", "None"},

        {" Quake SNG ",         "QuakeClass5Message", "QuakeNails", "None"},
        {" Quake SNG ",         "QuakeClass5Message", "QuakeNails", "None"},

        {" Quake RL ",          "QuakeClass7Message", "QuakeExplosive", "None"},
        {" Quake RL ",          "QuakeClass7Message", "QuakeExplosive", "None"},

        {" Quake GL ",          "QuakeClass6Message", "QuakeExplosive", "None"},
        {" Quake GL ",          "QuakeClass6Message", "QuakeExplosive", "None"},

        {" Quake LG ",          "QuakeClass8Message", "QuakeCell", "JKEMana"},
        {" Quake LG ",          "QuakeClass8Message", "QuakeCell", "None"},

        {"None",                "None",               "None", "None"},
        {"None",                "None",               "None", "None"},
    },
};
