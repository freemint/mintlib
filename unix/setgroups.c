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

#ifdef HAVE_WEAK_SYMBOLS
__typeof__(setgroups) __setgroups;
# define setgroups __setgroups
#endif


int setgroups (size_t count, const gid_t *groups)
{
	int r;

	if ((long)count < 0 || (count > 0 && !groups)) {
		r = -EINVAL;
	} else {
		size_t i;
		unsigned short gids[count];
		for (i = 0; i < count; i++)
			gids[i] = groups[i];
		r = Psetgroups (count, gids);
	}
	if (r < 0) {
		if (r == -EACCES)
			r = -EPERM;
		__set_errno (-r);
		return -1;
	}

	return 0;
}

#undef setgroups
weak_alias (__setgroups, setgroups)
