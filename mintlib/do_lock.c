/*
 * lockf(3) and flock(2) emulation for MiNT by Dave Gymer
 * Placed in the public domain; do with me as you will!
 */

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <mint/mintbind.h>
#include <sys/file.h>

#include "lib.h"


int
__do_lock (int fd, int cmd, long size, int whence)
{
	struct flock lock;
	int fcmd;
	long r;
	
	lock.l_whence = whence;
	lock.l_start = 0;
	lock.l_len = size;
	switch (cmd) {
		case F_ULOCK:
			lock.l_type = F_UNLCK;
			fcmd = F_SETLK;
			break;
		case F_TEST:
			lock.l_type = F_WRLCK;
			fcmd = F_GETLK;
			break;
		case F_TLOCK:
			lock.l_type = F_WRLCK;
			fcmd = F_SETLK;
			break;
		case F_LOCK:
			lock.l_type = F_WRLCK;
			if (__mint < 95)
				fcmd = F_SETLK;
			else
				fcmd = F_SETLKW;
			break;
		default:
			__set_errno (EINVAL);
			return -1;
	}
	if ((r = Fcntl(fd, &lock, fcmd)) < 0) {
		/* if the filesystem doesn't understand F_SETLKW, 
		   retry with F_SETLK */
		if ((r == -ENOSYS || r == -EINVAL) && fcmd == F_SETLKW) {
			while ((r = Fcntl(fd, &lock, F_SETLK)) == -ELOCKED)
				/* busy-wait...bletch */ ;
			if (r == 0)
				return 0;
		}
		__set_errno (-r);
		return -1;
	}
	return 0;
}
