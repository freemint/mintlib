/*  sysctl.c -- MiNTLib.
    Copyright (C) 2001 Frank Naumann <fnaumnn@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <errno.h>
#include <mint/mintbind.h>
#include <mint/sysctl.h>

#ifdef __MSHORT__
#error sysctl not 16bit int clean
#endif

int
__sysctl (int *name, unsigned long namelen, void *old, unsigned long *oldlenp,
          const void *new, unsigned long newlen)
{
	int ret;
	
	ret = Psysctl (name, namelen, old, oldlenp, new, newlen);
	if (ret < 0) {
		__set_errno (-ret);
		return -1;
	}
	return ret;
}
weak_alias (__sysctl, sysctl)
