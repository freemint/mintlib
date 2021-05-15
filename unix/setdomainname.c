/*  setdomainname.c -- MiNTLib.
    Copyright (C) 2001 Frank Naumann <fnaumnn@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <errno.h>
#include <stdlib.h>
#include <mint/sysctl.h>
#include <sys/types.h>
#include <unistd.h>

__typeof__(setdomainname) __setdomainname;

int
__setdomainname (const char *name, size_t namelen)
{
	int mib[2];

	if (!name) {
		__set_errno (EINVAL);
		return -1;
	}

	mib[0] = CTL_KERN;
	mib[1] = KERN_DOMAINNAME;

	if (sysctl(mib, 2, NULL, NULL, name, namelen) == -1)
		return -1;

	return 0;
}
weak_alias (__setdomainname, setdomainname)
