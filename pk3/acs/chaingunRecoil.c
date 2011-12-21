#include "zcommon.acs"
#library "chaingunRecoil"


script 474 (int recoilInt, int recoilFrac)
{
    int recoil = (recoilInt << 16) + ((recoilFrac << 16) / 100);

    int angle = GetActorAngle(0);
    int pitch = GetActorPitch(0);

    int dx = FixedMul(cos(angle), recoil);
        dx = -FixedMul(dx, cos(pitch));
    
    int dy = FixedMul(sin(angle), recoil);
        dy = -FixedMul(dy, cos(pitch));

    int dz = FixedMul(sin(pitch), recoil);

    SetActorVelocity(0, dx, dy, dz, 1, 1);
}
