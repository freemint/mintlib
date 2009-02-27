/* sleep -- sleep for a specified number of seconds */
/* written by Eric R. Smith and placed in the public domain */
/* extensively rehacked by entropy for mint >= 0.95, still public domain */

#include <errno.h>
#include <limits.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <mint/mintbind.h>

#include "lib.h"

/* _clock() has a rez of CLOCKS_PER_SEC ticks/sec */
clock_t _clock (void);

static unsigned long
_alarm (unsigned long secs)
{
	unsigned long r;

#ifndef __MSHORT__
	if (secs > ((unsigned long) (LONG_MAX/1000)))
		secs = ((unsigned long) (LONG_MAX/1000));
#endif
	r = Talarm((long) secs);

	return (unsigned long) r;
}

static void
alarm_catch (long signum)
{
	(void) signum;

	return;
}

unsigned int
__sleep (unsigned int n)
{
	long stop;
	long old_alarm_func;
	long old_sigmask;
	unsigned long alarm_sec;
	long remain;

	if (__mint) {
		if (n == 0)
			return 0;
		/* Clear any existing alarm, but save its expire time.
		   Then block all signals and save original mask.
		   Install our alarm handler, and remask (since Psignal()
		   just unmasked SIGALRM.)
		*/
		alarm_sec = (long) Talarm(0L);
		old_sigmask = Psigblock(~0L);
		old_alarm_func = Psignal(SIGALRM, (long)alarm_catch);
		(void) Psigblock(~0L);
		/* Figure out when we would normally wake up */
		stop = _clock() + n * CLOCKS_PER_SEC;
		/* But only sleep as long as the original alarm clock */
		if (alarm_sec && (alarm_sec < n))
			(void) _alarm(alarm_sec);
		else
			(void) _alarm((unsigned long) n);
		/* Go to sleep with the original mask but always
		   allow SIGALRM or we might never wake up.
		*/
		Psigpause(old_sigmask & ~(sigmask(SIGALRM)));
		/* Cancel any time left on the alarm clock */
		(void) _alarm(0L);
		/* Eat any alarms that occurred before we cancelled.
		   The Syield ensure we enter the kernel and handle the
		   signal.
		*/
		(void) Psignal(SIGALRM, (long) alarm_catch);
		(void) Syield();
		/* Remask again after the Psignal() */
		(void) Psigblock(~0L);
		remain = (stop - _clock()) 
			  / (long) CLOCKS_PER_SEC;
		if (alarm_sec) {
			/* Restore the original timer (or if it expired,
			   post the signal now)
			*/
			alarm_sec -= ((long) n - remain);
			if (alarm_sec <= 0)
				(void) Pkill(Pgetpid(), SIGALRM);
			else
				(void) _alarm(alarm_sec);
		}
		/* Restore the original alarm handler (which also
		   allows it to be delivered!)  Then restore the
		   original signal mask (if the signal handler
		   does a longjmp() we might lose).
		*/
		(void) Psignal(SIGALRM, (long) old_alarm_func);
		(void) Psigsetmask(old_sigmask);
		(void) Syield();
		return ((remain > 0) ? (unsigned) remain : 0);
	}
	else {
		stop = _clock() + n * CLOCKS_PER_SEC;
		while (_clock() < stop)
			;
	}
	return 0;
}
weak_alias (__sleep, sleep)
