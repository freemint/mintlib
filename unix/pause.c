/* public domain pause(), by ers */

#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <mint/mintbind.h>

#include "lib.h"

int
__pause (void)
{
	if (__mint) {
		(void) Pause();
		__set_errno (ERESTART);
		return -1;
	}

	/* do nothing for TOS */
	__set_errno (EINTR);
	return -1;
}
weak_alias (__pause, pause)
