/*  fchmod.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <errno.h>
#include <limits.h>
#include <stddef.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <mint/mintbind.h>

int
__fchmod (int fd, mode_t mode)
{
	int r;

	if (fd > SHRT_MAX)
	{
		__set_errno(EBADF);
		return -1;
	}
	r = Ffchmod(fd, mode);
	if (r != 0)
	{
		/*
		 * if the function is not available, silently ignore the error.
		 * we won't be able to set unix modes in SingleTOS, anyway.
		 */
		if (r != -ENOSYS)
		{
			__set_errno(-r);
			return -1;
		}
	}
	return 0;
}
weak_alias (__fchmod, fchmod)
