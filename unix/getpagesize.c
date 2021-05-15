/*  getpagesize.c -- MiNTLib.
    Copyright (C) 2001 Frank Naumann <fnaumnn@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <stdlib.h>
#include <mint/sysctl.h>
#include <unistd.h>

__typeof__(getpagesize) __getpagesize;
__typeof__(sysctl) __sysctl;

#define DEF_PAGESIZE 8192	/* default page size for TOS */

int
__getpagesize (void)
{
	int call[2] = { CTL_HW, HW_PAGESIZE };
	int val;
	unsigned long valsize = sizeof (val);
	int ret;

	ret = __sysctl (call, 2, &val, &valsize, NULL, 0);
	if (ret == 0)
		return val;

	return DEF_PAGESIZE;
}
weak_alias (__getpagesize, getpagesize)
