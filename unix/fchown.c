/*  fchown.c -- MiNTLib.
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
#include <unistd.h>
#include <sys/types.h>
#include <mint/mintbind.h>

int
__fchown (int fd, uid_t owner, gid_t group)
{
	int r;

#ifndef __MSHORT__
	if (fd > SHRT_MAX) {
		__set_errno (EBADF);
		return -1;
	}
#endif
	r = Ffchown (fd, owner, group);
	if (r != 0) {
		__set_errno (-r);
		return -1;
	}
	return 0;
}
weak_alias (__fchown, fchown)
