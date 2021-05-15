/*
 * lockf(3) and flock(2) emulation for MiNT by Dave Gymer
 * Placed in the public domain; do with me as you will!
 */

#include <unistd.h>
#include <fcntl.h>
#include "lib.h"

__typeof__(lockf) __lockf;

int
__lockf (int fd, int cmd, __off_t size)
{
	return __do_lock (fd, cmd, size, 1);
}
weak_alias (__lockf, lockf)
