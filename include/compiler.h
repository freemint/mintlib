/* compiler specific defines */
/* this file is guaranteed to be included exactly once if you include
   anything at all. all site-dependent or compiler-dependent stuff
   should go here!!!
 */

#ifndef _COMPILER_H
# define _COMPILER_H 1

/* symbol to identify the library itself */
#ifndef __MINT__
# define __MINT__
#endif

/* symbols to identify the type of compiler */

#ifdef __SOZOBONC__
#define __SOZOBON__ __SOZOBONC__
#else
# ifdef SOZOBON
  /* The "real" Sozobon, as distinct from HSC.  Don't want to assume any
     features about it, so set version number to 0. */
# define __SOZOBON__ 0
# endif
#endif

#ifdef LATTICE
#define __LATTICE__
#endif

/* general library stuff */
/* __SIZE_TYPEDEF__: 	the type returned by sizeof() */
/* __SSIZE_TYPEDEF__:   signed long values.  */
/* __PTRDIFF_TYPEDEF__: the type of the difference of two pointers */
/* __WCHAR_TYPEDEF__: 	wide character type (i.e. type of L'x') */
/* __WINT_TYPEDEF__:    the type wint_t (whatever this is).  */
/* __EXITING:           the type of a function that exits */
/* __NORETURN:          attribute of a function that exits (gcc >= 2.5) */
/* __CDECL:             function must get parameters on stack */
		/* if !__CDECL, passing in registers is OK */

/* symbols to report about compiler features */
/* #define __NEED_VOID__	compiler doesn't have a void type */
/* #define __MSHORT__		compiler uses 16 bit integers */
/* (note that gcc and C68 define this automatically when appropriate) */

#ifdef __GNUC__
#if __GNUC__ > 1
#define __SIZE_TYPEDEF__ __SIZE_TYPE__
#define __PTRDIFF_TYPEDEF__ __PTRDIFF_TYPE__
#ifdef __GNUG__
/* In C++, wchar_t is a distinct basic type,
   and we can expect __wchar_t to be defined by cc1plus.  */
#define __WCHAR_TYPEDEF__ __wchar_t
#else
/* In C, cpp tells us which type to make an alias for.  */
#define __WCHAR_TYPEDEF__ __WCHAR_TYPE__
#endif
#else
#ifndef sun
#  define __SIZE_TYPEDEF__ unsigned long
#  define __PTRDIFF_TYPEDEF__ long
#  define __WCHAR_TYPEDEF__ int
#else
   /* sun always seems to have an agenda of their own */
#  include <sys/stdtypes.h>
#  define __SIZE_TYPEDEF__ int
#  define __PTRDIFF_TYPEDEF__ int
#  define __WCHAR_TYPEDEF__ unsigned short /* this seems reasonable */
#  define _SIZE_T __SIZE_TYPEDEF__
#  define _WCHAR_T __WCHAR_TYPEDEF__
#endif
#endif
#if (__GNUC__ == 2) && (__GNUC_MINOR__ >= 5) /* false for gcc < 2.5 */
#define __NORETURN __attribute__ ((noreturn))
#define __EXITING void
#else
#define __EXITING volatile void
#endif
#ifndef __NO_INLINE__
# define __GNUC_INLINE__
#endif
#endif

#ifdef __LATTICE__
#define __SIZE_TYPEDEF__ unsigned long
#define __PTRDIFF_TYPEDEF__ long
#define __WCHAR_TYPEDEF__ char
#define __EXITING void
#define __CDECL __stdargs
#ifdef _SHORTINT
# define __MSHORT__
#endif
#ifdef _UNSIGNEDCHAR
# define __CHAR_UNSIGNED__
#endif
#endif

#ifdef __C68__
#define __SIZE_TYPEDEF__ unsigned long
#define __PTRDIFF_TYPEDEF__ long
#define __WCHAR_TYPEDEF__ char
#define __EXITING void
#endif

#ifdef __SOZOBON__
/*
 * Temporary hacks to overcome 1.33i's short symbol names.  As of 2.01i,
 * this restriction is removed, but can be reinstated for compatibility
 * via the -8 compiler flag.  -- sb 5/26/93
 */
#if __SOZOBON__ < 0x201 || !defined(__HSC_LONGNAMES__)
#  define _mallocChunkSize _sc_mCS
#  define _malloczero _sc_mz
#  define _console_read_byte _sc_crb
#  define _console_write_byte _sc_cwb
#endif

#define __NULL (0L)
#if __SOZOBON__ < 0x122		/* previous versions didn't grok (void *) */
#  define void char
#endif
#define __SIZE_TYPEDEF__ unsigned int
#define __PTRDIFF_TYPEDEF__ long
#define __WCHAR_TYPEDEF__ char
#define __EXITING void
#if __SOZOBON__ < 0x201		/* 2.01 now #define's this */
#  define __MSHORT__
#endif
#endif /* __SOZOBON__ */

#ifdef __TURBOC__
#ifndef __STDC__
#  define __STDC__ 1
#endif
#define __SIZE_TYPEDEF__ unsigned long
#define __SSIZE_TYPEDEF__ unsigned long
#define __PTRDIFF_TYPEDEF__ long
#define __WCHAR_TYPEDEF__ char
#define __EXITING void
#define __MSHORT__
#define __gnuc_va_list void*
#define __CDECL cdecl
/* As long as we haven't ported gemlib to Pure C and hence have to use
 * Turbo's/Pure's GEM library, define the next:
 */
#define __TCC_GEMLIB__
#endif /* __TURBOC__ */

#if defined(__hpux) && (!defined(__GNUC__))
#define __SIZE_TYPEDEF__ unsigned int
#define __PTRDIFF_TYPEDEF__ int
#define __WCHAR_TYPEDEF__ unsigned int
#define __EXITING void
#endif

/* some default declarations */
/* if your compiler needs something
 * different, define it above
 */
#ifndef __CDECL
#define __CDECL
#endif

#ifndef __NORETURN
#define __NORETURN
#endif

#ifndef __NULL
#  ifdef __MSHORT__
#    define __NULL (0L)
#  else
     /* avoid complaints about misuse of NULL :-) */
#    define __NULL (0)
#  endif
#endif

#ifdef __cplusplus
# define __PROTO(x) x
#else
# ifdef __STDC__
#  ifndef __NO_PROTO__
#    define __PROTO(x) x
#  endif
# else
/*
 * fudge non-ANSI compilers to be like ANSI
 */
#  define const
#  define volatile

#  ifdef __NEED_VOID__
typedef char void;	/* so that (void *) is the same as (char *) */
	/* also lets us know that foo() {...} and void foo() {...} are
	   different */
#  endif
# endif /* __STDC__ */
#endif /* __cplusplus */

#ifdef __TURBOC__
# define __EXTERN
#else
# define __EXTERN extern
#endif

#ifndef __PROTO
#define __PROTO(x) ()
#endif

/* used in limits.h, stdio.h */
#define	_NFILE		(32)		/* maximum number of open streams */

#ifdef __TURBOC__
# define atarist
#endif

#ifdef __MSHORT__
# define __SSIZE_TYPEDEF__ long
# define __WINT_TYPEDEF__ unsigned long
#else
# define __SSIZE_TYPEDEF__ int
# define __WINT_TYPEDEF__ unsigned int
#endif

/* These macros are provided for GNU compatibility.  */
#ifndef __P
# define __P(x) __PROTO(x)
#endif

#ifdef __cplusplus
# ifndef __BEGIN_DECLS
#  define __BEGIN_DECLS extern "C" {
#  define __END_DECLS }
# endif
#else
# ifndef __BEGIN_DECLS
#  define __BEGIN_DECLS
#  define __END_DECLS
# endif
#endif

#ifndef __GNUC__
# ifdef __OPTIMIZE__
#  undef __OPTIMIZE__
# endif
#endif

#if defined (__GNUC__) && !defined (__MSHORT__)
# ifndef __unix__
#  define __unix__ 1
# endif
# ifndef __unix
#  define __unix __unix__
# endif
# ifndef __UNIX__
#  define __UNIX__ __unix__
# endif
# ifndef __UNIX
#  define __UNIX __unix__
# endif
# ifndef _unix
#  define _unix __unix__
# endif
# ifndef __STRICT_ANSI__
#  ifndef unix
#   define unix __unix__
#  endif
# endif
#endif

#ifndef _LINKER_H
# include <linker.h>
#endif

#ifdef _LIBC
# ifndef _LIBC_SYMBOLS_H
#  include <libc-symbols.h>
# endif
#endif

#ifndef _FEATURES_H
# include <features.h>
#endif

#ifdef _LIBC
# define _MINTLIB
#endif

#ifdef __GNUC__

/* GCC can always grok prototypes.  For C++ programs we add throw()
   to help it optimize the function calls.  But this works only with
   gcc 2.8.x and egcs.  */
# if defined __cplusplus && (__GNUC__ >= 3 || __GNUC_MINOR__ >= 8)
#  define __THROW	throw ()
# else
#  define __THROW
# endif
# define __MALLOC_P(args)	args __THROW
/* This macro will be used for functions which might take C++ callback
   functions.  */
# define __MALLOC_PMT(args)	args

#else	/* Not GCC.  */

# if (defined __STDC__ && __STDC__) || defined __cplusplus

#  define __MALLOC_P(args)	args
#  define __MALLOC_PMT(args)	args

# else	/* Not ANSI C or C++.  */

#  define __MALLOC_P(args)	()	/* No prototypes.  */
#  define __MALLOC_PMT(args)	()

# endif	/* ANSI C or C++.  */

# define __THROW

#endif	/* GCC.  */

#endif /* _COMPILER_H */
