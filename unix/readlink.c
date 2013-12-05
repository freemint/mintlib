/* soft link routines */

#include <errno.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>
#include <mint/mintbind.h>
#include <sys/stat.h>

#include "lib.h"


/*
 * If MiNT 0.9 or later is active, use the kernel routines for these;
 * otherwise, try to choose failure modes that applications will best be
 * able to handle
 */

int
__readlink (const char *unxname, char *buf, size_t siz)
{
	long r;
	size_t l;
	char filenamebuf[PATH_MAX];
	char linkto[PATH_MAX+1];
	const char *filename = unxname;
	
	if (!__libc_unix_names)
	  {
	    filename = filenamebuf;
	    _unx2dos(unxname, filenamebuf, sizeof (filenamebuf));
	  }
	r = Freadlink(PATH_MAX, linkto, filename);
	if (r < 0) {
		if (r == -EACCES) {
			struct stat sb;

			/* UNIX gives EINVAL, not EACCES, on non-links */
			if ((__sys_stat (filename, &sb, 1, 0) == 0)
			    && ((sb.st_mode & S_IFMT) != S_IFLNK)) {
				r = -EINVAL;
			}
		}
		if ((r == -ENOTDIR) && _enoent(filename)) {
			r = -ENOENT;
		}
		__set_errno (-r);
		return -1;
	}
	linkto[PATH_MAX] = 0;
	/* Sigh, when reading links we have to convert the names back 
	   because for compatibility reasons they are always stored in
	   Redmond format.  */
	_dos2unx(linkto, filenamebuf, sizeof (filenamebuf));

	/*
	 * readlink specifies to truncate with no null termination.
	 */
	for (l = 0; l < siz && filenamebuf[l] != '\0'; l++)
		buf[l] = filenamebuf[l];

	return (int) l;
}
weak_alias (__readlink, readlink)
