/*  ppoll.c -- MiNTLib.
    Copyright (C) 2024 Thorsten Otto

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.	By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <signal.h>
#include <sys/select.h>
#include <sys/poll.h>
#include <sys/time.h>

__typeof__(ppoll) __ppoll;

int
__ppoll (struct pollfd *fds, nfds_t nfds, const struct timespec *tmo, const sigset_t *sigmask)
{
	sigset_t savemask;
	int retval;
	__int32_t timeout = tmo == NULL ? -1 : tmo->tv_sec * 1000 + (tmo->tv_nsec + 999999) / 1000000;

  /* The setting and restoring of the signal mask and the select call
     should be an atomic operation.  This can't be done without kernel
     help.  */
	if (sigmask != NULL)
		__sigprocmask(SIG_SETMASK, sigmask, &savemask);
	retval = poll(fds, nfds, timeout);
	if (sigmask != NULL)
		__sigprocmask(SIG_SETMASK, &savemask, NULL);
	return retval;
}
weak_alias (__ppoll, ppoll)
