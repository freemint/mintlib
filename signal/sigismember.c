/*  sigismember.c -- MiNTLib.
    Copyright (C) 2000 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.	By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <errno.h>
#include <signal.h>

int
sigismember (set, signo)
  	sigset_t *set;
  	int signo;
{
  	if (!set || signo <= 0 || signo >= __NSIG) {
    		__set_errno (EINVAL);
    		return -1;
  	}
  	return __sigismember (set, signo);
}
