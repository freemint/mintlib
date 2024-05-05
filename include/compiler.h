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

/* Convenience macros to test the versions of glibc and gcc.
   Use them like this:
   #if __GNUC_PREREQ (2,8)
   ... code requiring gcc 2.8 or later ...
   #endif
   Note - they won't work for gcc1 or glibc1, since the _MINOR macros
   were not defined then.  */
#if defined __GNUC__ && defined __GNUC_MINOR__
# define __GNUC_PREREQ(maj, min) \
	((__GNUC__ << 16) + __GNUC_MINOR__ >= ((maj) << 16) + (min))
#else
# define __GNUC_PREREQ(maj, min) 0
#endif

/* Similarly for clang.  Features added to GCC after version 4.2 may
   or may not also be available in clang, and clang's definitions of
   __GNUC(_MINOR)__ are fixed at 4 and 2 respectively.  Not all such
   features can be queried via __has_extension/__has_feature.  */
#if defined __clang_major__ && defined __clang_minor__
# define __glibc_clang_prereq(maj, min) \
  ((__clang_major__ << 16) + __clang_minor__ >= ((maj) << 16) + (min))
#else
# define __glibc_clang_prereq(maj, min) 0
#endif

/* symbols to identify the type of compiler */

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
/* (note that gcc define this automatically when appropriate) */

#ifdef __GNUC__

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

#if __GNUC_PREREQ(2, 5)
#define __NORETURN __attribute__ ((noreturn))
#define __EXITING void
#else
#define __EXITING volatile void
#endif

#ifndef __NO_INLINE__
# define __GNUC_INLINE__
#endif

#if __GNUC_PREREQ(3, 3)
# define __CLOBBER_RETURN(a) 
#else
# define __CLOBBER_RETURN(a) a,
#endif

#if __GNUC_PREREQ(2, 6)
#define AND_MEMORY , "memory"
#else
#define AND_MEMORY
#endif

#endif /* __GNUC__ */

/* some default declarations */
/* if your compiler needs something
 * different, define it above
 */
#ifndef __CDECL
#ifdef __FASTCALL__
#define __CDECL __attribute__((__cdecl__))
#else
#define __CDECL
#endif
#endif

#ifndef __NORETURN
#define __NORETURN
#endif

#ifndef __EXTERN
#define __EXTERN extern
#endif

#ifndef __NULL
#  ifdef __MSHORT__
#    define __NULL (0L)
#  else
     /* avoid complaints about misuse of NULL :-) */
#    define __NULL (0)
#  endif
#endif

#ifdef __MSHORT__
# define __SSIZE_TYPEDEF__ long
# define __WINT_TYPEDEF__ unsigned long
#else
# define __SSIZE_TYPEDEF__ int
# define __WINT_TYPEDEF__ unsigned int
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

#ifndef __USER_LABEL_PREFIX__
#  if defined(__ELF__)
#    define __USER_LABEL_PREFIX__
#  else
#    define __USER_LABEL_PREFIX__ _
#  endif
#endif

#ifndef __SYMBOL_PREFIX
# define __SYMBOL_PREFIX __STRINGIFY(__USER_LABEL_PREFIX__)
# define __ASM_SYMBOL_PREFIX __USER_LABEL_PREFIX__
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

#endif /* _COMPILER_H */
