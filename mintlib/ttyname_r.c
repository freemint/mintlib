/*
 * ttyname -- figure out the name of the terminal attached to a file
 * descriptor
 *
 * Written by Eric R. Smith and placed in the public domain.
 * Reentrant version by Guido Flohr.
 */

#include <stdio.h>

#ifdef __TURBOC__
# include <sys\types.h>
# include <sys\stat.h>
# include <sys\ioctl.h>
#else
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
#endif

#include <string.h>
#include <unistd.h>
#include <mintbind.h>
#include <limits.h>
#include <errno.h>
#include "lib.h"

extern int __mint;

static int find_ino __PROTO((char *, struct xattr *, char *, size_t));

/* Find the file in directory "dir" that matches "sbuf". Returns 1
 * on success, 0 on failure. Note that "dir" is a prefix, i.e. it
 * should end with "\\".
 */

static int
find_ino(dir, sb, buf, buflen)
	char *dir;
	struct xattr *sb;
	char *buf;
	size_t buflen;
{
	char _name[PATH_MAX];
	char *where = _name;
	long drv;
	struct xattr testsb;
	struct dbuf {
		long ino;
		char name[NAME_MAX + 1];
	} dbuf;

	drv = Dopendir (dir, 0);
	if ((drv & 0xff000000L) == 0xff000000L) return 0;

	while (*dir) {
		*where++ = *dir++;
	}

	while (Dreaddir((int) sizeof (dbuf), drv, (char *) &dbuf) == 0) {
		strcpy(where, dbuf.name);
		if (Fxattr(0, _name, &testsb))
			continue;
		if (testsb.st_dev == sb->st_dev &&
		    testsb.st_ino == sb->st_ino) {
			Dclosedir(drv);
			_dos2unx (_name, buf, buflen);
			return 1;
		}
	}
	Dclosedir(drv);
	return 0;
}

int
ttyname_r (fd, buf, buflen)
	int fd;
	char* buf;
	size_t buflen;
{
	char *name;
	struct xattr sb;

	if (!isatty(fd)) return -1;

	if (__mint < 9) {
		if (fd == -2) {
			name = "/dev/aux";
		} else {
			name = "/dev/con";
		}
		strncpy(buf, name, buflen);
		return 0;
	}

	if (Fcntl(fd, &sb, FSTAT))
		return -1;

	/* try the devices first */
	if (find_ino("u:\\dev\\", &sb, buf, buflen))
		return 0;

	/* hmmm, maybe we're a pseudo-tty */
	if (find_ino("u:\\pipe\\", &sb, buf, buflen))
		return 0;

	/* I give up */
	strncpy(buf, "/dev/tty", buflen);
	return 0;
}
