/*
 * Fchdir implemented by Alan Hourihane <alanh@fairlite.co.uk>
 */
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <support.h>
#include <time.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <mint/mintbind.h>

#include "lib.h"

int
__fchdir (int fd)
{
	int r;

	if (fd < 0) {
		__set_errno(EBADF);
		return -1;
	}

	r = Fchdir(fd);
	if (r < 0) {
		__set_errno(-r);
		return -1;
	}

	return 0;
}
weak_alias (__fchdir, fchdir)
