/*  sigpending.c -- MiNTLib.
    Copyright (C) 2000 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.	By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <errno.h>
#include <mintbind.h>
#include <signal.h>

int
__sigpending (set)
	sigset_t *set;
{
  	if (!set) {
    		__set_errno (EINVAL);
    		return -1;
  	}
  	(void) sigemptyset (set);
  	*set = Psigpending();
  	return 0;
}
weak_alias (__sigpending, sigpending)
