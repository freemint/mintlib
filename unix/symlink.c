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
__symlink(old, new)
	const char *old, *new;
{
	char linknamebuf[PATH_MAX];
	char pathbuf[PATH_MAX];
	char* linkname;
	char* path = (char*) new;
	long r;

	/* Sigh, for compatibility reasons we have to store links in
	   Redmond style.  */
	linkname = linknamebuf;
	_unx2dos(old, linkname, sizeof (linknamebuf));
	
	if (!__libc_unix_names)
	  {
	    path = pathbuf;
	    _unx2dos(new, pathbuf, sizeof (pathbuf));
	  }
	
	r = Fsymlink(linkname, path);
	if (r) {
		struct xattr sb;

		if ((r == -ENOTDIR)) {
			if (_enoent(path))
				r = -ENOENT;
		} else if ((r == -EACCES) && (!Fxattr(1, path, &sb)))
			r = -EEXIST;
		errno = (int) -r;
		return -1;
	}
	return (int) r;
}

weak_alias (__symlink, symlink)
