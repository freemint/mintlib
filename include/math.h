#ifndef _MATH_H
#define _MATH_H 1

/************************************************************************
 *									*
 *				N O T I C E				*
 *									*
 *			Copyright Abandoned, 1987, Fred Fish		*
 *									*
 *	This previously copyrighted work has been placed into the	*
 *	public domain by the author (Fred Fish) and may be freely used	*
 *	for any purpose, private or commercial.  I would appreciate	*
 *	it, as a courtesy, if this notice is left in all copies and	*
 *	derivative works.  Thank you, and enjoy...			*
 *									*
 *	The author makes no warranty of any kind with respect to this	*
 *	product and explicitly disclaims any implied warranties of	*
 *	merchantability or fitness for any particular purpose.		*
 *									*
 ************************************************************************
 */

/*
 *  FILE
 *
 *	math.h    include file for users of portable math library
 *
 *  SYNOPSIS
 *
 *	#include <math.h>
 *
 *  DESCRIPTION
 *
 *	This file should be included in any user compilation module
 *	which accesses routines from the Portable Math Library (PML).
 *
 */

#ifndef	_FEATURES_H
# include <features.h>
#endif

__BEGIN_DECLS

/* Get machine-dependent HUGE_VAL value (returned on overflow).
   On all IEEE754 machines, this is +Infinity.  */
#include <bits/huge_val.h>

/* Get machine-dependent NAN value (returned for some domain errors).  */
#ifdef	 __USE_ISOC99
# include <bits/nan.h>
#endif
/* Get general and ISO C9X specific information.  */
#include <bits/mathdef.h>


#ifndef __STRICT_ANSI__
/*
 *	Create the type "COMPLEX".  This is an obvious extension that I
 *	hope becomes a part of standard C someday.
 *
 */

typedef struct cmplx {			/* Complex structure */
    double real;			/* Real part */
    double imag;			/* Imaginary part */
} COMPLEX;

typedef enum  {
    DOMAIN      = 1,
    SING        = 2,
    OVERFLOW    = 3,
    UNDERFLOW   = 4,
    TLOSS       = 5,
    PLOSS       = 6
} exception_type;

/* In SVID error handling, `matherr' is called with this description
   of the exceptional condition.

   We have a problem when using C++ since `exception' is a reserved
   name in C++.  */
/* do not change the comment above; it is looked up by GCCs fixincludes script */
#ifdef __cplusplus
struct __exception
#else
struct exception 
#endif
{
	exception_type	type;	/* exception type */
	const char	*name;	/* function in which it occured */
	double		arg1;	/* an arg */
	double		arg2;	/* another arg */
	double		retval; /* val to return */
};
#endif /* __STRICT_ANSI__ */


/* Some useful constants.  */
#if defined __USE_BSD || defined __USE_XOPEN
# define M_E		2.7182818284590452354	/* e */
# define M_LOG2E	1.4426950408889634074	/* log_2 e */
# define M_LOG10E	0.43429448190325182765	/* log_10 e */
# define M_LN2		0.69314718055994530942	/* log_e 2 */
# define M_LN10		2.30258509299404568402	/* log_e 10 */
# define M_PI		3.14159265358979323846	/* pi */
# define M_PI_2		1.57079632679489661923	/* pi/2 */
# define M_PI_4		0.78539816339744830962	/* pi/4 */
# define M_1_PI		0.31830988618379067154	/* 1/pi */
# define M_2_PI		0.63661977236758134308	/* 2/pi */
# define M_2_SQRTPI	1.12837916709551257390	/* 2/sqrt(pi) */
# define M_SQRT2	1.41421356237309504880	/* sqrt(2) */
# define M_SQRT1_2	0.70710678118654752440	/* 1/sqrt(2) */
#endif

/* The above constants are not adequate for computation using `long double's.
   Therefore we provide as an extension constants with similar names as a
   GNU extension.  Provide enough digits for the 128-bit IEEE quad.  */
#ifdef __USE_GNU
# define M_El		2.7182818284590452353602874713526625L  /* e */
# define M_LOG2El	1.4426950408889634073599246810018922L  /* log_2 e */
# define M_LOG10El	0.4342944819032518276511289189166051L  /* log_10 e */
# define M_LN2l		0.6931471805599453094172321214581766L  /* log_e 2 */
# define M_LN10l	2.3025850929940456840179914546843642L  /* log_e 10 */
# define M_PIl		3.1415926535897932384626433832795029L  /* pi */
# define M_PI_2l	1.5707963267948966192313216916397514L  /* pi/2 */
# define M_PI_4l	0.7853981633974483096156608458198757L  /* pi/4 */
# define M_1_PIl	0.3183098861837906715377675267450287L  /* 1/pi */
# define M_2_PIl	0.6366197723675813430755350534900574L  /* 2/pi */
# define M_2_SQRTPIl	1.1283791670955125738961589031215452L  /* 2/sqrt(pi) */
# define M_SQRT2l	1.4142135623730950488016887242096981L  /* sqrt(2) */
# define M_SQRT1_2l	0.7071067811865475244008443621048490L  /* 1/sqrt(2) */
#endif


extern const double _infinitydf;	/* in normdf.cpp */


#if defined(__GNUC_INLINE__) && (!defined(NO_INLINE_MATH)) && (defined(_M68881) || defined(__M68881__))
#  define _INLINE_MATH 1
#else
#  define _INLINE_MATH 0
#endif

#if _INLINE_MATH
# include <math-68881.h>
#endif

#define HUGE HUGE_VAL

#ifdef __GNUC__
# ifndef __cplusplus
#  ifndef max
#   define max(x,y) ({typeof(x) _x=(x); typeof(y) _y=(y); if (_x>_y) _y=_x; _y;})
#   define min(x,y) ({typeof(x) _x=(x); typeof(y) _y=(y); if (_x<_y) _y=_x; _y;})
#  endif
# endif
#endif

#ifdef __USE_BSD

extern int finite(double) __THROW;
extern int __finite(double) __THROW;
extern int finitef(float) __THROW;
extern int __finitef(float) __THROW;
extern int finitel(long double) __THROW;
extern int __finitel(long double) __THROW;

extern int isinf (double) __THROW;
extern int __isinf (double) __THROW;
extern int isinff (float) __THROW;
extern int __isinff (float) __THROW;
extern int isinfl (long double) __THROW;
extern int __isinfl (long double) __THROW;

extern int isnan (double) __THROW;
extern int __isnan (double) __THROW;
extern int isnanf (float) __THROW;
extern int __isnanf (float) __THROW;
extern int isnanl (long double) __THROW;
extern int __isnanl (long double) __THROW;

extern int signbit (double) __THROW;
extern int __signbit (double) __THROW;
extern int signbitf (float) __THROW;
extern int __signbitf (float) __THROW;
extern int signbitl (long double) __THROW;
extern int __signbitl (long double) __THROW;

#endif

/* Return nonzero value if sign of X is negative.  */
# ifdef __NO_LONG_DOUBLE_MATH
#  define signbit(x) \
     (sizeof (x) == sizeof (float) ? __signbitf (x) : __signbit (x))
# else
#  define signbit(x) \
     (sizeof (x) == sizeof (float)					      \
      ? __signbitf (x)							      \
      : sizeof (x) == sizeof (double)					      \
      ? __signbit (x) : __signbitl (x))
# endif

/* Return nonzero value if X is not +-Inf or NaN.  */
# ifdef __NO_LONG_DOUBLE_MATH
#  define isfinite(x) \
     (sizeof (x) == sizeof (float) ? __finitef (x) : __finite (x))
# else
#  define isfinite(x) \
     (sizeof (x) == sizeof (float)					      \
      ? __finitef (x)							      \
      : sizeof (x) == sizeof (double)					      \
      ? __finite (x) : __finitel (x))
# endif

/* Return nonzero value if X is a NaN.  We could use `fpclassify' but
   we already have this functions `__isnan' and it is faster.  */
# ifdef __NO_LONG_DOUBLE_MATH
#  define isnan(x) \
     (sizeof (x) == sizeof (float) ? __isnanf (x) : __isnan (x))
# else
#  define isnan(x) \
     (sizeof (x) == sizeof (float)					      \
      ? __isnanf (x)							      \
      : sizeof (x) == sizeof (double)					      \
      ? __isnan (x) : __isnanl (x))
# endif

/* Return nonzero value is X is positive or negative infinity.  */
# ifdef __NO_LONG_DOUBLE_MATH
#  define isinf(x) \
     (sizeof (x) == sizeof (float) ? __isinff (x) : __isinf (x))
# else
#  define isinf(x) \
     (sizeof (x) == sizeof (float)					      \
      ? __isinff (x)							      \
      : sizeof (x) == sizeof (double)					      \
      ? __isinf (x) : __isinfl (x))
# endif


#if !_INLINE_MATH
extern double sin (double) __THROW;
extern double cos (double) __THROW;
extern double tan (double) __THROW;
extern double asin (double) __THROW;
extern double acos (double) __THROW;
extern double atan (double) __THROW;
extern double atan2 (double, double) __THROW;
extern double sinh (double) __THROW;
extern double cosh (double) __THROW;
extern double tanh (double) __THROW;
extern double atanh (double) __THROW;
extern double exp (double) __THROW;
extern double log (double) __THROW;
extern double log10 (double) __THROW;
extern double sqrt (double) __THROW;
extern double hypot (double, double) __THROW;
extern double pow (double, double) __THROW;
extern double fabs (double) __THROW;
extern double ceil (double) __THROW;
extern double floor (double) __THROW;
extern double round (double) __THROW;
extern double rint (double) __THROW;
extern double fmod (double, double) __THROW;

extern double ldexp (double, int) __THROW;
extern double frexp (double, int *) __THROW;
extern double modf (double, double *) __THROW;
#endif

extern double acosh (double) __THROW;
extern double asinh (double) __THROW;

#ifdef __USE_ISOC99
/* Return X with its signed changed to Y's.  */
extern double copysign (double, double) __THROW;
#endif

#ifndef __STRICT_ANSI__

#ifndef dabs
#if _INLINE_MATH
# define dabs(x) fabs(x)
#else
extern double dabs (double) __THROW;
#endif
#endif

#ifdef __cplusplus
extern int matherr (struct __exception *) throw();
#else
extern int matherr (struct exception *) __THROW;
#endif

extern int pmlcfs (int, int) __THROW;
extern int pmlcnt (void) __THROW;
extern int pmlerr (int) __THROW;
extern int pmllim (int) __THROW;
extern int pmlsfs (int, int) __THROW;
extern double poly (int, double *, double) __THROW;

#endif /* __STRICT_ANSI__ */

__END_DECLS

#endif /* math.h  */
