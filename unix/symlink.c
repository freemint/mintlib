/* soft link routines */

#include <errno.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>

#include <sys/stat.h>
#include <mint/mintbind.h>

#include "lib.h"

/*
 * If MiNT 0.9 or later is active, use the kernel routines for these;
 * otherwise, try to choose failure modes that applications will best be
 * able to handle
 */

int
__symlink (const char *old, const char *new)
{
	char linknamebuf[PATH_MAX];
	char pathbuf[PATH_MAX];
	char *linkname;
	char *path = (char *) new;
	long r;

	/* Sigh, for compatibility reasons we have to store links in
	   Redmond style.  */
	linkname = linknamebuf;
	_unx2dos(old, linkname, sizeof (linknamebuf));
	
	if (!__libc_unix_names) {
		path = pathbuf;
		_unx2dos(new, pathbuf, sizeof (pathbuf));
	}
	
	r = Fsymlink(linkname, path);
	if (r) {
		struct stat sb;

		if ((r == -ENOTDIR)) {
			if (_enoent(path))
				r = -ENOENT;
		} else if ((r == -EACCES) && (!__sys_stat (path, &sb, 1, 0)))
			r = -EEXIST;
		__set_errno (-r);
		return -1;
	}
	return (int) r;
}
weak_alias (__symlink, symlink)
