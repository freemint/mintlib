/*
 * tfork(function, argument): starts a new thread of execution running
 * in the same address space. The new thread gets its own 4K stack,
 * and starts at the address in "function" with "argument" on the stack,
 * i.e. as though the main program had a call like "function(argument)".
 * The main program continues executing, with tfork returning the process
 * i.d. of the child.
 * (if MiNT is not active, then the child runs to completion
 *  and the return value is the child's exit status; vfork() relies on
 *  this behavior)
 *
 * Note that parent and child share the same memory; this could cause
 * problems with some library calls, notably malloc().
 */

#include <compiler.h>
#include <mint/osbind.h>
#include <mint/basepage.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <support.h>
#include "lib.h"

#define SIZE 4096L


/* this is used by wait() and wait3() to retrieve the child's exit code */
long __waitval = -ENOENT;

/* and this is used to retrieve the child's time */
long __waittime = 0;

static void __CDECL
startup(register BASEPAGE *b)
{
	register int (*func)(long);
	register long arg;
	_setstack(((char *)b) + SIZE);
	func = (int (*)(long))b->p_dbase;
	arg = b->p_dlen;

	/* If this is a thread, it doesn't need
	 * own copy of the environment, right?
	 */
	Mfree(b->p_env);
	b->p_env = _base->p_env;

	/* copy from parents basepage for debuggers... */
	b->p_tbase = _base->p_tbase;
	b->p_tlen = _base->p_tlen;
	b->p_dbase = _base->p_dbase;
	b->p_dlen = _base->p_dlen;
	b->p_bbase = _base->p_bbase;
	b->p_blen = _base->p_blen;

	Pterm((*func)(arg));
}

/* use long instead of int so vfork works OK with -mshort */
long
tfork(int (*func)(long), long arg)
{
	register BASEPAGE *b;
	register long pid;
	register long savpending, savmask;
	register BASEPAGE *savbase;
	sighandler_t savhandler[NSIG];
	long now;
	int i;

	b = (BASEPAGE *)Pexec(PE_CBASEPAGE, 0L, "", 0L);
	(void)Mshrink(b, SIZE+256);
	b->p_tbase = (char *)startup;
	b->p_dbase = (char *)func;
	b->p_dlen = arg;
	b->p_hitpa = ((char *)b) + SIZE + 256;
 
	pid = Pexec(104, 0L, b, 0L);
	if (pid == -ENOSYS)
	{
		/* save the signal masks and signal handlers,
		 * the child may change them
		 */
		savpending = _sigpending;
		_sigpending = 0;
		savmask = _sigmask;
		_sigmask = 0;
		for (i = 0; i < NSIG; i++)
			savhandler[i] = _sig_handler[i];
		savbase = _base;
		_base = b;

		now = _clock();
		pid = Pexec(4, 0L, b, 0L);

		_base = savbase;
		/* restore signal stuff */
		for (i = 0; i < NSIG; i++)
			_sig_handler[i] = savhandler[i];
		_sigmask = savmask;
		_sigpending = savpending;
		if (pid >= 0) {
			long retval = pid;

		/* see the TOS algorithm for getpid() */
			pid = ((long)b) >> 8;
			__waitval = (pid << 16) | retval;
			raise(SIGCHLD);
			__waittime = _clock() - now;
			_childtime += __waittime;
		}
	}
	(void)Mfree(b->p_env);	/* free the memory */
	(void)Mfree(b);
	return pid;
}
