/*  s_isnanl.c -- MiNTLib.
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

#undef __isnanl
#undef isnanl

int
__isnanl (value)
     long double value;
{
  union ieee854_long_double u;
  
  u.d = value;
  
  return ((u.ieee.exponent & 0x7fff) == 0x7fff && 
          ((u.ieee.mantissa0 & 0x7fffffff) != 0 || u.ieee.mantissa1 != 0));
}

weak_alias (__isnanl, isnanl)
