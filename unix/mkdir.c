/* mkdir: make a new directory
 * written by Eric R. Smith and placed in the public domain
 * modified by Alan Hourihane, to check for directory and return EEXIST.
 */

#include <errno.h>
#include <limits.h>
#include <unistd.h>
#include <mint/mintbind.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "lib.h"

int 
__mkdir(const char *_path, mode_t mode)
{
	struct stat statbuf;
	int rv, umask;
	char pathbuf[PATH_MAX];
	char* path = (char*) _path;
	
	if (_path == NULL)
	  {
	    __set_errno (EFAULT);
	    return -1;
	  }
	if (!__libc_unix_names)
	  {
	    path = pathbuf;
	    _unx2dos(_path, path, sizeof (pathbuf));
	  }

	rv = __quickstat(path, &statbuf, 0);	/* Stat directory */
	if (rv == 0) {			/* Does it exist ? */
		__set_errno (EEXIST);	/* Yes, so tell user. */
		return -1;
	}

	if (errno != ENOENT) {		/* Return stat error, if other than */
					/* File not found. */
		if ((errno == ENOTDIR) && (_enoent(path)))
			__set_errno (ENOENT);
		return -1;
	}

	rv = Dcreate(path);
	if (rv < 0) {
		__set_errno (-rv);
		return -1;
	}
	
	if ((umask = Pumask (0)) != -ENOSYS) {
		(void) Pumask (umask);
		(void)Fchmod(path, mode & ~umask);
	}
	return 0;
}
weak_alias (__mkdir, mkdir)
