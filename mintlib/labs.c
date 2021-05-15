/* return absolute values */
#include <stdlib.h>

#ifdef labs
#undef labs
#endif

#ifdef __MSHORT__
long
labs(long x)
{
  return x < 0 ? -x : x;
}
#else
strong_alias(abs, labs)
#endif
