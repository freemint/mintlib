/* soft link routines */

#include <mintbind.h>
#include <errno.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>

#ifdef __TURBOC__
# include <sys\stat.h>
#else
# include <sys/stat.h>
#endif

#include "lib.h"


/*
 * If MiNT 0.9 or later is active, use the kernel routines for these;
 * otherwise, try to choose failure modes that applications will best be
 * able to handle
 */

int
__readlink (const char *unxname, char *buf, int siz)
{
	long r;
	size_t l;
	char filenamebuf[PATH_MAX];
	char linkto[PATH_MAX+1];
	char* filename = unxname;
	
	if (!__libc_unix_names)
	  {
	    filename = filenamebuf;
	    _unx2dos(unxname, filename, sizeof (filenamebuf));
	  }
	r = Freadlink(PATH_MAX, linkto, filename);
	if (r < 0) {
		if (r == -EACCES) {
			struct xattr sb;

			/* UNIX gives EINVAL, not EACCES, on non-links */
			if ((Fxattr(1, filename, &sb) == 0)
			    && (((mode_t) sb.st_mode & S_IFMT) != S_IFLNK)) {
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
	l = strlen(filenamebuf);
	if (l > siz) {
		__set_errno (ERANGE);
		return -1;
	}
	strncpy(buf, filenamebuf, siz);
	return (int) l;
}

weak_alias (__readlink, readlink)
