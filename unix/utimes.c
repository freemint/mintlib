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

int __utime (const char *_filename, const struct utimbuf *_tset);

/* There is no use faking odd seconds or fractional parts here.  The
 * operating system doesn't support for now.
 */
int
__utimes (const char *filename, struct timeval tvp[2])
{
	struct utimbuf utimbuf;

	if (filename == NULL) {
		__set_errno (EFAULT);
		return -1;
	}

	if (tvp == NULL)
		return __utime (filename, NULL);

	utimbuf.actime = tvp[0].tv_sec;
	utimbuf.modtime = tvp[1].tv_sec;

	return __utime (filename, &utimbuf);
}
weak_alias (__utimes, utimes)
