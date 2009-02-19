/*
 * Fdirfd implemented by Alan Hourihane <alanh@fairlite.co.uk>
 */
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include <limits.h>
#include <dirent.h>
#include <errno.h>
#include <mint/mintbind.h>
#include "lib.h"

int
__dirfd (DIR *dir)
{
	int r;
	
	if (!dir) {
		__set_errno(EBADF);
		return -1;
	}

	r = Fdirfd(dir->handle);

	if (r < 0) {
		__set_errno(-r);
		return -1;
	}

	return r;
}
weak_alias (__dirfd, dirfd)
