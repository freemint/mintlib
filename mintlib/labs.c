/* return absolute values */
#include <stdlib.h>

#ifdef labs
#undef labs
#endif

long
labs(x)
  long x;
{
  return x < 0 ? -x : x;
}
