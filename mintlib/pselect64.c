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
#include "lib.h"

int __pselect64(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, const struct timespec64 *timeout, const sigset_t *sigmask)
{
	struct timespec ts;

	if (timeout != NULL)
	{
		__int32_t high = timeout->tv_sec >> 32;
		if (high != 0)
		{
			__set_errno(EINVAL);
			return -1;
		}
		ts.tv_sec = timeout->tv_sec;
		ts.tv_nsec = timeout->tv_nsec;
		return pselect(nfds, readfds, writefds, exceptfds, &ts, sigmask);
	}
	return pselect(nfds, readfds, writefds, exceptfds, NULL, sigmask);
}
