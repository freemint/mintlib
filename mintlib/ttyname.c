/*
 * ttyname -- figure out the name of the terminal attached to a file
 * descriptor
 *
 * Written by Eric R. Smith and placed in the public domain.
 */

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <mint/mintbind.h>

#include "lib.h"


static char tname[L_ctermid];

/* Find the file in directory "dir" that matches "sbuf". Returns 1
 * on success, 0 on failure. Note that "dir" is a prefix, i.e. it
 * should end with "\\".
 */

static int
find_ino (char *dir, struct stat *sb, char *name)
{
	char _name[PATH_MAX];
	char *where = _name;
	long drv;
	struct stat testsb;
	struct dbuf {
		long ino;
		char name[NAME_MAX + 1];
	} dbuf;

	drv = Dopendir (dir, 0);
	if ((drv & 0xff000000L) == 0xff000000L) return 0;

	while (*dir)
		*where++ = *dir++;

	while (Dreaddir (sizeof (dbuf), drv, &dbuf) == 0) {
		strcpy (where, dbuf.name);
		if (__sys_stat (_name, &testsb, 0, 0))
			continue;
		if (testsb.st_dev == sb->st_dev &&
		    testsb.st_ino == sb->st_ino) {
			Dclosedir (drv);
			_dos2unx (_name, name, L_ctermid);
			return 1;
		}
	}
	Dclosedir (drv);
	return 0;
}

char *
ttyname (int fd)
{
	struct stat sb;
	char *name;

	if (!isatty (fd))
		return NULL;

	if (__mint < 9) {
		if (fd == -2) {
			name = "/dev/aux";
		} else {
			name = "/dev/con";
		}
		strcpy (tname, name);
		return tname;
	}

	if (__sys_fstat (fd, &sb, 0))
		return NULL;

	/* try the devices first */
	if (find_ino ("u:\\dev\\", &sb, tname))
		return tname;

	/* hmmm, maybe we're a pseudo-tty */
	if (find_ino ("u:\\pipe\\", &sb, tname))
		return tname;

	/* I give up */
	strcpy (tname, "/dev/tty");
	return tname;
}
