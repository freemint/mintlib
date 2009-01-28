/*
 *	ISO C Standard: 4.7 SIGNAL HANDLING <signal.h>
 */

#ifndef _SIGNAL_H
#define _SIGNAL_H

#if !defined __need_sig_atomic_t && !defined __need_sigset_t
# define _SIGNAL_H
#endif

#ifndef _FEATURES_H
# include <features.h>
#endif

__BEGIN_DECLS

#include <bits/sigset.h>		/* __sigset_t, __sig_atomic_t.  */

/* An integral type that can be modified atomically, without the
   possibility of a signal arriving in the middle of the operation.  */
#ifndef __sig_atomic_t_defined
# if defined __need_sig_atomic_t || defined _SIGNAL_H
#  undef __need_sig_atomic_t
#  define __sig_atomic_t_defined 1
typedef __sig_atomic_t sig_atomic_t;
# endif
#endif

#ifndef __sigset_t_defined
# if defined __need_sigset_t || (defined _SIGNAL_H && defined __USE_POSIX)
#  undef __need_sigset_t
#  define __sigset_t_defined	1
typedef __sigset_t sigset_t;
# endif
#endif

#ifdef _SIGNAL_H

#include <bits/types.h>
#include <bits/signum.h>

#ifdef __USE_XOPEN
# ifndef pid_t
typedef __pid_t pid_t;
#  define pid_t pid_t
# endif
# ifndef uid_t
typedef __uid_t uid_t;
#  define uid_t uid_t
# endif
#endif	/* Unix98 */


typedef void __CDECL (*__sighandler_t) __PMT ((int signum));

/* The X/Open definition of `signal' specifies the SVID semantic.  Use
   the additional function `sysv_signal' when X/Open compatibility is
   requested.  */
__EXTERN __sighandler_t __sysv_signal __P ((int __sig,
					  __sighandler_t __handler));
#ifdef __USE_GNU
__EXTERN __sighandler_t sysv_signal __P ((int __sig, __sighandler_t __handler));
#endif

/* Set the handler for the signal SIG to HANDLER, returning the old
   handler, or SIG_ERR on error.
   By default `signal' has the BSD semantic.  */
#ifdef __USE_BSD
extern __sighandler_t signal __P ((int __sig, __sighandler_t __handler));
#else
/* Make sure the used `signal' implementation is the SVID version. */
# ifdef __REDIRECT
extern __sighandler_t __REDIRECT (signal,
				  __P ((int __sig, __sighandler_t __handler)),
				  __sysv_signal);
# else
#  define signal __sysv_signal
# endif
#endif

#ifdef __USE_XOPEN
/* The X/Open definition of `signal' conflicts with the BSD version.
   So they defined another function `bsd_signal'.  */
extern __sighandler_t bsd_signal __P ((int __sig, __sighandler_t __handler));
#endif

__EXTERN int		__kill	__P((int, int));
#ifdef __USE_POSIX
__EXTERN int		kill	__P((int, int));
#endif

#if defined __USE_BSD || defined __USE_XOPEN_EXTENDED
__EXTERN int		killpg	__P((int, int));
#endif

__EXTERN int		raise	__P((int sig));

#ifdef __USE_SVID
/* SVID names for the same things.  */
__EXTERN __sighandler_t ssignal __P ((int __sig, __sighandler_t __handler));
__EXTERN int gsignal __P ((int __sig));
#endif /* Use SVID.  */

#ifdef __USE_MISC
/* Print a message describing the meaning of the given signal number.  */
__EXTERN void psignal __P ((int __sig, __const char *__s));
#endif /* Use misc.  */

/* The `sigpause' function has two different interfaces.  The original
   BSD definition defines the argument as a mask of the signal, while
   the more modern interface in X/Open defines it as the signal
   number.  We go with the BSD version unless the user explicitly
   selects the X/Open version.  */
__EXTERN int __sigpause __P ((long __sig_or_mask, int __is_sig));

#ifdef __USE_BSD
/* Set the mask of blocked signals to MASK,
   wait for a signal to arrive, and then restore the mask.  */
__EXTERN int sigpause __P ((int __mask));
# define sigpause(mask) __sigpause ((mask), 0)
#else
# ifdef __USE_XOPEN
/* Remove a signal from the signal mask and suspend the process.  */
#  define sigpause(sig) __sigpause ((sig), 1)
# endif
#endif

#ifdef __USE_MISC
# define _SIGSET_INDEX(__sig)	(__sig / 32)
# define _SIGSET_BITPOS(__sig)	(__sig % 32)
# define _SIGSET_MAX_INDEX	(__NSIG / 32)
#endif

#ifdef __USE_BSD
#ifdef __MSHORT__
__EXTERN long	sigsetmask  __P((long mask));
__EXTERN long	sigblock    __P((long mask));
__EXTERN long	__sigblock    __P((long mask));
#else
__EXTERN int	sigsetmask  __P((long mask));
__EXTERN int	sigblock    __P((long mask));
__EXTERN int	__sigblock    __P((long mask));
#endif
/* a mask for signals */
#define sigmask(__sig) __sigmask(__sig)
#endif /* BSD */

#ifdef __USE_MISC
# define NSIG __NSIG
#endif

#ifdef __USE_GNU
typedef __sighandler_t sighandler_t;
#endif

/* 4.4 BSD uses the name `sig_t' for this.  */
#ifdef __USE_BSD
typedef __sighandler_t sig_t;
#endif

#ifdef __USE_POSIX

# ifdef __USE_POSIX199309
/* We need `struct timespec' later on.  */
#  define __need_timespec
#  include <time.h>
# endif /* !__USE_POSIX199309 */

__EXTERN int	sigaddset   __P((sigset_t *set, int signo));
__EXTERN int	sigdelset   __P((sigset_t *set, int signo));
__EXTERN int	sigemptyset __P((sigset_t *set));
__EXTERN int	sigfillset  __P((sigset_t *set));
__EXTERN int	sigismember __P((sigset_t *set, int signo));

# ifdef __USE_GNU
/* Return non-empty value is SET is not empty.  */
__EXTERN int sigisemptyset __P ((__const sigset_t *__set));

/* Build new signal set by combining the two inputs set using logical AND.  */
__EXTERN int sigandset __P ((sigset_t *__set, __const sigset_t *__left,
			   __const sigset_t *__right));

/* Build new signal set by combining the two inputs set using logical OR.  */
__EXTERN int sigorset __P ((sigset_t *__set, __const sigset_t *__left,
			  __const sigset_t *__right));
# endif /* GNU */

/* Get the system-specific definitions of `struct sigaction'
   and the `SA_*' and `SIG_*'. constants.  */
# include <bits/sigaction.h>

__EXTERN int	sigprocmask __P((int how, const sigset_t *set,
				 sigset_t *oset));
__EXTERN int	__sigprocmask __P((int how, const sigset_t *set,
				   sigset_t *oset));
__EXTERN int	sigsuspend  __P((const sigset_t *sigmask));
__EXTERN int	__sigsuspend  __P((const sigset_t *sigmask));
__EXTERN int    sigaction   __P((int, const struct sigaction *,
                                 struct sigaction *));
__EXTERN int    __sigaction   __P((int, const struct sigaction *,
                                   struct sigaction *));
__EXTERN int	sigpending  __P((sigset_t *set));

#if 0
/* Should these four friends be implemented somehow?  */

/* Select any of pending signals from SET or wait for any to arrive.  */
extern int sigwait __P ((__const sigset_t *__set, int *__sig));

# ifdef __USE_POSIX199309
/* Select any of pending signals from SET and place information in INFO.  */
extern int sigwaitinfo __P ((__const sigset_t *__set, siginfo_t *__info));

/* Select any of pending signals from SET and place information in INFO.
   Wait the imte specified by TIMEOUT if no signal is pending.  */
extern int sigtimedwait __P ((__const sigset_t *__set, siginfo_t *__info,
			      __const struct timespec *__timeout));

/* Send signal SIG to the process PID.  Associate data in VAL with the
   signal.  */
extern int sigqueue __P ((__pid_t __pid, int __sig,
			  __const union sigval __val));
#endif

# endif	/* Use POSIX 199306.  */

#endif /* Use POSIX.  */

#if defined __USE_BSD
extern const char* const _sys_siglist[__NSIG];
extern const char* const sys_siglist[__NSIG];

/* Structure passed to `sigvec'.  */
struct sigvec {
    __sighandler_t sv_handler;  /* Signal handler.  */
    int sv_mask;	   /* Mask of signals to be blocked.  */
    int sv_flags;	   /* Flags (see below).  */
#define sv_onstack sv_flags /* 4.2 BSD compatibility.  */
};
  
/* Bits in `sv_flags'.  */
#define SV_ONSTACK   0x4000 /* Take the signal on the signal stack.  */
#define SV_INTERRUPT 0x4000 /* Do not restart system calls.  */ 
#define SV_RESETHAND 0x8000 /* Reset handler to SIG_DFL on receipt.  */

#if 0
/* If VEC is non-NULL, set the handler for SIG to the `sv_handler'
   member of VEC.  The signals in `sv_mask' will be blocked while the
   handler runs.
   If the SV_RESETHAND bit is set in `sv_flags', the handler for SIG
   will be reset to SIG_DFL before `sv_handler' is entered.  If OVEC
   is non-NULL, it is fille in with the old information for SIG.  */
extern int sigvec (int __sig, __const struct sigvec *__vec,
		   struct sigvec *__ovec) __THROW;
#endif
#endif


/* Get machine-dependent `struct sigcontext' and signal subcodes.  */
# include <bits/sigcontext.h>

/* Restore the state saved in SCP.  */
__EXTERN void	sigreturn __P ((struct sigcontext* __unused));

#endif /*  use BSD.  */


#if defined (__USE_BSD) || defined (__USE_XOPEN_EXTENDED)

/* If INTERRUPT is nonzero, make signal SIG interrupt system calls
   (causing them to fail with EINTR); if INTERRUPT is zero, make system
   calls be restarted after signal SIG.  */
__EXTERN int siginterrupt __P ((int __sig, int __interrupt));

# include <bits/sigstack.h>
# ifdef __USE_XOPEN
#  include <ucontext.h>
# endif

#if 0
/* FIXME: sigstack and sigaltstack would be quite useful!  */

/* Run signals handlers on the stack specified by SS (if not NULL).
   If OSS is not NULL, it is filled in with the old signal stack status.
   This interface is obsolete and on many platform not implemented.  */
extern int sigstack (struct sigstack *__ss, struct sigstack *__oss) __THROW;

/* Alternate signal handler stack interface.
   This interface should always be preferred over `sigstack'.  */
extern int sigaltstack (__const struct sigaltstack *__ss,
			struct sigaltstack *__oss) __THROW;
#endif

#endif /* use BSD or X/Open Unix.  */

#ifdef __USE_UNIX98
/* Simplified interface for signal management.  */

/* Add SIG to the calling process' signal mask.  */
extern int sighold __P ((int __sig));

/* Remove SIG from the calling process' signal mask.  */
extern int sigrelse __P ((int __sig));

/* Set the disposition of SIG to SIG_IGN.  */
extern int sigignore __P ((int __sig));

/* Set the disposition of SIG.  */
extern __sighandler_t sigset __P ((int __sig, __sighandler_t __disp));

#endif /* use Unix98 */

/* This is used by the library itself.  */
extern const char* const __signal_names[__NSIG];

__END_DECLS

#endif /* _SIGNAL_H */
