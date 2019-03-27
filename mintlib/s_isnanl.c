/* s_isnanl.c -- long double version of s_isnan.c.
 * Conversion to long double by Jakub Jelinek, jj@ultra.linux.cz.
 */

/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */

/*
 * isnanl(x) returns 1 is x is nan, else 0;
 * no branching!
 */

#include "math.h"
#include "math_private.h"

#ifndef NO_LONG_DOUBLE
int
__isnanl (long double x)
{
	int32_t se, hx, lx;

	GET_LDOUBLE_WORDS(se, hx, lx, x);
	se = (se & 0x7fff) << 1;
	lx |= hx & 0x7fffffffL;
	se |= (uint32_t) (lx | (-lx)) >> 31;
	se = 0xfffe - se;
	return (int) (((uint32_t) (se)) >> 31);
}
weak_alias (__isnanl, isnanl)
#endif
