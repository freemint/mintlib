#ifndef _SETJMP_H
#define _SETJMP_H

#ifndef _COMPILER_H
#include <compiler.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __TURBOC__

#  ifdef __68881__
typedef char jmp_buf[12 * 4 + 5 * 12];
#  else
typedef char *jmp_buf[12];
#  endif

#else /* __TURBOC__ */

typedef long jmp_buf[14]; /* retaddr, 12 regs, sigmask */

#endif /* __TURBOC__ */

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

#ifndef __MINT__
# ifndef __cplusplus
__EXTERN int catch __PROTO((jmp_buf id, int (*fn )(void )));
__EXTERN void throw __PROTO((jmp_buf id, int rv));
# endif
#endif

#ifdef __cplusplus
}
#endif

#endif /* _SETJMP_H */
