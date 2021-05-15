/*  sigsuspend.c -- MiNTLib.
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
#include <stddef.h>

__typeof__(sigsuspend) __sigsuspend;

int
__sigsuspend (const sigset_t* signalmask)
{
  	Psigpause (*signalmask);
  	__set_errno (EINTR);
  	return -1;
}
weak_alias (__sigsuspend, sigsuspend);
