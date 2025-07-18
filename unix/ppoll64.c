/*  ppoll.c -- MiNTLib.
    Copyright (C) 2024 Thorsten Otto

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.	By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <sys/select.h>
#include <sys/poll.h>
#include <sys/time.h>
#include <errno.h>
#include "lib.h"

int __ppoll64 (struct pollfd *fds, nfds_t nfds, const struct timespec64 *timeout, const sigset_t *sigmask)
{
	if (timeout)
	{
		struct timespec ts;

		__int32_t high = timeout->tv_sec >> 32;
		if (high != 0)
		{
			__set_errno(EINVAL);
			return -1;
		}
		ts.tv_sec = timeout->tv_sec;
		ts.tv_nsec = timeout->tv_nsec;
		return ppoll(fds, nfds, &ts, sigmask);
	}
	return ppoll(fds, nfds, NULL, sigmask);
}
