/* return absolute values */
#include <stdlib.h>

#ifdef abs
#undef abs
#endif

int abs(x)
  int x;
{
  return x < 0 ? -x : x;
}
