/*  sigprocmask.c -- MiNTLib.
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

int
__sigprocmask (int how, const sigset_t* set, sigset_t* oset)
{
	int retval = 0;
  	long oldmask = 0L;

  	if (set == NULL) {
        /*
         * If set is NULL, then the signal mask is unchanged (i.e., how is ignored),
         * but the current value of the signal mask is nevertheless returned in oldset (if
         * it is not NULL).
         */
        if (oset != NULL)
            *oset = Psigblock(0);
        return retval;
  	}
  	
  	switch (how) {
    		case SIG_BLOCK:
      			oldmask = Psigblock (*set);
      			break;
    		case SIG_UNBLOCK:
      			oldmask = Psigblock (0L);
      			(void) Psigsetmask (oldmask & ~(*set));
      			break;
    		case SIG_SETMASK:
      			oldmask = Psigsetmask (*set);
      			break;
	    	default:
      			__set_errno (EINVAL);
      			retval = -1;
  	}
  	
  	if (oset) 
  		*oset = oldmask;
  		
  	return retval;
}
weak_alias (__sigprocmask, sigprocmask)
