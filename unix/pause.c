/* public domain pause(), by ers */

#include <mintbind.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>

extern int __mint;

#include "lib.h"

int
__pause()
{
	if (__mint)
	  {
	    (void)Pause();
	    __set_errno (ERESTART);
	  }
	/* do nothing for TOS */
	__set_errno (EINTR);
	return -1;
}

weak_alias (__pause, pause)
