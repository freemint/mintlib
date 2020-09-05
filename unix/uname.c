/*  uname.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <errno.h>
#include <sys/systeminfo.h>
#include <sys/utsname.h>
#include <string.h>

int __uname(struct utsname *info)
{
	if (info == 0)
	{
		__set_errno(EFAULT);
		return -1;
	}

	/*
	 * assumes that if sysinfo(SI_SYSNAME) fails, the other will fail, too
	 */
	if (sysinfo(SI_SYSNAME, info->sysname, sizeof (info->sysname)) < 0)
	{
		if (errno != ENOSYS)
			return -1;
		strcpy(info->sysname, "atari");
		strcpy(info->nodename, "localhost");
		strcpy(info->release, "1.0");
		strcpy(info->version, "1.0");
		strcpy(info->machine, "m68k");
		return 0;
	}
	sysinfo(SI_HOSTNAME, info->nodename, sizeof(info->nodename));
	sysinfo(SI_RELEASE, info->release, sizeof(info->release));
	sysinfo(SI_VERSION, info->version, sizeof(info->version));
	sysinfo(SI_PLATFORM, info->machine, sizeof(info->machine));
#ifdef _UTSNAME_DOMAIN_LENGTH
	sysinfo(SI_DOMAINNAME, info->domainname, sizeof(info->domainname));
#endif
#ifdef _UTSNAME_ARCHITECTURE_LENGTH
	sysinfo(SI_ARCHITECTURE, info->architecture, sizeof(info->architecture));
#endif

	return 0;
}
weak_alias (__uname, uname)
