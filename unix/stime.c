/*  stime.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <errno.h>
#include <time.h>
#include <sys/time.h>

int
__stime (const time_t *now)
{
	struct timeval tv;

	if (now == (const time_t *) 0) {
		__set_errno (EINVAL);
		return -1;
	}

	tv.tv_sec = *now;
	tv.tv_usec = 0;
	return settimeofday (&tv, (struct timezone *) 0);
}
weak_alias (__stime, stime)
