/*
 * lockf(3) and flock(2) emulation for MiNT by Dave Gymer
 * Placed in the public domain; do with me as you will!
 */

#include <unistd.h>
#include <fcntl.h>
#include "lib.h"

int
__lockf (int fd, int cmd, long size)
{
	return __do_lock (fd, cmd, size, 1);
}
weak_alias (__lockf, lockf)
