
#ifndef _SETJMP_H
#define _SETJMP_H 1

#ifndef	_FEATURES_H
# include <features.h>
#endif

__BEGIN_DECLS


typedef long jmp_buf[14]; /* retaddr, 12 regs, sigmask */


#ifndef __STRICT_ANSI__

typedef jmp_buf sigjmp_buf;

__EXTERN int	sigsetjmp  __PROTO((sigjmp_buf env, int savemask));
__EXTERN int	siglongjmp __PROTO((sigjmp_buf env, int val));

#ifdef __USE_BSD
/* BUG: we lose if __USE_BSD && __STRICT_ANSI__ */
#define _setjmp(__jb)		(sigsetjmp(__jb, 0))
#define _longjmp(__jb,__v)	(siglongjmp(__jb, __v))
#define setjmp(__jb)		(sigsetjmp(__jb, 1))
#define longjmp(__jb,__v)	(siglongjmp(__jb, __v))
#endif /* __USE_BSD */

#endif /* __STRICT_ANSI__ */

#ifndef __USE_BSD
__EXTERN int	setjmp	__PROTO((jmp_buf));
__EXTERN void	longjmp	__PROTO((jmp_buf, int));
#endif /* not __USE_BSD */


__END_DECLS

#endif /* _SETJMP_H */
