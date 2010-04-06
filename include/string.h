/*
 *	ISO C Standard: 4.11 STRING HANDLING	<string.h>
 */

#ifndef _STRING_H
#define _STRING_H

#ifndef	_FEATURES_H
# include <features.h>
#endif

__BEGIN_DECLS

/* Get size_t and NULL from <stddef.h>.  */
#define __need_size_t
#define	__need_NULL
#include <stddef.h>


/* Copy N bytes of SRC to DEST.  */
__EXTERN void* memcpy __P ((void*  __dest,
			    const void*  __src, size_t __n));
/* Copy N bytes of SRC to DEST, guaranteeing
   correct behavior for overlapping strings.  */
__EXTERN void* memmove __P ((void* __dest, const void* __src,
			     size_t __n));

/* Copy no more than N bytes of SRC to DEST, stopping when C is found.
   Return the position in DEST one byte past where C was copied,
   or NULL if C was not found in the first N bytes of SRC.  */
#if defined __USE_SVID || defined __USE_BSD || defined __USE_XOPEN
__EXTERN void* memccpy __P ((void* __dest, const void* __src,
			     int __c, size_t __n));
#endif /* SVID.  */


/* Set N bytes of S to C.  */
__EXTERN void* memset __P ((void* __s, int __c, size_t __n));

/* Compare N bytes of S1 and S2.  */
__EXTERN int memcmp __P ((const void* __s1, const void* __s2,
			  size_t __n));

/* Search N bytes of S for C.  */
__EXTERN void* memchr __P ((const void* __s, int __c, size_t __n));

#ifdef __USE_GNU
/* Search in S for C.  This is similar to `memchr' but there is no
   length limit.  */
__EXTERN void* __rawmemchr __P ((const void* __s, int __c));
__EXTERN void* rawmemchr __P ((const void* __s, int __c));

/* Search N bytes of S for the final occurrence of C.  */
__EXTERN void* memrchr __P ((const void *__s, int __c, size_t __n));
#endif


/* Copy SRC to DEST.  */
__EXTERN char* strcpy __P ((char* __dest,
			    const char* __src));
/* Copy no more than N characters of SRC to DEST.  */
__EXTERN char* strncpy __P ((char* __dest,
			     const char* __src, size_t __n));

/* Append SRC onto DEST.  */
__EXTERN char* strcat __P ((char* __dest,
			  const char* __src));
/* Append no more than N characters from SRC onto DEST.  */
__EXTERN char* strncat __P ((char* __dest,
			   const char* __src, size_t __n));

/* Compare S1 and S2.  */
__EXTERN int strcmp __P ((const char* __s1, const char* __s2));
/* Compare N characters of S1 and S2.  */
__EXTERN int strncmp __P ((const char* __s1, const char* __s2, size_t __n));

/* Compare the collated forms of S1 and S2.  */
__EXTERN int strcoll __P ((const char* __s1, const char* __s2));
/* Put a transformation of SRC into no more than N bytes of DEST.  */
__EXTERN size_t strxfrm __P ((char* __dest,
			      const char* __src, size_t __n));


#if defined __USE_SVID || defined __USE_BSD || defined __USE_XOPEN_EXTENDED
/* Duplicate S, returning an identical malloc'd string.  */
__EXTERN char* __strdup __P ((const char* __s));
__EXTERN char* strdup __P ((const char* __s));
#endif

/* Return a malloc'd copy of at most N bytes of STRING.  The
   resultant string is terminated even if no null terminator
   appears before STRING[N].  */
#if defined __USE_GNU
__EXTERN char* strndup __P ((const char* __string, size_t __n));
#endif

#if defined __USE_GNU && defined __GNUC__
/* Duplicate S, returning an identical alloca'd string.  */
# define strdupa(s)							      \
  (__extension__							      \
    ({									      \
      const char* __old = (s);					      \
      size_t __len = strlen (__old) + 1;				      \
      char* __new = __builtin_alloca (__len);				      \
      (char*) memcpy (__new, __old, __len);				      \
    }))

/* Return an alloca'd copy of at most N bytes of string.  */
# define strndupa(s, n)							      \
  (__extension__							      \
    ({									      \
      const char* __old = (s);					      \
      size_t __len = strnlen (__old, (n));				      \
      char* __new = __builtin_alloca (__len + 1);			      \
      __new[__len] = '\0';						      \
      (char*) memcpy (__new, __old, __len);				      \
    }))
#endif

/* Find the first occurrence of C in S.  */
__EXTERN char* strchr __P ((const char* __s, int __c));
/* Find the last occurrence of C in S.  */
__EXTERN char* strrchr __P ((const char* __s, int __c));

#ifdef __USE_GNU
/* This function is similar to `strchr'.  But it returns a pointer to
   the closing NUL byte in case C is not found in S.  */
extern char *strchrnul (__const char *__s, int __c)
     __THROW __attribute_pure__ __nonnull ((1));
#endif

/* Return the length of the initial segment of S which
   consists entirely of characters not in REJECT.  */
__EXTERN size_t strcspn __P ((const char* __s, const char* __reject));
/* Return the length of the initial segment of S which
   consists entirely of characters in ACCEPT.  */
__EXTERN size_t strspn __P ((const char* __s, const char* __accept));
/* Find the first occurrence in S of any character in ACCEPT.  */
__EXTERN char* strpbrk __P ((const char* __s, const char* __accept));
/* Find the first occurrence of NEEDLE in HAYSTACK.  */
__EXTERN char* strstr __P ((const char* __haystack, const char* __needle));

#ifdef __USE_GNU
/* Similar to `strstr' but this function ignores the case of both strings.  */
__EXTERN char* __strcasestr __P ((const char* __haystack,
				  const char* __needle));
__EXTERN char* strcasestr __P ((const char* __haystack,
			        const char* __needle));
#endif

/* Divide S into tokens separated by characters in DELIM.  */
__EXTERN char* strtok __P ((char* __s,
			    const char* __delim));

/* Divide S into tokens separated by characters in DELIM.  Information
   passed between calls are stored in SAVE_PTR.  */
__EXTERN char* __strtok_r __P ((char* __s,
			        const char* __delim,
			        char** __save_ptr));
#if defined __USE_POSIX || defined __USE_MISC
__EXTERN char* strtok_r __P ((char* __s,
			      const char* __delim,
			      char** __save_ptr));
#endif

#ifdef __USE_GNU
/* Find the first occurrence of NEEDLE in HAYSTACK.
   NEEDLE is NEEDLELEN bytes long;
   HAYSTACK is HAYSTACKLEN bytes long.  */
__EXTERN void* memmem __P ((const void* __haystack, size_t __haystacklen,
			    const void* __needle, size_t __needlelen));

/* Copy N bytes of SRC to DEST, return pointer to bytes after the
   last written byte.  */
__EXTERN void* __mempcpy __P ((void*  __dest,
			       const void*  __src, size_t __n));
__EXTERN void* mempcpy __P ((void*  __dest,
			     const void*  __src, size_t __n));
#endif


/* Return the length of S.  */
__EXTERN size_t strlen __P ((const char* __s));

#ifdef	__USE_GNU
/* Find the length of STRING, but scan at most MAXLEN characters.
   If no '\0' terminator is found in that many characters, return MAXLEN.  */
__EXTERN size_t strnlen __P ((const char* __string, size_t __maxlen));
#endif


/* Return a string describing the meaning of the `errno' code in ERRNUM.  */
__EXTERN char* strerror __P ((int __errnum));
#ifdef	__USE_MISC
/* Reentrant version of `strerror'.  If a temporary buffer is required, at
   most BUFLEN bytes of BUF will be used.  */
__EXTERN char* __strerror_r __P ((int __errnum, char* __buf, size_t __buflen));
__EXTERN char* strerror_r __P ((int __errnum, char* __buf, size_t __buflen));
#endif

/* We define this function always since `bzero' is sometimes needed when
   the namespace rules does not allow this.  */
__EXTERN void __bzero __P ((void* __s, size_t __n));
__EXTERN void _bzero __P ((void* __s, unsigned long __n));

__EXTERN void __bcopy __P ((const void* __src, void* __dest, size_t __n));
__EXTERN void _bcopy __P ((const void* __src, void* __dest,
			   unsigned long __n));

#if defined __USE_BSD || defined __USE_XOPEN_EXTENDED
/* Copy N bytes of SRC to DEST (like memmove, but args reversed).  */
__EXTERN void bcopy __P ((const void* __src, void* __dest, size_t __n));

/* Set N bytes of S to 0.  */
__EXTERN void bzero __P ((void* __s, size_t __n));

/* Compare N bytes of S1 and S2 (same as memcmp).  */
__EXTERN int bcmp __P ((const void* __s1, const void* __s2, size_t __n));

/* Find the first occurrence of C in S (same as strchr).  */
__EXTERN char* index __P ((const char* __s, int __c));

/* Find the last occurrence of C in S (same as strrchr).  */
__EXTERN char* rindex __P ((const char* __s, int __c));

/* Return the position of the first bit set in I, or 0 if none are set.
   The least-significant bit is position 1, the most-significant 32.  */
__EXTERN int __ffs __P ((int __i)) __attribute__ ((const));
__EXTERN int ffs __P ((int __i)) __attribute__ ((const));

/* The following two functions are non-standard but necessary for non-32 bit
   platforms.  */
# ifdef	__USE_GNU
__EXTERN int ffsl __P ((long int __l)) __attribute__ ((const));
#  ifdef __GNUC__
__extension__ __EXTERN int ffsll __P ((long long int __ll))
     __attribute__ ((const));
#  endif
# endif

/* These are the internal interfaces to the above functions.  */
__EXTERN int __ffss __P ((short int __s)) __attribute__ ((const));
__EXTERN int __ffsl __P ((long int __l)) __attribute__ ((const));

/* Compare S1 and S2, ignoring case.  */
__EXTERN int __strcasecmp __P ((const char* __s1, const char* __s2));
__EXTERN int strcasecmp __P ((const char* __s1, const char* __s2));

/* Compare no more than N chars of S1 and S2, ignoring case.  */
__EXTERN int strncasecmp __P ((const char* __s1, const char* __s2,
			     size_t __n));
#endif /* Use BSD or X/Open Unix.  */

#ifdef	__USE_BSD
/* Return the next DELIM-delimited token from *STRINGP,
   terminating it with a '\0', and update *STRINGP to point past it.  */
__EXTERN char* strsep __P ((char** __stringp,
			  const char* __delim));
#endif

#ifdef	__USE_GNU
/* Compare S1 and S2 as strings holding name & indices/version numbers.  */
__EXTERN int __strverscmp __P ((const char* __s1, const char* __s2));
__EXTERN int strverscmp __P ((const char* __s1, const char* __s2));

/* Return a string describing the meaning of the signal number in SIG.  */
__EXTERN char* strsignal __P ((int __sig));

/* Copy SRC to DEST, returning the address of the terminating '\0' in DEST.  */
__EXTERN char* __stpcpy __P ((char* __dest,
			    const char* __src));
__EXTERN char* stpcpy __P ((char* __dest,
			  const char* __src));

/* Copy no more than N characters of SRC to DEST, returning the address of
   the last character written into DEST.  */
__EXTERN char* __stpncpy __P ((char* __dest,
			     const char* __src, size_t __n));
__EXTERN char* stpncpy __P ((char* __dest,
			   const char* __src, size_t __n));

/* Sautee STRING briskly.  */
__EXTERN char* strfry __P ((char* __string));

/* Frobnicate N bytes of S.  */
__EXTERN void* memfrob __P ((void* __s, size_t __n));

# ifndef basename
/* Return the file name within directory of FILENAME.  We don't
   declare the function if the `basename' macro is available (defined
   in <libgen.h>) which makes the XPG version of this function
   available.  */
__EXTERN char* basename __P ((const char* __filename));
# endif
#endif

/* All inline stuff is currently disabled.  There is no measurable
   performance goal and we run into a lot of problems.  */
#if 0
#if defined __GNUC__ && __GNUC__ >= 2
# if defined __OPTIMIZE__ && !defined __OPTIMIZE_SIZE__ && !defined __cplusplus
/* When using GNU CC we provide some optimized versions of selected
   functions from this header.  There are two kinds of optimizations:

   - machine-dependent optimizations, most probably using inline
     assembler code; these might be quite expensive since the code
     size can increase significantly.
     These optimizations are not used unless the symbol
	__USE_STRING_INLINES
     is defined before including this header.

   - machine-independent optimizations which do not increase the
     code size significantly and which optimize mainly situations
     where one or more arguments are compile-time constants.
     These optimizations are used always when the compiler is
     taught to optimize.

   One can inhibit all optimizations by defining __NO_STRING_INLINES.  */

/* Get the machine-dependent optimizations (if any).  */
#  include <bits/string.h>

/* The test string/test-common fails if the optimization macro for stpcpy
   is turned on.  Trying to track down the bug will cause it to disappear,
   i. e. it only shows up in the mammut source file.  Until we find a 
   reason (and remembering that stpcpy is often used in the libc) we turn
   it off here.  */
#ifndef _HAVE_STRING_ARCH_stpcpy
# define _HAVE_STRING_ARCH_stpcpy
#endif

/* These are generic optimizations which do not add too much inline code.  */
#  include <bits/string2.h>
# endif
#endif
#endif /* not 0 */

#ifdef __USE_MISC
__EXTERN char* strlwr __P ((char* string));
__EXTERN char* strupr __P ((char* string));
/* CAUTION: there are assumptions elsewhere in the code that strrev()
   reverses in-place
 */
__EXTERN char* strrev __P ((char* string));

/* FIXME: Do these four lads belong to wany standard?  */
__EXTERN int stricmp __P (( const char* , const char*));
__EXTERN int strnicmp __P (( const char* , const char* , size_t ));
__EXTERN int strcmpi __P (( const char* , const char*));
__EXTERN int strncmpi __P (( const char* , const char* , size_t ));
#endif

/* BSD? */
__EXTERN size_t strlcpy __P ((char *dst, const char *src, size_t siz));
__EXTERN size_t strlcat __P ((char *dst, const char *src, size_t siz));

__END_DECLS

#endif /* _STRING_H */
