#include "zcommon.acs"
#library "chaingunRecoil"

function int canJump(void)
{
    return !GetCVar("sv_nojump");
}


script 474 (int recoilInt, int recoilFrac)
{
    int dx; int dy; int dz;
    int jump = canJump();
    int recoil = (recoilInt << 16) + ((recoilFrac << 16) / 100);

    int angle = GetActorAngle(0);
    int pitch = GetActorPitch(0);
    
    if (jump)
    {
        dx = FixedMul(cos(angle), recoil);
        dx = -FixedMul(dx, cos(pitch));
        
        dy = FixedMul(sin(angle), recoil);
        dy = -FixedMul(dy, cos(pitch));
    
        dz = FixedMul(sin(pitch), recoil);
    }
    else
    {
        dx = -FixedMul(cos(angle), recoil);
        dy = -FixedMul(sin(angle), recoil);
        dz = 0;
    }

    SetActorVelocity(0, dx, dy, dz, 1, 1);
}
