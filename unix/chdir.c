
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
__chdir (const char *_dir)
{
	int old = 0;
	int r;
	char *tmp = NULL;
	const char *dir;

	dir = _dir;

	if (dir == NULL) {
	  	__set_errno (EFAULT);
	  	return -1;
	}

	if (!__libc_unix_names) {
		/* save old drive */
		old = Dgetdrv();

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

	if (tmp)
		__free (tmp);

	if (r < 0) {
		/* restore old drive */
		if (!__libc_unix_names)
			Dsetdrv(old);

		if ((r == -ENOTDIR) && _enoent(tmp))
			r = -ENOENT;

		__set_errno (-r);
		return -1;
	}

	return 0;
}
weak_alias (__chdir, chdir)
