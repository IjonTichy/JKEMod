#include "zcommon.acs"
#library "instantswitch"

function int sqrt(int number)
{
  if (number == 1.0) return 1.0;
  if (number <= 0) return 0;
  int val = 150.0;
  for (int i=0; i<15; i++)
    val = (val + FixedDiv(number, val)) >> 1;

  return val;
}

script 583 (int x, int y, int z)
{
    SetResultValue(sqrt(x*X + y*y + z*z) );
}

script 584 (int take)
{
    SetActivatorToTarget(0);

    int ret = CheckInventory("QuakeCell");
    SetResultValue(ret);

    if (take == 1)
    {
        TakeInventory("QuakeCell", ret);
    }
}
