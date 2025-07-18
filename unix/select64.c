/*  select.c -- MiNTLib.
    Copyright (C) 2000 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <sys/types.h>
#include <sys/time.h>
#include <sys/param.h>
#include <sys/poll.h>
#include <alloca.h>
#include <string.h>
#include <errno.h>
#include "lib.h"

int __select64 (int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval64 *timeout)
{
	if (timeout)
	{
		struct timeval tv;
		int ret;

		__int32_t high = timeout->tv_sec >> 32;
		if (high != 0)
		{
			__set_errno(EINVAL);
			return -1;
		}
		tv.tv_sec = timeout->tv_sec;
		tv.tv_usec = timeout->tv_usec;
		ret = select(nfds, readfds, writefds, exceptfds, &tv);
		timeout->tv_sec = tv.tv_sec;
		timeout->tv_usec = tv.tv_usec;
		return ret;
	}
	return select(nfds, readfds, writefds, exceptfds, NULL);
}
