/*
 * _write: like write, but takes a long instead of an int. Written by
 * Eric R. Smith and placed in the public domain.
 */

/* BUG: under TOS, CRMOD doesn't work unless RAW is on or SIGINT is
 * being caught
 */

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <mint/mintbind.h>
#include "lib.h"


#ifdef __MSHORT__
long
#else
int
#endif
__write (int fd, const void *buf, size_t size)
{
	unsigned char c, *foo;
	unsigned flags;
	long r;
	struct xattr statbuf;
	_DOSTIME timebuf;

	if (__mint == 0 && isatty(fd)) {
		r = __OPEN_INDEX(fd);
		if (r < 0 || r >= __NHANDLES)
			r = __NHANDLES - 1;
		flags = __open_stat[r].flags;
		if ((flags & RAW) || _sig_handler[SIGINT] != SIG_DFL) {
			foo = (unsigned char *) buf;
			r = size;
			while (r-- > 0) {
				c = *foo++;
				if (c == '\n' && (flags & CRMOD))
					_console_write_byte(fd, '\r');
				_console_write_byte(fd, c);
			}
			return size;
		}
	}

	r = Fwrite(fd, size, buf);
	if (r < 0) {
		__set_errno (-r);
		return -1;
	}
	if (size && r == 0) {
	  if (__mint >= 9)
	    {
	      if ((r = Fcntl (fd, &statbuf, FSTAT)) < 0)
		{
		  __set_errno (-r);
		  return -1;
		}
	      if (((mode_t) statbuf.st_mode & S_IFMT) == S_IFREG)
		{
		  __set_errno (ENOSPC);
		  return -1;
		}
	    }
	  else if (Fdatime (&timebuf, fd, 0) == 0
		   && Fseek (0L, fd, SEEK_CUR) >= 0)
	    {
	      __set_errno (ENOSPC);
	      return -1;
	    }
	}

	return r;
}
weak_alias (__write, write)
