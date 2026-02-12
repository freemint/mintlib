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
			    const char* __src)) __THROW __nonnull ((1, 2));
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
__EXTERN int strcmp __P ((const char* __s1, const char* __s2)) __THROW __attribute_pure__ __nonnull ((1, 2));
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
__EXTERN size_t strlen __P ((const char* __s)) __THROW __attribute_pure__ __nonnull ((1));

#ifdef	__USE_GNU
/* Find the length of STRING, but scan at most MAXLEN characters.
   If no '\0' terminator is found in that many characters, return MAXLEN.  */
__EXTERN size_t strnlen __P ((const char* __string, size_t __maxlen)) __THROW __attribute_pure__ __nonnull ((1));
#endif


/* Return a string describing the meaning of the `errno' code in ERRNUM.  */
__EXTERN char* strerror __P ((int __errnum));
#if defined __USE_XOPEN2K || defined __USE_MISC
/* Reentrant version of `strerror'.
   There are 2 flavors of `strerror_r', GNU which returns the string
   and may or may not use the supplied temporary buffer and POSIX one
   which fills the string into the buffer.
   To use the POSIX version, -D_XOPEN_SOURCE=600 or -D_POSIX_C_SOURCE=200112L
   without -D_GNU_SOURCE is needed, otherwise the GNU version is
   preferred.  */
# if defined __USE_XOPEN2K && !defined __USE_GNU
/* Fill BUF with a string describing the meaning of the `errno' code in
   ERRNUM.  */
#  ifdef __REDIRECT_NTH
extern int __REDIRECT_NTH (strerror_r,
			   (int __errnum, char *__buf, size_t __buflen),
			   __xpg_strerror_r) __nonnull ((2));
#  else
extern int __xpg_strerror_r (int __errnum, char *__buf, size_t __buflen)
     __THROW __nonnull ((2));
#   define strerror_r __xpg_strerror_r
#  endif
# else
/* If a temporary buffer is required, at most BUFLEN bytes of BUF will be
   used.  */
extern char *strerror_r (int __errnum, char *__buf, size_t __buflen)
     __THROW __nonnull ((2));
extern char *__strerror_r (int __errnum, char *__buf, size_t __buflen)
     __THROW __nonnull ((2));
# endif
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


/*
 * inline versions of some functions.
 */
extern __inline __attribute__((__gnu_inline__)) size_t __inline_strlen(const char *scan);
extern __inline __attribute__((__gnu_inline__)) size_t __inline_strlen(const char *scan)
{
	const char *start = scan;

	while (*scan++ != '\0')
		continue;
	return scan - start - 1;
}
#ifdef __OPTIMIZE__
#define strlen(s) __inline_strlen(s)
#endif


extern __inline __attribute__((__gnu_inline__)) int __inline_strcmp(const char *s1, const char *s2);
extern __inline __attribute__((__gnu_inline__)) int __inline_strcmp(const char *s1, const char *s2)
{
#ifdef __mcoldfire__
	unsigned long cmp;
	unsigned long tmp;

	__asm__ __volatile__(
	   "1:\n"
		" mvz.b 	(%[s2])+,%[tmp]\n"
		" mvz.b 	(%[s1])+,%[cmp]\n"
		" beq.s 	1f\n"
		" cmp.l 	%[tmp],%[cmp]\n"
		" beq.s 	1b\n"
	   "1:\n"
		" sub.l 	%[tmp],%[cmp]\n"
	: [cmp]"=d"(cmp), [tmp]"=d"(tmp), [s1]"+a"(s1), [s2]"+a"(s2)
	:
	: "cc");
	return cmp;
#else
	unsigned long cmp;
	unsigned long tmp;

	__asm__ __volatile__(
		" moveq #0,%[tmp]\n"
		" moveq #0,%[cmp]\n"
	   "1:\n"
		" move.b 	(%[s2])+,%[tmp]\n"
		" move.b	(%[s1])+,%[cmp]\n"
		" beq.s 	1f\n"
		" cmp.b 	%[tmp],%[cmp]\n"
		" beq.s 	1b\n"
	   "1:\n"
		" sub.l 	%[tmp],%[cmp]\n"
	: [cmp]"=d"(cmp), [tmp]"=d"(tmp), [s1]"+a"(s1), [s2]"+a"(s2)
	:
	: "cc");
	return cmp;
#endif
}
#ifdef __OPTIMIZE__
#define strcmp(s1, s2) __inline_strcmp(s1, s2)
#endif

extern __inline __attribute__((__gnu_inline__)) char *__inline_strcpy(char *dest, const char *src);
extern __inline __attribute__((__gnu_inline__)) char *__inline_strcpy(char *dest, const char *src)
{
	char *dscan = dest;

	__asm__ __volatile__(
	   "1:\n"
		" move.b	(%[src])+,(%[dest])+\n"
		" bne.s 	1b\n"
	: [src]"+a"(src), [dest]"+a"(dscan)
	:
	: "cc" AND_MEMORY);
	return dest;
}
#ifdef __OPTIMIZE__
#define strcpy(dest, src) (__builtin_constant_p(src) && strlen(src) < 2 ? __builtin_strcpy(dest, src) : __inline_strcpy(dest, src))
#endif

__END_DECLS

#endif /* _STRING_H */
