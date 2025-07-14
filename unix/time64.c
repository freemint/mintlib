/*  time64.c -- MiNTLib.
    64bit version of time()
    Copyright (C) 2025 Thorsten Otto

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <time.h>
#include <sys/time.h>
#include "lib.h"

__time64_t __time64(__time64_t *buf)
{
	struct timeval64 now;

	if (__gettimeofday64(&now, NULL) != 0)
		return ((__time64_t) -1);

	if (buf)
		*buf = now.tv_sec;

	return now.tv_sec;
}
