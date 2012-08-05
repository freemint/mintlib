/*
 *	MACROS.H	commonly useful macros
 */

#ifndef	_MACROS_H
#define	_MACROS_H

#ifdef __GNUC__	
/* with GNUC we will use safe versions, these may look like that they
 * have overhead, but they do not -- trust me!
 */

/* absolute value for any type of number */
#define abs(a) \
    ({__typeof__ (a) _a = (a);     \
	      _a  < ((__typeof__ (a))0) ? -(_a) : _a; })

/* maximum and minumum for any type of number */
#define max(a,b) \
    ({__typeof__ (a) _a = (a); __typeof__ (b) _b = (b);  \
	      _a > _b ? _a : _b; })

#define min(a,b) \
    ({__typeof__ (a) _a = (a); __typeof__ (b) _b = (b);     \
	      _a < _b ? _a : _b; })

/* swap any objects (even identically typed structs!) */
/* WARNING: not safe */
#define swap(a,b) \
    ({__typeof__ (a) _t;  \
	      _t = (a); (a) = (b); (b) = _t; })

#else	/* be careful !! */

/* absolute value for any type of number */
#define	abs(x)		((x)<0?(-(x)):(x))

/* maximum and minumum for any type of number */
#define max(x,y)   	(((x)>(y))?(x):(y))
#define	min(x,y)   	(((x)<(y))?(x):(y))

/* swap any objects which can be XORed */
#define	swap(a,b)	((a)=(a)^((b)=(b)^((a)=(a)^(b))))

#endif /* __GNUC__ */

/* lo and hi byte of a word */
#define	lobyte(x)	(((unsigned char *)&(x))[1])
#define	hibyte(x)	(((unsigned char *)&(x))[0])

/* lo and hi word of a long */
#define	loword(x)	(((unsigned short *)&(x))[1])
#define	hiword(x)	(((unsigned short *)&(x))[0])

/* These are often useful.  Since this file is non-standard anyway we
   can afford to have them here.  Summary:
   
   	ROds(offset, x): Bit-rotate argument x of size s (one of
   	                 L for unsigned long, W for unsigned short
   	                 or B for unsigned char) by in direction d
   	                 (one of L for left or R for right) by
   	                 offset bits.
   
   The same macros are available with a 1 appended.  Semantics are
   the same except that offset is always 1.  */

#if defined(__GNUC__) && !defined(__mcoldfire__)
#define ROLL(offset, x)	\
({ unsigned long __arg = (x);	\
    __asm__ ("roll %2,%1": "=d" (__arg) : "0" (__arg), "d" (offset)); \
    __arg; })

#define RORL(offset, x)	\
({ unsigned long __arg = (x);	\
    __asm__ ("rorl %2,%1": "=d" (__arg) : "0" (__arg), "d" (offset)); \
    __arg; })

#define ROLW(offset, x)	\
({ unsigned short __arg = (x);	\
    __asm__ ("roll %2,%1": "=d" (__arg) : "0" (__arg), "d" (offset)); \
    __arg; })

#define RORW(offset, x)	\
({ unsigned short __arg = (x);	\
    __asm__ ("rorl %2,%1": "=d" (__arg) : "0" (__arg), "d" (offset)); \
    __arg; })

#define ROLB(offset, x)	\
({ unsigned char __arg = (x);	\
    __asm__ ("roll %2,%1": "=d" (__arg) : "0" (__arg), "d" (offset)); \
    __arg; })

#define RORB(offset, x)	\
({ unsigned char __arg = (x);	\
    __asm__ ("rorl %2,%1": "=d" (__arg) : "0" (__arg), "d" (offset)); \
    __arg; })

#define ROLL1(x)	\
({ unsigned long __arg = (x);	\
    __asm__ ("roll #1,%1": "=d" (__arg) : "0" (__arg)); \
    __arg; })

#define RORL1(x)	\
({ unsigned long __arg = (x);	\
    __asm__ ("roll #1,%1": "=d" (__arg) : "0" (__arg)); \
    __arg; })

#define ROLW1(x)	\
({ unsigned short __arg = (x);	\
    __asm__ ("roll #1,%1": "=d" (__arg) : "0" (__arg)); \
    __arg; })

#define RORW1(x)	\
({ unsigned short __arg = (x);	\
    __asm__ ("roll #1,%1": "=d" (__arg) : "0" (__arg)); \
    __arg; })

#define ROLB1(x)	\
({ unsigned char __arg = (x);	\
    __asm__ ("roll #1,%1": "=d" (__arg) : "0" (__arg)); \
    __arg; })

#define RORB1(x)	\
({ unsigned char __arg = (x);	\
    __asm__ ("roll #1,%1": "=d" (__arg) : "0" (__arg)); \
    __arg; })

#endif

#endif /* _MACROS_H */
