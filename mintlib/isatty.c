/* from the original GCC TOS library by jrd */
/* this algorithm is due to Allan Pratt @ Atari.  Thanks Allan! */

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/ioctl.h>
#include <mint/mintbind.h>

#include "lib.h"

struct __open_file __open_stat[__NHANDLES];

int
__isatty (int fd)
{
	int handle = __OPEN_INDEX(fd);
	int rc, retval;
	long dummy;

	if ((handle < __NHANDLES) && (__open_stat[handle].status != FH_UNKNOWN))
		return (__open_stat[handle].status == FH_ISATTY);

	/* save 1 or 2 system calls (isatty gets called on every open...) */

	retval = Fcntl (fd, &dummy, TIOCGPGRP);
	if (retval == -ENOSYS) {
		long oldloc;

		/* save current location */
		oldloc = Fseek (0L, fd, SEEK_CUR);

		/* try to seek ahead one byte */
		if (Fseek (1L, fd, SEEK_CUR) != 0) {
			/* got either a file position or an error (usually
			 * EBADARG indicating a range error from trying to
			 * seek past EOF), so it is not a tty
			 */
			rc = 0;
			
			/* seek back to original location */
			(void) Fseek (oldloc, fd, SEEK_SET);
		}
		else  {
			rc = 1; /* yes, tty */
		}
	}
	else {
		rc = (retval == 0);
	}

	if (handle < __NHANDLES) {
		if (rc) {
			__open_stat[handle].status = FH_ISATTY;
			__open_stat[handle].flags = CRMOD|ECHO;
		}
		else {
			__open_stat[handle].status = FH_ISAFILE;
		}
	}

	/* return true, false, or error */
	return rc;
}
weak_alias (__isatty, isatty)
