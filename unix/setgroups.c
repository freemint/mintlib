/*  setgroups.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <errno.h>
#include <grp.h>
#include <sys/types.h>
#include <mint/mintbind.h>

int
__setgroups (size_t count, gid_t *groups)
{
	int r;

	r = Psetgroups (count, groups);
	if (r < 0) {
		if (r == -EACCES)
			r = -EPERM;
		__set_errno (-r);
		return -1;
	}

	return 0;
}
weak_alias (__setgroups, setgroups)
