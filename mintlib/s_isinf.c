/*  s_isinf.c -- MiNTLib.
    Copyright (C) 2000 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

/* FIXME: Please check if this is correct!  */

#include <math.h>
#include <ieee754.h>

#undef __isinf
#undef isinf

int
__isinf (value)
      double value;
{
  union ieee754_double u;
  
  u.d = value;
  
  if ((u.ieee.exponent & 0x7ff) == 0x7ff && 
      (u.ieee.mantissa0 & 0xfffff) == 0 && u.ieee.mantissa1 == 0)
    return u.ieee.negative ? -1 : 1;
  
  return 0;
}

weak_alias (__isinf, isinf)
