/*
 * ttyname -- figure out the name of the terminal attached to a file
 * descriptor
 *
 * Written by Eric R. Smith and placed in the public domain.
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

static int find_ino __PROTO((char *, struct xattr *, char *));

static char tname[L_ctermid];

/* Find the file in directory "dir" that matches "sbuf". Returns 1
 * on success, 0 on failure. Note that "dir" is a prefix, i.e. it
 * should end with "\\".
 */

static int
find_ino(dir, sb, name)
	char *dir;
	struct xattr *sb;
	char *name;
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
			_dos2unx (_name, name, L_ctermid);
			return 1;
		}
	}
	Dclosedir(drv);
	return 0;
}

char *
ttyname(fd)
	int fd;
{
	char *name;
	struct xattr sb;

	if (!isatty(fd)) return (char *)0;

	if (__mint < 9) {
		if (fd == -2) {
			name = "/dev/aux";
		} else {
			name = "/dev/con";
		}
		strcpy(tname, name);
		return tname;
	}

	if (Fcntl(fd, &sb, FSTAT))
		return (char *)0;

	/* try the devices first */
	if (find_ino("u:\\dev\\", &sb, tname))
		return tname;

	/* hmmm, maybe we're a pseudo-tty */
	if (find_ino("u:\\pipe\\", &sb, tname))
		return tname;

	/* I give up */
	strcpy(tname, "/dev/tty");
	return tname;
}
