
#include <errno.h>
#include <limits.h>
#include <mint/mintbind.h>
#include <sys/types.h>
#include <sys/ioctl.h>

#include "lib.h"

int
__ftruncate (int fd, off_t length)
{
	long r;

	r = Fcntl (fd, &length, FTRUNCATE);
	if (r < 0) {
		__set_errno (-r);
		return -1;
	}
	return 0;
}
weak_alias (__ftruncate, ftruncate)
