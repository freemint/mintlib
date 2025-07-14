/* Copyright (C) 1996, 1997, 1998 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Ulrich Drepper <drepper@cygnus.com>, 1996.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

#include <errno.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/select.h>

__typeof__(pselect) __pselect;

/* Check the first NFDS descriptors each in READFDS (if not NULL) for read
   readiness, in WRITEFDS (if not NULL) for write readiness, and in EXCEPTFDS
   (if not NULL) for exceptional conditions.  If TIMEOUT is not NULL, time out
   after waiting the interval specified therein.  Additionally set the sigmask
   SIGMASK for this call.  Returns the number of ready descriptors, or -1 for
   errors.  */
int
__pselect (int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, const struct timespec *timeout, const sigset_t *sigmask)
{
  struct timeval tval;
  int retval;
  sigset_t savemask;

  /* Change nanosecond number to microseconds.  This may loose
     precision and therefore the `pselect` should be available.  But
     for now it is hardly found.  */
  if (timeout != NULL)
    TIMESPEC_TO_TIMEVAL (&tval, timeout);

  /* The setting and restoring of the signal mask and the select call
     should be an atomic operation.  This can't be done without kernel
     help.  */
  __sigprocmask (SIG_SETMASK, sigmask, &savemask);
  retval = select (nfds, readfds, writefds, exceptfds,
		     timeout != NULL ? &tval : NULL);
  __sigprocmask (SIG_SETMASK, &savemask, NULL);

  return retval;
}
weak_alias (__pselect, pselect)
