/*  stime64.c -- MiNTLib.
    Copyright (C) 2025 Thorsten Otto

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include "lib.h"

int __stime64(const __time64_t *now)
{
	struct timeval64 tv;

	if (now == NULL) {
		__set_errno (EINVAL);
		return -1;
	}

	tv.tv_sec = *now;
	tv.tv_usec = 0;
	return __settimeofday64(&tv, (struct timezone *) 0);
}
