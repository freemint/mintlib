
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <mint/osbind.h>
#include "lib.h"

/***************************************************************
chdir: change the directory and (possibly) the drive.
By ERS: it's in the public domain.
****************************************************************/

void *__malloc (size_t __n);
void __free (void* __param);

int
__chdir (const char *dir)
{
	char *tmp = NULL;
	int old = -1;
	int r;

	if (dir == NULL) {
	  	__set_errno (EFAULT);
	  	return -1;
	}

	if (!__libc_unix_names) {
		/* convert Unix filename to DOS */
		tmp = __malloc(strlen(dir)+16);
		if (!tmp) {
			__set_errno(ENOMEM);
			return -1;
		}

		_unx2dos(dir, tmp, strlen(dir)+16);

		dir = tmp;
	}

	if (!*dir) {
		/* empty path means root directory */
		dir = "\\";
	}
	else if (dir[1] == ':') {
		if (!__libc_unix_names) {
			int drv;

			/* save old drive */
			old = Dgetdrv();

			drv = toupper(dir[0]) - 'A';
			Dsetdrv(drv);

			dir += 2;
		}
		else {
			tmp = __malloc(strlen(dir)+16);
			if (!tmp) {
				__set_errno(ENOMEM);
				return -1;
			}

	  		strcpy (tmp, dir);

			tmp[1] = tolower(tmp[0]);
			tmp[0] = '/';

			dir = tmp;
		}
	}

	r = Dsetpath(dir);
	if (r < 0) {
		if ((r == -ENOTDIR) && _enoent(dir))
			r = -ENOENT;

		__set_errno (-r);
		r = -1;
	}

	if (tmp)
		__free (tmp);

	/* restore old drive */
	if (old >= 0)
		Dsetdrv(old);

	return r;
}
weak_alias (__chdir, chdir)
