/*  poll.c -- MiNTLib.
    Copyright (C) 2000 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.	By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

/* Currently this file emulates XPG4 poll and is the base for the
   select() implementation.  Future kernel versions that support
   the poll io primitive are already prepared.

   For now that Fpoll is not available we still fall back into Fselect.
   An open question is what should happen in case TIMEOUT is negative.
   The current implementation casts TIMEOUT to unsigned long and thus
   silently converts negative TIMEOUTS to large ones.
   
   The prepared implementation for poll assumes that the kernel will
   emulate the poll primitive by means of select for file systems that
   do not support it.

   Poll the file descriptors described by the NFDS structures starting at
   FDS.  If TIMEOUT is nonzero and not -1, allow TIMEOUT milliseconds for
   an event to occur; if TIMEOUT is -1, block until an event occurs.
   Returns the number of file descriptors with events, zero if timed out,
   or -1 for errors.  */

#include <sys/poll.h>
#include <errno.h>
#include <mintbind.h>
#include <sys/time.h>
#include <limits.h>

int
__poll (struct pollfd *fds, unsigned long int nfds, __int32_t __timeout)
{
	long int retval;
	unsigned long timeout = (unsigned long) __timeout;
#ifdef Fpoll
	static int must_emulate = 0;

	if (!must_emulate) {
		retval = Fpoll (fds, nfds, timeout);
		if (retval < 0) {
			if (retval != -ENOSYS) {
				__set_errno (-retval);
				return -1;
			} else
				must_emulate = 1;
		}
	}
#endif /* not Fpoll.  */

	{
		/* We must emulate the call via Fselect ().  First task is to
		   set up the file descriptor masks.	*/
		unsigned long rfds = 0;
		unsigned long wfds = 0;
		unsigned long xfds = 0;
		register unsigned long int i;
		register struct pollfd* pfds = fds;

		for (i = 0; i < nfds; i++) {
			if (pfds[i].fd > 31) {
				/* We lose.  Any better idea than EINVAL?  */
				__set_errno (EINVAL);
				return -1;
			}

#define LEGAL_FLAGS \
	(POLLIN | POLLPRI | POLLOUT | POLLERR | POLLHUP | POLLNVAL | POLLRDNORM | POLLWRNORM)

			if ((pfds[i].events | LEGAL_FLAGS) != LEGAL_FLAGS) {
				/* Not supported.  */
				__set_errno (EINVAL);
				return -1;
			}

			if (pfds[i].events & POLLIN)
				rfds |= (1L << (pfds[i].fd));
			if (pfds[i].events & POLLPRI)
				xfds |= (1L << (pfds[i].fd));
			if (pfds[i].events & POLLOUT)
				wfds |= (1L << (pfds[i].fd));
		}

		if (timeout == ~0) { /* Which is -1 as unsigned long.  */
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

		if (retval < 0) {
			__set_errno (-retval);
			return -1;
		}

		/* Now fill in the results in struct pollfd.	*/
		for (i = 0; i < nfds; i++) {
			if (rfds & (1L << (pfds[i].fd)))
				pfds[i].revents = POLLIN;
			else
				pfds[i].revents = 0;
			if (xfds & (1L << (pfds[i].fd)))
				pfds[i].revents |= POLLPRI;
			if (wfds & (1L << (pfds[i].fd)))
				pfds[i].revents |= POLLOUT;
		}

	} /* must emulate.  */

	return retval;
}
weak_alias (__poll, poll)
