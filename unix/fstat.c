#include <limits.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>	/* for FSTAT */

#include <ctype.h>
#include <errno.h>
#include <osbind.h>
#include <mintbind.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <support.h>
#include "lib.h"

extern ino_t __inode;

/* 
 * fstat: if we're not running under MiNT, this is pretty bogus.
 * what we can really find is:
 * modification time: via Fdatime()
 * file size: via Fseek()
 * fortunately, these are the things most programs are interested in.
 * BUG: passing an invalid file descriptor gets back a stat structure for
 * a tty.
 *
 * The internal function __do_fstat takes a third flag that determines
 * whether timestamps are needed or not.
 */

int
__do_fstat (fd, st, gettime)
	int fd;
	struct stat *st;
	int gettime;
{
	long retval;
	struct xattr xattr;

	/* Try to use FSTAT64 fcntl first.  */
	retval = Fcntl (fd, (long) st, FSTAT64);
	
	if (retval == 0)
		return 0;
	else if (retval != -ENOSYS && retval != -EINVAL) {
		__set_errno (-retval);
		return -1;
	}
	

	memset (&xattr, 0, sizeof xattr);
	memset (st, 0, sizeof *st);
	if ((retval = Fcntl(fd, (long) &xattr, FSTAT)) != -ENOSYS) {
		if (retval != 0) {
			__set_errno (-retval);
			return -1;
		}
		
		st->st_mode = (mode_t) xattr.st_mode;
		st->st_ino = (ino_t) xattr.st_ino;
		st->st_dev = (dev_t) xattr.st_dev;
		st->st_rdev = (dev_t) xattr.st_rdev;
		st->st_nlink = (nlink_t) xattr.st_nlink;
		st->st_uid = (uid_t) xattr.st_uid;
		st->st_gid = (gid_t) xattr.st_gid;
		st->st_size = (off_t) xattr.st_size;
		st->st_blksize = (unsigned long int) xattr.st_blksize;
		st->st_blocks = 
			(off_t) (((off_t) xattr.st_blocks 
				 * (off_t) xattr.st_blksize) >> 9);
		if (gettime) {
			__UNIXTIME (xattr.st_mtime);
			__UNIXTIME (xattr.st_atime);
			__UNIXTIME (xattr.st_ctime);
			st->st_mtime = (time_t) xattr.st_mtime;
			st->st_atime = (time_t) xattr.st_atime;
			st->st_ctime = (time_t) xattr.st_ctime;
		}
		st->st_flags = (unsigned long int) 0;
		return 0;
	} else {
		long oldplace;
		_DOSTIME timeptr;
		short magic;

		retval = Fdatime(&timeptr, fd, 0);
		if (retval < 0) {			/* assume TTY */
			st->st_mode = S_IFCHR | 0600;
			st->st_flags = 0;
			if (gettime)
				st->st_mtime = st->st_ctime = st->st_atime =
					time ((time_t*) 0) - 2;
					
			st->st_size = 0;
		} else {
			if (gettime)
				st->st_mtime = st->st_atime = st->st_ctime =
					__unixtime(timeptr.time, timeptr.date);
			st->st_mode = S_IFREG | 0644;	/* this may be false */
			st->st_flags = 0;		/* because this is */

		/* get current file location */
			oldplace = Fseek(0L, fd, SEEK_CUR);
			if (oldplace < 0) { /* can't seek -- must be pipe */
				st->st_mode = S_IFIFO | 0644;
				st->st_size = 1024;
			} else {
				/* Go to end of file.  */
				retval = Fseek(0L, fd, SEEK_END);
				st->st_size = retval;
				/* Go to start of file.  */
				(void) Fseek (0L, fd, SEEK_SET);
				/* Check for executable file.  */
				if (Fread (fd, 2, (char *)&magic) == 2) {
					if (magic == 0x601a 
					    || magic == 0x2321)
						st->st_mode |= 0111;
				}
				(void) Fseek (oldplace, fd, SEEK_SET);
			}
		}

/* all this stuff is likely bogus as well. sigh. */
		st->st_dev = Dgetdrv ();
		st->st_rdev = 0;
		st->st_uid = getuid ();
		st->st_gid = getgid();
		st->st_blksize = 1024;
		/* Note: most Unixes measure st_blocks in 512 byte units.  */
		st->st_blocks = (st->st_size + 511) / 512;
		st->st_ino = __inode++;
		st->st_nlink = 1;
	
	}
	
	return 0;
}

int
__fstat (fd, st)
	int fd;
	struct stat *st;
{
	return __do_fstat (fd, st, 1);
}
weak_alias (__fstat, fstat)
