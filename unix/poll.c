/*  poll.c -- MiNTLib.
    Copyright (C) 2000 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.	By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <errno.h>
#include <limits.h>
#include <mint/mintbind.h>
#include <sys/poll.h>
#include <sys/time.h>

int
__poll (struct pollfd *fds, unsigned long int nfds, __int32_t __timeout)
{
	long int retval;
	unsigned long timeout = (unsigned long) __timeout;

	if (__timeout < 0) {
		timeout = ~0;
	}

	retval = Fpoll (fds, nfds, timeout);
	if (retval != -ENOSYS) {
		if (retval < 0) {
			__set_errno (-retval);
			return -1;
		}
	} else {
		/* We must emulate the call via Fselect ().  First task is to
		   set up the file descriptor masks.	*/
		unsigned long rfds = 0;
		unsigned long wfds = 0;
		unsigned long xfds = 0;
		register unsigned long int i;
		register struct pollfd* pfds = fds;
		unsigned long early_out = 0;

		for (i = 0; i < nfds; i++) {
			pfds[i].revents = 0;

			/* Older than 1.19 can't do more than 32 file descriptors.
			 * And we'd only get here if we're a very old kernel anyway.
			 */
			if (pfds[i].fd >= 32) {
				pfds[i].revents = POLLNVAL;
				continue;
			}

#define LEGAL_FLAGS \
	(POLLIN | POLLPRI | POLLOUT | POLLRDNORM | POLLWRNORM | POLLRDBAND | POLLWRBAND)

			if ((pfds[i].events | LEGAL_FLAGS) != LEGAL_FLAGS) {
				pfds[i].revents = POLLNVAL;
				continue;
			}

			if (pfds[i].events & (POLLIN | POLLRDNORM))
				rfds |= (1L << (pfds[i].fd));
			if (pfds[i].events & POLLPRI)
				xfds |= (1L << (pfds[i].fd));
			if (pfds[i].events & (POLLOUT | POLLWRNORM))
				wfds |= (1L << (pfds[i].fd));
		}

		if (__timeout < 0) { 
			retval = Fselect (0L, &rfds, &wfds, &xfds);
		} else if (timeout == 0) {
			retval = Fselect (1L, &rfds, &wfds, &xfds);
		} else if (timeout < USHRT_MAX) {
			/* The manpage Fselect(2) says that timeout is
			   signed.  But it is really unsigned.  */
			retval = Fselect (timeout, &rfds, &wfds, &xfds);
		} else {
			/* Thanks to the former kernel hackers we have
			   to loop in order to simulate longer timeouts
			   than USHRT_MAX.  */
			unsigned long saved_rfds, saved_wfds, saved_xfds;
			unsigned short int this_timeout;
			int last_round = 0;

			saved_rfds = rfds;
			saved_wfds = wfds;
			saved_xfds = xfds;

			do {
				if ((unsigned long) timeout > USHRT_MAX)
					this_timeout = USHRT_MAX;
				else {
					this_timeout = timeout;
					last_round = 1;
				}

				retval = Fselect (this_timeout, &rfds, &wfds,
							&xfds);

				if (retval != 0)
					break;

				timeout -= this_timeout;

				/* I don't know whether we can rely on the
				   masks not being clobbered on timeout.  */
				rfds = saved_rfds;
				wfds = saved_wfds;
				xfds = saved_xfds;
			} while (!last_round);
		}

		/* Now fill in the results in struct pollfd.	*/
		for (i = 0; i < nfds; i++) {
			/* Older than 1.19 can't do more than 32 file descriptors. */
			if (pfds[i].fd >= 32)
				continue;
			if (rfds & (1L << (pfds[i].fd)))
				pfds[i].revents |= (pfds[i].events & (POLLIN | POLLRDNORM));
			if (wfds & (1L << (pfds[i].fd)))
				pfds[i].revents |= (pfds[i].events & (POLLOUT | POLLWRNORM));
			if (xfds & (1L << (pfds[i].fd)))
				pfds[i].revents |= (pfds[i].events & POLLPRI);
		}

		if (retval < 0) {
			__set_errno (-retval);
			return -1;
		}
	}

	return retval;
}
weak_alias (__poll, poll)
