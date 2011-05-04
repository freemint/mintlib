
#ifndef _SETJMP_H
#define _SETJMP_H 1

#ifndef	_FEATURES_H
# include <features.h>
#endif

__BEGIN_DECLS


typedef long jmp_buf[14]; /* retaddr, 12 regs, sigmask */


#ifndef __STRICT_ANSI__

typedef jmp_buf sigjmp_buf;

extern int sigsetjmp  (sigjmp_buf env, int savemask);
extern int siglongjmp (sigjmp_buf env, int val);

#ifdef __USE_BSD
/* BUG: we lose if __USE_BSD && __STRICT_ANSI__ */
#define _setjmp(__jb)		(sigsetjmp(__jb, 0))
#define setjmp(__jb)		(sigsetjmp(__jb, 1))

extern void longjmp(sigjmp_buf env, int val);

static inline void
_longjmp (sigjmp_buf env, int val)
{
	siglongjmp(env, val);
}

#endif /* __USE_BSD */

#endif /* __STRICT_ANSI__ */

#ifndef __USE_BSD
extern int setjmp	(jmp_buf);
extern void longjmp	(jmp_buf, int);
#endif /* not __USE_BSD */


__END_DECLS

#endif /* _SETJMP_H */
