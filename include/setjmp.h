
#ifndef _SETJMP_H
#define _SETJMP_H 1

#ifndef	_FEATURES_H
# include <features.h>
#endif

__BEGIN_DECLS


typedef long jmp_buf[14]; /* retaddr, 12 regs, sigmask */

/* Store the calling environment in ENV, also saving the signal mask.
   Return 0.  */
extern int setjmp	(jmp_buf);

/* Jump to the environment saved in ENV, making the
   `setjmp' call there return VAL, or 1 if VAL is 0.  */
extern void longjmp	(jmp_buf, int);


/* Use the same type for `jmp_buf' and `sigjmp_buf'.
   The `__mask_was_saved' flag determines whether
   or not `longjmp' will restore the signal mask.  */
typedef jmp_buf sigjmp_buf;

/* Store the calling environment in ENV, also saving the
   signal mask if SAVEMASK is nonzero.  Return 0.
   This is the internal name for `sigsetjmp'.  */
extern int sigsetjmp  (sigjmp_buf env, int savemask);
extern int siglongjmp (sigjmp_buf env, int val);


#ifdef __USE_BSD
/* Store the calling environment in ENV, not saving the signal mask.
   Return 0.  */
#define _setjmp(__jb)		sigsetjmp(__jb, 0)
#define setjmp(__jb)		sigsetjmp(__jb, 1)

static inline void
_longjmp (sigjmp_buf env, int val)
{
	siglongjmp(env, val);
}

#endif /* __USE_BSD */

#ifdef	__USE_POSIX
#define setjmp(__jb)		(sigsetjmp(__jb, 1))
#endif

#ifndef	setjmp
#define setjmp(__jb)		(sigsetjmp(__jb, 0))
#endif


__END_DECLS

#endif /* _SETJMP_H */
