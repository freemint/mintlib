/*
 *	ISO C Standard: 4.10 GENERAL UTILITIES	<stdlib.h>
 */

#ifndef _STDLIB_H
#define _STDLIB_H

#ifndef _FEATURES_H
#include <features.h>
#endif

__BEGIN_DECLS

#define __need_size_t
#define __need_wchar_t
#define __need_ptrdiff_t
#define __need_NULL
#include <stddef.h>

#ifdef __MSHORT__
#define	RAND_MAX	(0x7FFF)	/* maximum value from rand() */
#else
#define	RAND_MAX	(0x7FFFFFFFL)	/* maximum value from rand() */
#endif

#define MB_CUR_MAX	1		/* max. length of multibyte character
					   in current locale */

#ifndef EXIT_FAILURE
#define EXIT_FAILURE	(1)
#define EXIT_SUCCESS	(0)
#endif

/* Returned by `div'.  */
typedef struct {
	int quot;			/* Quotient.  */
    	int rem;			/* Remainder.  */
} div_t;

/* Returned by `ldiv'.  */
#ifndef __ldiv_t_defined
typedef struct {
	long int quot;		/* Quotient.  */
	long int rem;		/* Remainder.  */
} ldiv_t;
# define __ldiv_t_defined	1
#endif

#if defined __USE_ISOC9X && !defined __lldiv_t_defined
/* Returned by `lldiv'.  */
__extension__ typedef struct {
	long long int quot;		/* Quotient.  */
	long long int rem;		/* Remainder.  */
} lldiv_t;
# define __lldiv_t_defined	1
#endif

/* Shorthand for type of comparison functions.  */
#ifndef __COMPAR_FN_T
# define __COMPAR_FN_T
typedef int (*__compar_fn_t) __PMT ((const void*, const void*));

# ifdef	__USE_GNU
typedef __compar_fn_t comparison_fn_t;
# endif
#endif

__EXTERN double atof __P ((const char* __s));
__EXTERN int atoi __P ((const char* __str));
__EXTERN long atol __P ((const char* __str));

#if defined __USE_ISOC9X || (defined __GNUC__ && defined __USE_MISC)
/* This function will be part of the standard C library in ISO C 9X.  */
__EXTERN long long int atoll __PROTO ((const char* __nptr));
#endif

/* Convert a string to a floating point number.  */
__EXTERN double strtod __PROTO ((const char* __nptr, char** __endptr));

#ifdef __USE_ISOC9X
/* Likewise for `float' and `long double' sizes of floating-point numbers.  */
__EXTERN float strtof __PROTO ((__const char* __nptr, char** __endptr));
__EXTERN long double strtold __PROTO ((__const char* __nptr, char** __endptr));
#endif

__EXTERN long int strtol __PROTO ((const char* __nptr, char** __endptr, 
                                   int __base));
__EXTERN unsigned long int strtoul __PROTO ((const char* __nptr, 
                                             char** __endptr, int __base));

#if defined __GNUC__ && defined __USE_BSD
/* Convert a string to a quadword integer.  */
__EXTERN long long int strtoq __PROTO ((const char* __nptr, char** _endptr,
                                        int __base));
/* Convert a string to an unsigned quadword integer.  */
__EXTERN long long int strtouq __PROTO ((const char* __nptr, char** _endptr,
                                         int __base));
#endif  /* GCC and use BSD.  */

#if defined __USE_ISOC9X || (defined __GNUC__ && defined __USE_MISC)
/* These functions will be part of the standard C library in ISO C 9X.  */
/* Convert a string to a quadword integer.  */
__EXTERN long long int strtoll __PROTO ((const char* __nptr, char** _endptr,
                                         int __base));
/* Convert a string to an unsigned quadword integer.  */
__EXTERN unsigned long long int strtoull __PROTO ((const char* __nptr, char** _endptr,
                                                   int __base));
#endif

__EXTERN void srand __P ((unsigned int __seed));
__EXTERN int rand __P ((void));

#if defined(__USE_SVID) || defined(__USE_XOPEN)
/* System V style 48-bit random number generator functions.  */

/* Return non-negative, double-precision floating-point value in [0.0,1.0).  */
__EXTERN double drand48 __PROTO ((void));
__EXTERN double erand48 __PROTO ((unsigned short int __xsubi[3]));

/* Return non-negative, long integer in [0,2^31).  */
__EXTERN long lrand48 __PROTO ((void));
__EXTERN long nrand48 __PROTO ((unsigned short int __xsubi[3]));

/* Return signed, long integers in [-2^31,2^31).  */
__EXTERN long mrand48 __PROTO ((void));
__EXTERN long jrand48 __PROTO ((unsigned short int __xsubi[3]));

/* Seed random number generator.  */
__EXTERN void srand48 __PROTO ((long __seedval));
__EXTERN unsigned short int *seed48 __PROTO ((unsigned short int __seed16v[3]));
__EXTERN void lcong48 __PROTO ((unsigned short int __param[7]));

/* Data structure for communication with thread safe versions.  */
struct drand48_data
  {
    unsigned short int x[3];	/* Current state.  */
    unsigned short int a[3];	/* Factor in congruential formula.  */
    unsigned short int c;	/* Additive const. in congruential formula.  */
    unsigned short int old_x[3]; /* Old state.  */
    int init;			/* Flag for initializing.  */
  };

#ifdef __USE_MISC
/* Return non-negative, double-precision floating-point value in [0.0,1.0).  */
__EXTERN int drand48_r __PROTO ((struct drand48_data *__buffer, 
                                 double *__result));
__EXTERN int erand48_r __PROTO ((unsigned short int __xsubi[3],
			         struct drand48_data *__buffer, 
			         double *__result));

/* Return non-negative, long integer in [0,2^31).  */
__EXTERN int lrand48_r __PROTO ((struct drand48_data *__buffer, 
                                 long *__result));
__EXTERN int nrand48_r __PROTO ((unsigned short int __xsubi[3],
			         struct drand48_data *__buffer, 
			         long *__result));

/* Return signed, long integers in [-2^31,2^31).  */
__EXTERN int mrand48_r __PROTO ((struct drand48_data *__buffer, 
                                 long *__result));
__EXTERN int jrand48_r __PROTO ((unsigned short int __xsubi[3],
			         struct drand48_data *__buffer, 
			         long *__result));

/* Seed random number generator.  */
__EXTERN int srand48_r __PROTO ((long __seedval, 
                                 struct drand48_data *__buffer));
__EXTERN int seed48_r __PROTO ((unsigned short int __seed16v[3],
			        struct drand48_data *__buffer));
__EXTERN int lcong48_r __PROTO ((unsigned short int __param[7],
			         struct drand48_data *__buffer));
#endif	/* Use misc.  */

/* Internal function to compute next state of the generator.  */
__EXTERN int __drand48_iterate __PROTO ((unsigned short int __xsubi[3],
				         struct drand48_data *__buffer));
#endif	/* Use SVID or X/Open.  */

__EXTERN void *malloc __P ((size_t __n));
__EXTERN void free __P ((void* __param));
__EXTERN void *realloc __P ((void* __r, size_t __n));
__EXTERN void *calloc __P ((size_t __n, size_t __s));

#if defined __USE_GNU || defined __USE_BSD || defined __USE_MISC
# include <alloca.h>
#endif /* Use GNU, BSD, or misc.  */

#ifndef __STRICT_ANSI__

# ifdef atarist
    __EXTERN void _malloczero __P ((int __yes));
    __EXTERN void _mallocChunkSize __P ((size_t __siz));
# endif

#endif /* __STRICT_ANSI__ */

__EXTERN __EXITING abort __P ((void)) __NORETURN;
#if !(defined (__GNUG__) && __GNUG__ == 1)
  /* bug in g++ 1.39.0 -- cant digest proto */
__EXTERN int atexit __P ((void (*)(void)));
#endif
__EXTERN __EXITING exit __P ((int)) __NORETURN;

__EXTERN char *getenv __P ((const char* __tag));
__EXTERN int system __P ((const char* __s));

__EXTERN void *bsearch __P ((const void* __key, const void* __base, 
                                size_t __num, size_t __size, 
                                __compar_fn_t __compar));
__EXTERN void qsort __P ((void* __base, size_t __total_elems, 
                             size_t __size, 
                             __compar_fn_t __compar));

__EXTERN int abs __P ((int __x));
__EXTERN long labs __P ((long __x));

/* Return the `div_t', `ldiv_t' or `lldiv_t' representation
   of the value of NUMER over DENOM. */
/* GCC may have built-ins for these someday.  */
__EXTERN div_t div __P ((int __numer, int __denom)) __attribute__ ((__const__));
__EXTERN ldiv_t ldiv __P ((long int __numer, long int __denom))
     __attribute__ ((__const__));
#ifdef __USE_ISOC9X
__extension__ __EXTERN lldiv_t lldiv __P ((long long int __numer,
					   long long int __denom))
     __attribute__ ((__const__));
#endif

__EXTERN int mblen __P ((const char *, size_t));
__EXTERN size_t mbstowcs __P ((wchar_t *, const char *, size_t));
__EXTERN int mbtowc __P ((wchar_t *, const char *, size_t));
__EXTERN size_t wcstombs __P ((char *, const wchar_t *, size_t));
__EXTERN int wctomb __P ((char *, wchar_t));

__EXTERN wchar_t *wcscat __P ((wchar_t *, const wchar_t *));
__EXTERN int wcscmp __P ((const wchar_t *, const wchar_t *));
__EXTERN wchar_t *wcscpy __P ((wchar_t *, const wchar_t *));
__EXTERN size_t wcslen __P ((const wchar_t *));
__EXTERN wchar_t *wcsncat __P ((wchar_t *, const wchar_t *, size_t));
__EXTERN int wcsncmp __P ((const wchar_t *, const wchar_t *, size_t));
__EXTERN wchar_t *wcsncpy __P ((wchar_t *, const wchar_t *, size_t));

/* This function is similar to the above but returns NULL if the
   programs is running with SUID or SGID enabled.  */
__EXTERN char *__secure_getenv __PROTO ((const char *__name));

#if defined(__USE_SVID) || defined(__USE_XOPEN)
/* The SVID says this is in <stdio.h>, but this seems a better place.	*/
/* Put STRING, which is of the form "NAME=VALUE", in the environment.
   If there is no `=', remove NAME from the environment.  */
__EXTERN int putenv __PROTO ((const char *__string));
#endif

#ifdef	__USE_BSD
/* Set NAME to VALUE in the environment.
   If REPLACE is nonzero, overwrite an existing value.  */
__EXTERN int setenv __PROTO ((const char *__name, const char *__value,
			int __replace));

/* Remove the variable NAME from the environment.  */
__EXTERN void unsetenv __PROTO ((const char *__name));
#endif

#ifdef __USE_MISC
/* The `clearenv` was planned to be added to POSIX.1 but probably
   never made it.  Nevertheless the POSIX.9 standard (POSIX bindings
   for Fortran 77) requires this function.  */
__EXTERN int clearenv __PROTO ((void));
#endif

#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED)
/* Generate a unique temporary file name from TEMPLATE.
   The last six characters of TEMPLATE must be "XXXXXX";
   they are replaced with a string that makes the file name unique.
   Returns TEMPLATE, or a null pointer if it cannot get a unique file name.  */
__EXTERN char *mktemp __PROTO ((char* __template));

/* Generate a unique temporary file name from TEMPLATE.
   The last six characters of TEMPLATE must be "XXXXXX";
   they are replaced with a string that makes the filename unique.
   Returns a file descriptor open on the file for reading and writing,
   or -1 if it cannot create a uniquely-named file.  */
__EXTERN int mkstemp __PROTO ((char* __template));
#endif

#ifdef __USE_GNU
/* Return a malloc'd string containing the canonical absolute name of the
   named file.  The last file name component need not exist, and may be a
   symlink to a nonexistent file.  */
__EXTERN char* canonicalize_file_name __P ((const char* __name));
#endif

#if defined __USE_BSD || defined __USE_XOPEN_EXTENDED
/* Return the canonical absolute name of file NAME.  The last file name
   component need not exist, and may be a symlink to a nonexistent file.
   If RESOLVED is null, the result is malloc'd; otherwise, if the canonical
   name is PATH_MAX chars or more, returns null with `errno' set to
   ENAMETOOLONG; if the name fits in fewer then PATH_MAX chars, returns
   the name in RESOLVED.  */
__EXTERN char* realpath __P ((const char* __name, char* __resolved));
#endif

#if defined(__LATTICE__) && !defined(_NO_INLINE)

int	__builtin_abs(int);
long	__builtin_labs(long);

#define abs(i)	__builtin_abs(i);
#define labs(l)	__builtin_labs(l);

#endif

__END_DECLS

#endif /* _STDLIB_H */
