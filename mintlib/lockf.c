/*
 * lockf(3) and flock(2) emulation for MiNT by Dave Gymer
 * Placed in the public domain; do with me as you will!
 */

#include <unistd.h>
#include <fcntl.h>
#include "lib.h"

int
lockf(fd, cmd, size)
	int fd;
	int cmd;
	long size;
{
	return _do_lock(fd, cmd, size, 1);
}

