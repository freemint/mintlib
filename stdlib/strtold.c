#ifdef __MINT__
# define DENORM_EXP (MIN_EXP - 1)
#endif

#include "math_private.h"

#if !defined(__NO_LONG_DOUBLE_MATH) && !defined(__mcoldfire__)
/* The actual implementation for all floating point sizes is in strtod.c.
   These macros tell it to produce the `long double' version, `strtold'.  */

# define FLOAT_TYPE 2
# include "strtod.c"

#else
# include <stdlib.h>

double __strtod_internal (const char *nptr, char **endptr, int group);
long double __strtold_internal (const char *nptr, char **endptr, int group);

/* There is no `long double' type, use the `double' implementations.  */
long double
__strtold_internal (const char *nptr, char **endptr, int group)
{
  return __strtod_internal (nptr, endptr, group);
}

long double
strtold (const char *nptr, char **endptr)
{
  return __strtod_internal (nptr, endptr, 0);
}
#endif
