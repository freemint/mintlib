#include <errno.h>
#include <osbind.h>
#include <stddef.h>
#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>
#include "lib.h"

/***************************************************************
chdir: change the directory and (possibly) the drive.
By ERS: it's in the public domain.
****************************************************************/

int __chdir(dir)
const char *dir;
{
	int old = 0;
	int r;
	char tmp[PATH_MAX];
	register char *d;

	if (dir == NULL)
	  {
	    __set_errno (EFAULT);
	    return -1;
	  }

	/* We can't simply use the user supplied buffer because we may
	   write into the buffer.  */
	if (!__libc_unix_names)
	  (void)_unx2dos(dir, tmp, sizeof (tmp));	/* convert Unix filename to DOS */
	else
	  strcpy (tmp, dir);

	d = tmp;

	/* save old drive */
	if (!__libc_unix_names)
		old = Dgetdrv();

	if (!*d) {		/* empty path means root directory */
		*d = '\\';
		*(d+1) = '\0';
	} else if (*(d+1) == ':') {
		if (!__libc_unix_names) {
			int drv = toupper(*d) - 'A';
			d+=2;
			(void)Dsetdrv(drv);
		} else {
			*(d+1) = tolower(*d);
			*d = '/';
		}
	}

	if ((r = Dsetpath(d)) < 0) {
		/* restore old drive */
		if (!__libc_unix_names)
			(void)Dsetdrv(old);
		if ((r == -ENOTDIR) && _enoent(tmp)) {
			r = -ENOENT;
		}
		__set_errno (-r);
		return -1;
	}
	return 0;
}
weak_alias (__chdir, chdir)
