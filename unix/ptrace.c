/*  ptrace.c -- MiNTLib.
    Copyright (C) 2000 Frank Naumann <fnaumann@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <errno.h>
#include <stdio.h>
#include <sys/ptrace.h>
#include <mint/mintbind.h>

#ifdef __MSHORT__
#define int long
#endif

int
__ptrace (int request, pid_t pid, caddr_t addr, int data)
{
	int retval;
	long tmp;
	
	if ((request == PT_READ_I) || (request == PT_READ_D))
		data = (int) &tmp;
	
	retval = Ptrace (request, pid, addr, data);
	if (retval < 0) {
		__set_errno (-retval);
		retval = -1;
		if (errno == ENOSYS) {
			fputs ("This system does not support the Ptrace() syscall!", stderr);
		}
	} else if (retval == 0) {
		if ((request == PT_READ_I) || (request == PT_READ_D)) {
			__set_errno (0);
			retval = tmp;
		}
	}
  	return retval;
}
weak_alias (__ptrace, ptrace)
