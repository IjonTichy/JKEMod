#include "zcommon.acs"
#library "chaingunRecoil"


script 474 (int recoilInt, int recoilFrac)
{
    int recoil = (recoilInt << 16) + ((recoilFrac << 16) / 100);

    int angle = GetActorAngle(0);
    int pitch = GetActorPitch(0);
    int bAngle = angle >> 8;

    //Print(f:angle, s:" ", d:bAngle);

    int hM = FixedMul(recoil, cos(pitch) ) >> 16;
    int vM = (FixedMul(recoil, -sin(pitch) ) >> 16) * 4;

    ThrustThing(bAngle, -hM, 1, 0);
    ThrustThingZ(0, vM, 1, 1);
}
