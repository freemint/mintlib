/*  getpgid.c -- MiNTLib.
    Copyright (C) 2001 Frank Naumann <fnaumann@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/


#include <unistd.h>
#include <sys/types.h>

int __bsd_getpgrp (int pid);

pid_t
__getpgid (pid_t pid)
{
	return __bsd_getpgrp (pid);
}
weak_alias (__getpgid, getpgid)
