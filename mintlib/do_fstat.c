/*
 * $Id$
 */

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <support.h>
#include <time.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <mint/mintbind.h>

#include "lib.h"

long
Ffstat (short fd, struct stat *st, int exact)
{
	long r;

	/* first try the native syscall */
	r = Ffstat64 (fd, st);
	if (r == -ENOSYS) {

		/* try the stat64 fcntl() */
		r = Fcntl (fd, st, FSTAT64);
		if (r == -ENOSYS || r == -EINVAL) {

			/* fall back to the xattr fcntl() */
			struct xattr xattr;

			r = Fcntl (fd, &xattr, FSTAT);
			if (r == 0) {
				unsigned short *ptr;

				__bzero (st, sizeof (*st));

				st->st_dev = (dev_t) xattr.st_dev;
				st->st_ino = (ino_t) xattr.st_ino;
				st->st_mode = (mode_t) xattr.st_mode;
				st->st_nlink = (nlink_t) xattr.st_nlink;
				st->st_uid = (uid_t) xattr.st_uid;
				st->st_gid = (gid_t) xattr.st_gid;
				st->st_rdev = (dev_t) xattr.st_rdev;

				if (exact) {
					ptr = (unsigned short *) &xattr.st_mtime;
					st->st_mtime = __unixtime (ptr[0], ptr[1]);
					ptr = (unsigned short *) &xattr.st_atime;
					st->st_atime = __unixtime (ptr[0], ptr[1]);
					ptr = (unsigned short *) &xattr.st_ctime;
					st->st_ctime = __unixtime (ptr[0], ptr[1]);
				}

				st->st_size = (off_t) xattr.st_size;
				st->st_blocks = 
					(off_t) (((off_t) xattr.st_blocks 
						 * (off_t) xattr.st_blksize) >> 9);
				st->st_blksize = xattr.st_blksize;
				// st->st_flags = 0;
				// st->st_gen = 0;
			}
		}
	}
	return r;
}

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
__do_fstat (int fd, struct stat *st, int exact)
{
	long r;

	r = Ffstat (fd, st, exact);
	if (r != -ENOSYS) {
		if (r) {
			__set_errno (-r);
			return -1;
		}
		return 0;
	}

	/* emulation for TOS */
	__bzero (st, sizeof (*st));

	{
		long oldplace;
		_DOSTIME timeptr;
		short magic;

		if (!__mint && isatty(fd))
			r = -EBADF;
		else
			r = Fdatime(&timeptr, fd, 0);
		
		if (r < 0) {			/* assume TTY */
			st->st_mode = S_IFCHR | 0600;
			st->st_flags = 0;
			if (exact)
				st->st_mtime = st->st_ctime = st->st_atime =
					time ((time_t*) 0) - 2;
					
			st->st_size = 0;
		}
		else {
			if (exact)
				st->st_mtime = st->st_atime = st->st_ctime =
					__unixtime(timeptr.time, timeptr.date);
			st->st_mode = S_IFREG | 0644;	/* this may be false */
			st->st_flags = 0;		/* because this is */

			/* get current file location */
			oldplace = Fseek(0L, fd, SEEK_CUR);
			if (oldplace < 0) { /* can't seek -- must be pipe */
				st->st_mode = S_IFIFO | 0644;
				st->st_size = 1024;
			}
			else {
				/* Go to end of file.  */
				r = Fseek(0L, fd, SEEK_END);
				st->st_size = r;
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
