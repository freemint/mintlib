/*
 * close(): close a file. written by Eric R. Smith and placed in the public
 * domain
 */

#include <osbind.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include "lib.h"

int
__close(fd)
	int fd;
{
	int r;

	r = Fclose(fd);
	if (r < 0) {
		errno = -r;
		return -1;
	}
	fd = __OPEN_INDEX(fd);
	if (fd >= 0 && fd < __NHANDLES) {
		__open_stat[fd].status = FH_UNKNOWN;
		__open_stat[fd].flags = 0;
	}
	return 0;
}
weak_alias (__close, close)
