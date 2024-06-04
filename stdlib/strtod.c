/*
 * strtod.c --
 *
 *	Source code for the "strtod" library procedure.
 *
 * Copyright (c) 1988-1993 The Regents of the University of California.
 * Copyright (c) 1994 Sun Microsystems, Inc.
 *
 * Permission to use, copy, modify, and distribute this
 * software and its documentation for any purpose and without
 * fee is hereby granted, provided that the above copyright
 * notice appear in all copies.  The University of California
 * makes no representations about the suitability of this
 * software for any purpose.  It is provided "as is" without
 * express or implied warranty.
 *
 * RCS: @(#) $Id$
 *
 * Originally Taken from http://svn.ruby-lang.org/repos/ruby/branches/ruby_1_8/missing/strtod.c
 */

/* Modified for MiNTLib by Thorsten Otto. */

/* Configuration part.  These macros are defined by `strtold.c',
   `strtof.c', `wcstod.c', `wcstold.c', and `wcstof.c' to produce the
   `long double' and `float' versions of the reader.  */
#ifndef FLOAT_TYPE
#define FLOAT_TYPE 1
#endif
/* End of configuration part.  */

#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <ieee754.h>
#include <locale.h>

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif
#ifndef NULL
#define NULL 0
#endif


/* We use this code also for the extended locale handling where the
   function gets as an additional argument the locale which has to be
   used.  To access the values we have to redefine the _NL_CURRENT
   macro.  */
#ifdef USE_IN_EXTENDED_LOCALE_MODEL
#undef _NL_CURRENT
#define _NL_CURRENT(category, item) \
  (current->values[_NL_ITEM_INDEX (item)].string)
#define LOCALE_PARAM_DECL , __locale_t loc
#define LOCALE_PARAM , loc
#else
#define LOCALE_PARAM_DECL
#define LOCALE_PARAM
#endif

#ifndef __MINT__
#if defined _LIBC || defined HAVE_WCHAR_H
#include <wchar.h>
#endif
#else
#define __strtoull_internal(s, p, b, f) strtoull (s, p, b)
#define __strncasecmp strncasecmp
#endif

#ifdef USE_WIDE_CHAR
#include <wctype.h>
#define STRING_TYPE wchar_t
#define CHAR_TYPE wchar_t
#define L_(Ch) L##Ch
#ifdef USE_IN_EXTENDED_LOCALE_MODEL
#define ISSPACE(Ch) __iswspace_l ((Ch), loc)
#define ISDIGIT(Ch) __iswdigit_l ((Ch), loc)
#define ISXDIGIT(Ch) __iswxdigit_l ((Ch), loc)
#define TOLOWER(Ch) __towlower_l ((Ch), loc)
#define STRNCASECMP(S1, S2, N) __wcsncasecmp_l ((S1), (S2), (N), loc)
#define STRTOULL(S, E, B) ____wcstoull_l_internal ((S), (E), (B), 0, loc)
#else
#define ISSPACE(Ch) iswspace (Ch)
#define ISDIGIT(Ch) iswdigit (Ch)
#define ISXDIGIT(Ch) iswxdigit (Ch)
#define TOLOWER(Ch) towlower (Ch)
#define STRNCASECMP(S1, S2, N) __wcsncasecmp ((S1), (S2), (N))
#define STRTOULL(S, E, B) __wcstoull_internal ((S), (E), (B), 0)
#endif
#else
#define STRING_TYPE char
#define CHAR_TYPE unsigned char
#define L_(Ch) Ch
#ifdef USE_IN_EXTENDED_LOCALE_MODEL
#define ISSPACE(Ch) __isspace_l ((Ch), loc)
#define ISDIGIT(Ch) __isdigit_l ((Ch), loc)
#define ISXDIGIT(Ch) __isxdigit_l ((Ch), loc)
#define TOLOWER(Ch) __tolower_l ((Ch), loc)
#define STRNCASECMP(S1, S2, N) __strncasecmp_l ((S1), (S2), (N), loc)
#define STRTOULL(S, E, B) ____strtoull_l_internal ((S), (E), (B), 0, loc)
#else
#define ISSPACE(Ch) ((Ch) == '\n' || (Ch) == '\r' || (Ch) == '\v' || (Ch) == '\f' || (Ch) == ' ')
#define ISDIGIT(Ch) ((Ch) >= '0' && (Ch) <= '9')
#define ISXDIGIT(Ch) isxdigit (Ch)
#define TOLOWER(Ch) tolower (Ch)
#define STRNCASECMP(S1, S2, N) __strncasecmp ((S1), (S2), (N))
#define STRTOULL(S, E, B) __strtoull_internal ((S), (E), 0, (B))
#endif
#endif


/* Constants we need from float.h; select the set for the FLOAT precision.  */
#if FLOAT_TYPE == 0
/* Convert a multi-precision integer of the needed number of bits (24 for
   float) and an integral power of two to a `float' in IEEE754 single-
   precision format.  */

# define FLOAT		float

# define FC(x)      x ## F
# define MANT_DIG	__FLT_MANT_DIG__
# define DIG		__FLT_DIG__
# define MAX_EXP	__FLT_MAX_EXP__
# define MIN_EXP	__FLT_MIN_EXP__
# define MAX_10_EXP	__FLT_MAX_10_EXP__
# define MIN_10_EXP	__FLT_MIN_10_EXP__
# define FLOAT_HUGE_VAL	__builtin_inff()
# define FLOAT_NAN_VAL	__builtin_nanf("")
# ifdef USE_IN_EXTENDED_LOCALE_MODEL
#  define STRTOF		__strtof_l
# else
#  define STRTOF		strtof
# endif
# define SET_NAN_MANTISSA(flt, mant) \
  do { union ieee754_float u;						      \
       u.f = (flt);							      \
       if ((mant & 0x7fffff) == 0)					      \
	 mant = 0x400000;						      \
       u.ieee.mantissa = (mant) & 0x7fffff;				      \
       (flt) = u.f;							      \
  } while (0)
#elif FLOAT_TYPE == 1 || __DBL_MANT_DIG__ == __LDBL_MANT_DIG__

# define FLOAT		double

# define FC(x)      x
# define MANT_DIG	__DBL_MANT_DIG__
# define DIG		__DBL_DIG__
# define MAX_EXP	__DBL_MAX_EXP__
# define MIN_EXP	__DBL_MIN_EXP__
# define MAX_10_EXP	__DBL_MAX_10_EXP__
# define MIN_10_EXP	__DBL_MIN_10_EXP__
# define FLOAT_HUGE_VAL	__builtin_inf()
# define FLOAT_NAN_VAL	__builtin_nan("")
# ifdef USE_IN_EXTENDED_LOCALE_MODEL
#  define STRTOF	__strtod_l
# else
#  define STRTOF	strtod
# endif
#define SET_NAN_MANTISSA(flt, mant) \
  do { union ieee754_double u;						      \
       u.d = (flt);							      \
       if ((mant & 0xfffffffffffffULL) == 0)				      \
	 mant = 0x8000000000000ULL;					      \
       u.ieee.mantissa0 = ((mant) >> 32) & 0xfffff;			      \
       u.ieee.mantissa1 = (mant) & 0xffffffff;				      \
       (flt) = u.d;							      \
  } while (0)
#elif FLOAT_TYPE == 2

# define FLOAT		long double

# define FC(x)      x ## L
# define MANT_DIG	__LDBL_MANT_DIG__
# define DIG		__LDBL_DIG__
# define MAX_EXP	__LDBL_MAX_EXP__
# define MIN_EXP	__LDBL_MIN_EXP__
# define MAX_10_EXP	__LDBL_MAX_10_EXP__
# define MIN_10_EXP	__LDBL_MIN_10_EXP__
# define FLOAT_HUGE_VAL	__builtin_infl()
# define FLOAT_NAN_VAL	__builtin_nanl("")
# ifdef USE_IN_EXTENDED_LOCALE_MODEL
#  define STRTOF	__strtold_l
# else
#  define STRTOF	strtold
# endif
# define SET_NAN_MANTISSA(flt, mant) \
  do { union ieee854_long_double u;					      \
       u.d = (flt);							      \
       if ((mant & 0x7fffffffffffffffULL) == 0)				      \
	 mant = 0x4000000000000000ULL;					      \
       u.ieee.mantissa0 = (((mant) >> 32) & 0x7fffffff) | 0x80000000;	      \
       u.ieee.mantissa1 = (mant) & 0xffffffff;				      \
       (flt) = u.d;							      \
  } while (0)
#else
# error "unsupported float"
#endif

#if MANT_DIG >= 31
typedef unsigned long long mant_t;
#elif __INT_MAX__ >= 0x7fffffffL
typedef unsigned int mant_t;
#else
typedef unsigned long mant_t;
#endif



static FLOAT const powersOf10[] = {			/* Table giving binary powers of 10.  Entry */
	FC(1.0e1),								/* is 10^2^i.  Used to convert decimal */
	FC(1.0e2),								/* exponents into floating-point numbers. */
	FC(1.0e4),
	FC(1.0e8),
	FC(1.0e16),
	FC(1.0e32),
#if MAX_10_EXP >= 64
	FC(1.0e64),
	FC(1.0e128),
	FC(1.0e256),
#endif
#if MAX_10_EXP >= 512
	FC(1.0e512),
	FC(1.0e1024),
	FC(1.0e2048),
	FC(1.0e4096),
#endif
};

#define INTERNAL(x) INTERNAL1(x)
#define INTERNAL1(x) __##x##_internal

FLOAT INTERNAL (STRTOF) (const STRING_TYPE *nptr, STRING_TYPE **endptr, int group LOCALE_PARAM_DECL);

/*
 *----------------------------------------------------------------------
 *
 * strtod --
 *
 *	This procedure converts a floating-point number from an ASCII
 *	decimal representation to internal double-precision format.
 *
 * Results:
 *	The return value is the double-precision floating-point
 *	representation of the characters in string.  If endPtr isn't
 *	NULL, then *endPtr is filled in with the address of the
 *	next character after the last one that was part of the
 *	floating-point number.
 *
 * Side effects:
 *	None.
 *
 *----------------------------------------------------------------------
 */
/* A decimal ASCII floating-point number,
 * optionally preceded by white space.
 * Must have form "-I.FE-X", where I is the
 * integer part of the mantissa, F is the
 * fractional part of the mantissa, and X
 * is the exponent.  Either of the signs
 * may be "+", "-", or omitted.  Either I
 * or F may be omitted, or both.  The decimal
 * point isn't necessary unless F is present.
 * The "E" may actually be an "e".  E and X
 * may both be omitted (but not just one).
 */
FLOAT INTERNAL (STRTOF) (const STRING_TYPE *string, STRING_TYPE **endptr, int group LOCALE_PARAM_DECL)
{
	int sign;
	int expSign;
	FLOAT fraction;
	FLOAT dblExp;
	const FLOAT *d;
	const STRING_TYPE *p;
	CHAR_TYPE c;
	int exp;							/* Exponent read from "EX" field. */
	int fracExp;						/* Exponent that derives from the fractional
										 * part.  Under normal circumstatnces, it is
										 * the negative of the number of digits in F.
										 * However, if I is very long, the last digits
										 * of I get dropped (otherwise a long I with a
										 * large negative exponent could cause an
										 * unnecessary overflow on I alone).  In this
										 * case, fracExp is incremented one for each
										 * dropped digit. */
	int mantSize;						/* Number of digits in mantissa. */
	int decPt;							/* Number of mantissa digits BEFORE decimal
										 * point. */
	const char *pExp;					/* Temporarily holds location of exponent
										 * in string. */
	/*
	 * Strip off leading blanks and check for a sign.
	 */
	p = string;
	while (ISSPACE(*p))
	{
		p += 1;
	}
	if (*p == '-')
	{
		sign = TRUE;
		p += 1;
	} else
	{
		if (*p == '+')
		{
			p += 1;
		}
		sign = FALSE;
	}
	/*
	 * Count the number of digits in the mantissa (including the decimal
	 * point), and also locate the decimal point.
	 */
	decPt = -1;
	for (mantSize = 0;; mantSize += 1)
	{
		c = *p;
		if (!ISDIGIT(c))
		{
			if (c != '.' || decPt >= 0)
			{
				break;
			}
			decPt = mantSize;
		}
		p += 1;
	}
	/*
	 * Now suck up the digits in the mantissa.  Use two integers to
	 * collect 9 digits each (this is faster than using floating-point).
	 * If the mantissa has more than 18 digits, ignore the extras, since
	 * they can't affect the value anyway.
	 */

	pExp = p;
	p -= mantSize;
	if (decPt < 0)
	{
		decPt = mantSize;
	} else
	{
		mantSize -= 1;					/* One of the digits was the point. */
	}
	fracExp = decPt - mantSize;
	if (mantSize == 0)
	{
		fraction = 0.0;
		p = string;
		goto done;
	} else
	{
		long frac1;
		mant_t frac2;

		frac1 = 0;
		for (; mantSize > 9; mantSize -= 1)
		{
			c = *p;
			p += 1;
			if (c == '.')
			{
				c = *p;
				p += 1;
			}
			frac1 = 10 * frac1 + (c - '0');
		}
		frac2 = 0;
		for (; mantSize > 0; mantSize -= 1)
		{
			c = *p;
			p += 1;
			if (c == '.')
			{
				c = *p;
				p += 1;
			}
			frac2 = 10 * frac2 + (c - '0');
		}
		fraction = (1.0e9 * frac1) + frac2;
	}
	/*
	 * Skim off the exponent.
	 */
	exp = 0;
	expSign = FALSE;
	p = pExp;
	if (*p == 'E' || *p == 'e')
	{
		p += 1;
		if (*p == '-')
		{
			expSign = TRUE;
			p += 1;
		} else
		{
			if (*p == '+')
			{
				p += 1;
			}
		}
		for (;;)
		{
			c = *p;
			if (!ISDIGIT(c))
				break;
			exp = exp * 10 + (*p - '0');
			p += 1;
			if (exp > MAX_10_EXP)
			{
				/* Accept all following digits as part of the exponent.  */
				for (;;)
				{
					c = *p;
					if (!ISDIGIT(c))
						break;
				}
				errno = ERANGE;
				if (endptr != NULL)
				{
					*endptr = (STRING_TYPE *) p;
				}
				return sign ? -FLOAT_HUGE_VAL : FLOAT_HUGE_VAL;
			}
		}
	}
	if (expSign)
	{
		exp = fracExp - exp;
	} else
	{
		exp = fracExp + exp;
	}
	/*
	 * Generate a floating-point number that represents the exponent.
	 * Do this by processing the exponent one bit at a time to combine
	 * many powers of 2 of 10. Then combine the exponent with the
	 * fraction.
	 */

	if (exp < 0)
	{
		expSign = TRUE;
		exp = -exp;
	} else
	{
		expSign = FALSE;
	}
	dblExp = 1.0;
	for (d = powersOf10; exp != 0; exp >>= 1, d += 1)
	{
		if (exp & 01)
		{
			dblExp *= *d;
		}
	}
	if (expSign)
	{
		fraction /= dblExp;
	} else
	{
		fraction *= dblExp;
	}
  done:
	if (endptr != NULL)
	{
		*endptr = (STRING_TYPE *) p;
	}
	if (sign)
	{
		return -fraction;
	}
	return fraction;
}

/* External user entry point.  */

FLOAT
#ifdef weak_function
weak_function
#endif
STRTOF (const STRING_TYPE *nptr, STRING_TYPE **endptr LOCALE_PARAM_DECL)
{
	return INTERNAL (STRTOF) (nptr, endptr, 0 LOCALE_PARAM);
}
