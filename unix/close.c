/*
 * close(): close a file. written by Eric R. Smith and placed in the public
 * domain
 */

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <mint/osbind.h>
#include "lib.h"

int
__close (int fd)
{
	int r;

	r = Fclose(fd);
	if (r < 0) {
		__set_errno (-r);
		return -1;
	}
	fd = __OPEN_INDEX(fd);
	if (fd < __NHANDLES) {
		__open_stat[fd].status = FH_UNKNOWN;
		__open_stat[fd].flags = 0;
	}
	return 0;
}
weak_alias (__close, close)
