/*  fpathconf.c -- MiNTLib.
    Copyright (C) 2001 Frank Naumann <fnaumann@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/


#include <errno.h>
#include <limits.h>
#include <unistd.h>
#include <mint/mintbind.h>
#include "lib.h"

#define UNLIMITED	(0x7fffffffL)

long
__fpathconf (int fd, int var)
{
	switch(var) {
	case _PC_PIPE_BUF: {
		struct stat st;
		long r;
		
		r = fstat (fd, &st);
		if (r < 0)
			return r;
		
		return st.st_blksize;
	}
	default:
		/* The only way to determine whether -1 signifies an error
		   or is "no limit", is to set errno to 0, and check for
		   a possible error after the call again.  */
		__set_errno (EINVAL);
		return -1;
	}
}
weak_alias (__fpathconf, fpathconf)
