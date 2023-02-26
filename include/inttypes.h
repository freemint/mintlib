/* Copyright (C) 1997-2001, 2004, 2007 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

/* Modified for MiNTLib by Guido Flohr <guido@freemint.de>.  */

/*
 *	ISO C 9X: 7.5 Format conversion of integer types	<inttypes.h>
 */

#ifndef _INTTYPES_H
#define _INTTYPES_H	1

#include <features.h>
/* Get the type definitions.  */
#include <stdint.h>


/* The ISO C 9X standard specifies that these macros must only be
   defined if explicitly requested.  */
#if !defined __cplusplus || defined __STDC_FORMAT_MACROS

/* Macros for printing format specifiers.  */

/* Decimal notation.  */
# define PRId8		"d"
# define PRId16		"d"
# define PRId32		"d"
#ifndef __NO_LONGLONG
# define PRId64		"lld"
#endif

# define PRIdLEAST8	"d"
# define PRIdLEAST16	"d"
# define PRIdLEAST32	"d"
#ifndef __NO_LONGLONG
# define PRIdLEAST64	"lld"
#endif

# define PRIdFAST8	"d"
# define PRIdFAST16	"d"
# define PRIdFAST32	"d"
#ifndef __NO_LONGLONG
# define PRIdFAST64	"lld"
#endif


# define PRIi8		"i"
# define PRIi16		"i"
# define PRIi32		"i"
#ifndef __NO_LONGLONG
# define PRIi64		"lli"
#endif

# define PRIiLEAST8	"i"
# define PRIiLEAST16	"i"
# define PRIiLEAST32	"i"
#ifndef __NO_LONGLONG
# define PRIiLEAST64	"lli"
#endif

# define PRIiFAST8	"i"
# define PRIiFAST16	"i"
# define PRIiFAST32	"i"
#ifndef __NO_LONGLONG
# define PRIiFAST64	"lli"
#endif

/* Octal notation.  */
# define PRIo8		"o"
# define PRIo16		"o"
# define PRIo32		"o"
#ifndef __NO_LONGLONG
# define PRIo64		"llo"
#endif

# define PRIoLEAST8	"o"
# define PRIoLEAST16	"o"
# define PRIoLEAST32	"o"
#ifndef __NO_LONGLONG
# define PRIoLEAST64	"llo"
#endif

# define PRIoFAST8	"o"
# define PRIoFAST16	"o"
# define PRIoFAST32	"o"
#ifndef __NO_LONGLONG
# define PRIoFAST64	"llo"
#endif

/* Unsigned integers.  */
# define PRIu8		"u"
# define PRIu16		"u"
# define PRIu32		"u"
#ifndef __NO_LONGLONG
# define PRIu64		"llu"
#endif

# define PRIuLEAST8	"u"
# define PRIuLEAST16	"u"
# define PRIuLEAST32	"u"
#ifndef __NO_LONGLONG
# define PRIuLEAST64	"llu"
#endif

# define PRIuFAST8	"u"
# define PRIuFAST16	"u"
# define PRIuFAST32	"u"
#ifndef __NO_LONGLONG
# define PRIuFAST64	"llu"
#endif

/* lowercase hexadecimal notation.  */
# define PRIx8		"x"
# define PRIx16		"x"
# define PRIx32		"x"
#ifndef __NO_LONGLONG
# define PRIx64		"llx"
#endif

# define PRIxLEAST8	"x"
# define PRIxLEAST16	"x"
# define PRIxLEAST32	"x"
#ifndef __NO_LONGLONG
# define PRIxLEAST64	"llx"
#endif

# define PRIxFAST8	"x"
# define PRIxFAST16	"x"
# define PRIxFAST32	"x"
#ifndef __NO_LONGLONG
# define PRIxFAST64	"llx"
#endif

/* UPPERCASE hexadecimal notation.  */
# define PRIX8		"X"
# define PRIX16		"X"
# define PRIX32		"X"
#ifndef __NO_LONGLONG
# define PRIX64		"llX"
#endif

# define PRIXLEAST8	"X"
# define PRIXLEAST16	"X"
# define PRIXLEAST32	"X"
#ifndef __NO_LONGLONG
# define PRIXLEAST64	"llX"
#endif

# define PRIXFAST8	"X"
# define PRIXFAST16	"X"
# define PRIXFAST32	"X"
#ifndef __NO_LONGLONG
# define PRIXFAST64	"llX"
#endif


/* Macros for printing `intmax_t' and `uintmax_t'.  */
#ifndef __NO_LONGLONG
# define PRIdMAX	"lld"
# define PRIiMAX	"lli"
# define PRIoMAX	"llo"
# define PRIuMAX	"llu"
# define PRIxMAX	"llx"
# define PRIXMAX	"llX"
#else
# define PRIdMAX	"ld"
# define PRIiMAX	"li"
# define PRIoMAX	"lo"
# define PRIuMAX	"lu"
# define PRIxMAX	"lx"
# define PRIXMAX	"lX"
#endif


/* Macros for printing `intptr_t' and `uintptr_t'.  */
# define PRIdPTR	"d"
# define PRIiPTR	"i"
# define PRIoPTR	"o"
# define PRIuPTR	"u"
# define PRIxPTR	"x"
# define PRIXPTR	"X"


/* Macros for scanning format specifiers.  */

/* Signed decimal notation.  */
# define SCNd8		"hhd"
# define SCNd16		"hd"
# define SCNd32		"d"
#ifndef __NO_LONGLONG
# define SCNd64		"lld"
#endif

# define SCNdLEAST8	"hhd"
# define SCNdLEAST16	"hd"
# define SCNdLEAST32	"d"
#ifndef __NO_LONGLONG
# define SCNdLEAST64	"lld"
#endif

# define SCNdFAST8	"hhd"
# define SCNdFAST16	"d"
# define SCNdFAST32	"d"
#ifndef __NO_LONGLONG
# define SCNdFAST64	"lld"
#endif

/* Signed decimal notation.  */
# define SCNi8		"hhi"
# define SCNi16		"hi"
# define SCNi32		"i"
#ifndef __NO_LONGLONG
# define SCNi64		"lli"
#endif

# define SCNiLEAST8	"hhi"
# define SCNiLEAST16	"hi"
# define SCNiLEAST32	"i"
#ifndef __NO_LONGLONG
# define SCNiLEAST64	"lli"
#endif

# define SCNiFAST8	"hhi"
# define SCNiFAST16	"i"
# define SCNiFAST32	"i"
#ifndef __NO_LONGLONG
# define SCNiFAST64	"lli"
#endif

/* Unsigned decimal notation.  */
# define SCNu8		"hhu"
# define SCNu16		"hu"
# define SCNu32		"u"
#ifndef __NO_LONGLONG
# define SCNu64		"llu"
#endif

# define SCNuLEAST8	"hhu"
# define SCNuLEAST16	"hu"
# define SCNuLEAST32	"u"
#ifndef __NO_LONGLONG
# define SCNuLEAST64	"llu"
#endif

# define SCNuFAST8	"hhu"
# define SCNuFAST16	"u"
# define SCNuFAST32	"u"
#ifndef __NO_LONGLONG
# define SCNuFAST64	"llu"
#endif

/* Octal notation.  */
# define SCNo8		"hho"
# define SCNo16		"ho"
# define SCNo32		"o"
#ifndef __NO_LONGLONG
# define SCNo64		"llo"
#endif

# define SCNoLEAST8	"hho"
# define SCNoLEAST16	"ho"
# define SCNoLEAST32	"o"
#ifndef __NO_LONGLONG
# define SCNoLEAST64	"llo"
#endif

# define SCNoFAST8	"hho"
# define SCNoFAST16	"o"
# define SCNoFAST32	"o"
#ifndef __NO_LONGLONG
# define SCNoFAST64	"llo"
#endif

/* Hexadecimal notation.  */
# define SCNx8		"hhx"
# define SCNx16		"hx"
# define SCNx32		"x"
#ifndef __NO_LONGLONG
# define SCNx64		"llx"
#endif

# define SCNxLEAST8	"hhx"
# define SCNxLEAST16	"hx"
# define SCNxLEAST32	"x"
#ifndef __NO_LONGLONG
# define SCNxLEAST64	"llx"
#endif

# define SCNxFAST8	"hhx"
# define SCNxFAST16	"x"
# define SCNxFAST32	"x"
#ifndef __NO_LONGLONG
# define SCNxFAST64	"llx"
#endif


/* Macros for scanning `intmax_t' and `uintmax_t'.  */
#ifndef __NO_LONGLONG
# define SCNdMAX	"lld"
# define SCNiMAX	"lli"
# define SCNoMAX	"llo"
# define SCNuMAX	"llu"
# define SCNxMAX	"llx"
#else
# define SCNdMAX	"ld"
# define SCNiMAX	"li"
# define SCNoMAX	"lo"
# define SCNuMAX	"lu"
# define SCNxMAX	"lx"
#endif

/* Macros for scaning `intptr_t' and `uintptr_t'.  */
# define SCNdPTR	"d"
# define SCNiPTR	"i"
# define SCNoPTR	"o"
# define SCNuPTR	"u"
# define SCNxPTR	"x"

#endif	/* C++ && format macros */


__BEGIN_DECLS

#ifndef __NO_LONGLONG
/* We have to define the `uintmax_t' type using `lldiv_t'.  */
#ifndef __lldiv_t_defined
/* Returned by `lldiv'.  */
__extension__ typedef struct
  {
    long long int quot;		/* Quotient.  */
    long long int rem;		/* Remainder.  */
  } lldiv_t;
# define __lldiv_t_defined	1
#endif

/* This stuff is not yet implemented.  */

/* Returned by `imaxdiv'.  */
typedef lldiv_t imaxdiv_t;
#else
typedef struct
  {
    long int quot;		/* Quotient.  */
    long int rem;		/* Remainder.  */
  } imaxdiv_t;
#endif


/* Compute absolute value of N.  */
extern intmax_t imaxabs __P ((intmax_t __n)) __attribute__ ((__const__));
#ifdef __NO_LONGLONG
#  define imaxabs(x) labs(x)
#endif

/* Return the `imaxdiv_t' representation of the value of NUMER over DENOM. */
extern imaxdiv_t imaxdiv __P ((intmax_t __numer, intmax_t __denom))
     __attribute__ ((__const__));

/* Like `strtol' but convert to `intmax_t'.  */
extern intmax_t strtoimax __P ((__const char *__restrict __nptr,
				char **__restrict __endptr, int __base));

/* Like `strtoul' but convert to `uintmax_t'.  */
extern uintmax_t strtoumax __P ((__const char * __restrict __nptr,
				 char ** __restrict __endptr, int __base));

#ifndef __MINT__
/* Like `wcstol' but convert to `intmax_t'.  */
extern intmax_t wcstoimax __P ((__const wchar_t * __restrict __nptr,
				wchar_t **__restrict __endptr, int __base));

/* Like `wcstoul' but convert to `uintmax_t'.  */
extern uintmax_t wcstoumax __P ((__const wchar_t * __restrict __nptr,
				 wchar_t ** __restrict __endptr, int __base));
#endif /* not MiNT */

#ifndef __NO_LONGLONG
/* We want to use the appropriate functions from <stdlib.h> but cannot
   assume the header is read already.  */
__extension__ extern long long int llabs __P ((long long int __x))
     __attribute__ ((__const__));
__extension__ extern lldiv_t lldiv __P ((long long int __numer,
					 long long int __denom))
     __attribute__ ((__const__));
#endif


#ifdef __USE_EXTERN_INLINES

/* Compute absolute value of N.  */
_EXTERN_INLINE intmax_t
imaxabs (intmax_t __n)
{
  return llabs (__n);
}

/* Return the `imaxdiv_t' representation of the value of NUMER over DENOM. */
_EXTERN_INLINE imaxdiv_t
imaxdiv (intmax_t __numer, intmax_t __denom)
{
  return lldiv (__numer, __denom);
}

/* Like `strtol' but convert to `intmax_t'.  */
# ifndef __strtoll_internal_defined
__extension__
extern long long int __strtoll_internal __P ((__const char *__restrict __nptr,
					      char **__restrict __endptr,
					      int __base, int __group));
#  define __strtoll_internal_defined	1
# endif
_EXTERN_INLINE intmax_t
strtoimax (__const char *__restrict nptr, char **__restrict endptr,
	   int base)
{
  return __strtoll_internal (nptr, endptr, base, 0);
}

/* Like `strtoul' but convert to `uintmax_t'.  */
# ifndef __strtoull_internal_defined
__extension__
extern unsigned long long int __strtoull_internal __P ((__const char *
							__restrict __nptr,
							char **
							__restrict __endptr,
							int __base,
							int __group));
#  define __strtoull_internal_defined	1
# endif
_EXTERN_INLINE uintmax_t
strtoumax (__const char *__restrict nptr, char **__restrict endptr,
	   int base)
{
  return __strtoull_internal (nptr, endptr, base, 0);
}

#ifndef __MINT__
/* Like `wcstol' but convert to `intmax_t'.  */
# ifndef __wcstoll_internal_defined
__extension__
extern long long int __wcstoll_internal __P ((__const wchar_t *
					      __restrict __nptr,
					      wchar_t **__restrict __endptr,
					      int __base, int __group));
#  define __wcstoll_internal_defined	1
# endif
_EXTERN_INLINE intmax_t
wcstoimax (__const wchar_t *__restrict nptr, wchar_t **__restrict endptr,
	   int base) __THROW
{
  return __wcstoll_internal (nptr, endptr, base, 0);
}


/* Like `wcstoul' but convert to `uintmax_t'.  */
# ifndef __wcstoull_internal_defined
__extension__
extern unsigned long long int __wcstoull_internal __P ((__const wchar_t *
							__restrict __nptr,
							wchar_t **
							__restrict __endptr,
							int __base,
							int __group));
#  define __wcstoull_internal_defined	1
# endif
_EXTERN_INLINE uintmax_t
wcstoumax (__const wchar_t *__restrict nptr, wchar_t **__restrict endptr,
	   int base) __THROW
{
  return __wcstoull_internal (nptr, endptr, base, 0);
}
#endif	/* Use extern inlines.  */

#endif  /* not MiNT */

__END_DECLS

#endif /* inttypes.h */
