/*  utimes.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <errno.h>
#include <utime.h>
#include <stdlib.h>
#include <sys/time.h>
#include "lib.h"

#if __GNUC_PREREQ(7, 0)
# pragma GCC diagnostic ignored "-Wnonnull-compare"
#endif

int __utimes64(const char *filename, const struct timeval64 tvp[2])
{
	struct utimbuf64 utimbuf;

	if (filename == NULL) {
		__set_errno (EFAULT);
		return -1;
	}

	if (tvp == NULL)
		return __utime64 (filename, NULL);

	utimbuf.actime = tvp[0].tv_sec;
	utimbuf.modtime = tvp[1].tv_sec;

	return __utime64(filename, &utimbuf);
}
