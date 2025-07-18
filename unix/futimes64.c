/*  futimes.c -- MiNTLib, 64bit version.
    Copyright (C) 2019 Thorsten Otto <admin@tho-otto.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <errno.h>
#include <utime.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <mint/mintbind.h>
#include <unistd.h>
#include "lib.h"

/* There is no use faking odd seconds or fractional parts here.  The
 * operating system doesn't support for now.
 */
int __futimes64 (int fd, const struct timeval64 tvp[2])
{
	struct _mutimbuf settime;
	struct _mutimbuf* tset = NULL;
	long retval;

	if (tvp)
	{
		unsigned long *tp = (unsigned long*) &(settime.modtime);
		*tp =  __dostime (tvp[1].tv_sec);
		tp = (unsigned long*) &(settime.actime);
		*tp = __dostime (tvp[0].tv_sec);
		
		tset = &settime;
	}

	/* Try Fcntl.  */
	retval = Fcntl (fd, tset, FUTIME);
	if (retval == -ENOSYS) {
		/* Even that failed, fall back into Fdatime.  */
		_DOSTIME modtime;
		_DOSTIME *dtime;
	        
	    if (tset) {
	    	dtime = (_DOSTIME *) &tset->modtime;
		} else {
			modtime.time = Tgettime();
			modtime.date = Tgetdate();
			dtime = &modtime;
		}
		
		retval = Fdatime (dtime, fd, 1);
	}

	if (retval != 0) {
		__set_errno (-(int)retval);
		return -1;
	}
	
	return 0;
}
