/*  getitimer.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <stdlib.h>
#include <sys/time.h>

#include "lib.h"

int 
__getitimer (enum __itimer_which which, struct itimerval* old)
{
	return setitimer (which, NULL, old);
}
weak_alias (__getitimer, getitimer)
