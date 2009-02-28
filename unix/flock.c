/*
 * lockf(3) and flock(2) emulation for MiNT by Dave Gymer
 * Placed in the public domain; do with me as you will!
 */

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/file.h>

#include "lib.h"

int
__flock (int fd, int op)
{
	int cmd;
	int retval;
	
	switch (op & ~LOCK_NB) 
	  {
	  case LOCK_SH:
	    cmd = (op & LOCK_NB) ? F_TLOCK : F_LOCK; /* broken, F_RDLCK */
	    break;
	  case LOCK_EX:
	    cmd = (op & LOCK_NB) ? F_TLOCK : F_LOCK; /* broken, F_WRLCK */
	    break;
	  case LOCK_UN:
	    cmd = F_ULOCK;
	    break;
	  default:
  	    __set_errno (EINVAL);
	    return -1;
	  }
	retval = __do_lock(fd, cmd, 0L, 0);
	if (retval == -ELOCKED && (op & LOCK_NB))
	  {
	    __set_errno (EWOULDBLOCK);
	    return -1;
	  }
	return retval;
}
weak_alias (__flock, flock)
