/*  s_isinff.c -- MiNTLib.
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

#undef __isinff
#undef isinff

int
__isinff (value)
     float value;
{
  union ieee754_float u;
  
  u.f = value;
  
  if ((u.ieee.exponent & 0xff) == 0xff && 
      (u.ieee.mantissa & 0x7fffff) == 0)
    return u.ieee.negative ? -1 : 1;
  
  return 0;
}

weak_alias (__isinff, isinff)
