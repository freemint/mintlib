/*  s_isnanf.c -- MiNTLib.
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

#undef __isnanf
#undef isnanf

int
__isnanf (value)
     float value;
{
  union ieee754_float u;
  
  u.f = value;
  
  return ((u.ieee.exponent & 0xff) == 0xff && 
          (u.ieee.mantissa & 0x7fffff) != 0);
}

weak_alias (__isnanf, isnanf)
