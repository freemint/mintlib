/*  chroot.c -- MiNTLib.
    Copyright (C) 1999, 2000 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <unistd.h>
#include <errno.h>
#include <mintbind.h>

/* This call used to emulate chroot() by calling chdir() instead.
   This doesn't make any sense to me since chroot() actually doesn't
   change the current directory.  */
int __chroot (const char* path)
{
	int retval = Dchroot (path);
	if (retval < 0) {
		__set_errno (retval);
		return -1;
	}
  	return 0;
}
weak_alias (__chroot, chroot)
