/*
 *	ctype.h		Character classification and conversion
 */

#ifndef _CTYPE_H
#define _CTYPE_H

#ifndef	_FEATURES_H
# include <features.h>
#endif

__BEGIN_DECLS

extern unsigned int* _ctype;

#define	_IScntrl	0x01		/* control character */
#define	_ISdigit	0x02		/* numeric digit */
#define	_ISupper	0x04		/* upper case */
#define	_ISlower	0x08		/* lower case */
#define	_ISspace	0x10		/* whitespace */
#define	_ISpunct	0x20		/* punctuation */
#define	_ISxdigit	0x40		/* hexadecimal */
#define _ISblank	0x80		/* blank */
#define _ISgraph	0x100		/* graph */
#define _ISprint	0x200		/* print */

extern int isalnum __P ((int c));
extern int isalpha __P ((int c));
#if defined(__USE_SVID) || defined(__USE_MISC)
extern int isascii __P ((int c));
extern int toascii __P ((int c));
#endif /* _POSIX_SOURCE */
extern int iscntrl __P ((int c));
extern int isdigit __P ((int c));
extern int isgraph __P ((int c));
extern int islower __P ((int c));
extern int isprint __P ((int c));
extern int ispunct __P ((int c));
extern int isspace __P ((int c));
extern int isupper __P ((int c));
extern int isxdigit __P ((int c));
#ifdef __USE_ISOC99
extern int isblank __P ((int c));
#endif
#ifdef __USE_SVID
extern int _toupper __P ((int c));
extern int _tolower __P ((int c));
#endif

#ifndef __cplusplus
#ifndef __NO_CTYPE
/* You will notice that 255 when passed to this macros will return
   the same value as 0.  This happens to be correct so we can
   cast to unsigned char.  */
#define	isalnum(c)	(_ctype[(unsigned char)((c) + 1)]&(_ISupper|_ISlower|_ISdigit))
#define	isalpha(c)	(_ctype[(unsigned char)((c) + 1)]&(_ISupper|_ISlower))
#if defined(__USE_SVID) || defined(__USE_MISC)
#define	isascii(c)	!((c)&~0x7F)
#define	toascii(c)	((c)&0x7F)
#endif /* SVID or MISC */
/* Problem: iscntrl(255) and iscntrl(EOF) should produce different values
   (IMHO this is nonsense).  For non-GNU compilers there is now way to
   implement that safely.  */
#ifndef __GNUC__
# define	iscntrl(c)	(((c) == -1) ? 0 : \
	(unsigned char) (c) == 255 ? 1 : \
	(_ctype[(unsigned char)((c) + 1)]&_IScntrl))
	
#else /* GNU C */
# define        iscntrl(c) \
  ({ int _c = (int) (c);   \
     _c == -1 ? 0 : \
     (unsigned char) (_c) == 255 ? 1 : _ctype[(unsigned char)(_c + 1)]&_IScntrl; })
     
#endif /* GNU C */

#define	isdigit(c)	(_ctype[(unsigned char)((c) + 1)]&_ISdigit)
#define	isgraph(c)	(_ctype[(unsigned char)((c) + 1)]&_ISgraph)
#define	islower(c)	(_ctype[(unsigned char)((c) + 1)]&_ISlower)
#define isprint(c)      (_ctype[(unsigned char)((c) + 1)]&_ISprint)
#define	ispunct(c)	(_ctype[(unsigned char)((c) + 1)]&_ISpunct)
#define	isspace(c)	(_ctype[(unsigned char)((c) + 1)]&_ISspace)
#define	isupper(c)	(_ctype[(unsigned char)((c) + 1)]&_ISupper)
#define	isxdigit(c)	(_ctype[(unsigned char)((c) + 1)]&_ISxdigit)

#ifdef __USE_ISOC99
#define isblank(c)	(_ctype[(unsigned char)((c) + 1)]&_ISblank)
#endif

#ifdef __USE_SVID
#ifdef __GNUC__
#  define _toupper(c) \
	({typeof(c) _c = (typeof(c)) (c);	\
		(islower(_c) ? ((_c) & (~0x20)) : _c); })
#  define _tolower(c) \
	({typeof(c) _c = (typeof(c)) (c);	\
		(isupper(_c) ? ((_c) | (0x20)) : _c); })
# else
#  define _toupper(c) \
	({int _c = (int) (c);	\
		(islower(_c) ? ((_c) & (~0x20)) : _c); })
#  define _tolower(c) \
	({int _c = (int) (c);	\
		(isupper(_c) ? ((_c) | (0x20)) : _c); })
# endif
#endif

#ifdef __USE_MINTLIB

/* Better don't use these macros.  I think I will remove them since
   they aren't mentioned in any standard, are they?  */
#ifdef __GNUC__
/* use safe versions */

#define toint(c)    \
    ({typeof(c) _c = (c);     \
	    (_c) < '0' || (_c) > '9' ? (_c) : \
	    (_c <= '9') ? (_c - '0') : (toupper(_c) - 'A' + 10); })
#define isodigit(c) \
    ({typeof(c) _c = (c);      \
	    (_c >='0') && (_c<='7'); })
#define iscymf(c)   \
    ({typeof(c) _c = (c);      \
	    isalpha(_c) || (_c == '_'); })
#define iscym(c)    \
    ({typeof(c) _c = (c);      \
	    isalnum(_c) || (_c == '_'); })

#else /* you know what */

#define toint(c)	\
	({ int _c = (int) (c);  \
		(_c) < 0 || (_c) > '9' ? (_c) : \
		(_c) <= '9' ? (_c) - '0' : toupper(_c) - 'A' + 10); })
#define isodigit(c)	\
	({ int _c = (int) (c);	\
		(_c) >= '0' && (_c) <='7' ); })
#define iscymf(c)	\
	({ int _c = (int) (c);	\
		(isalpha(_c) || ((_c) == '_') ); })
#define iscym(c)	\
	({ int _c = (int) (c);	\
		(isalnum(_c) || ((_c) == '_') ); })

#endif /* __GNUC__ */
#endif /* __USE_MISC */

#endif /* no __NO_CTYPE */
#endif /* no __cplusplus */

extern int toupper __P((int));
extern int tolower __P((int));

__END_DECLS

#endif /* _CTYPE_H */
