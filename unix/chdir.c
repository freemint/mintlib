
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

void *malloc (size_t __n);
void free (void* __param);

int
__chdir (const char *dir)
{
	char *tmp = NULL;
	int r;

	if (dir == NULL) {
	  	__set_errno (EFAULT);
	  	return -1;
	}

	if (!__libc_unix_names) {
		/* convert Unix filename to DOS */
		tmp = malloc(strlen(dir)+16);
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
			tmp = malloc(strlen(dir)+16);
			if (!tmp) {
				__set_errno(ENOMEM);
				return -1;
			}

	  		if (toupper(dir[0]) == 'U' && dir[2]) {
		  		strcpy (tmp +1, dir +3);

		  	} else {
		  		strcpy (tmp +2, dir +2);
				tmp[1] = tolower(dir[0]);
			}
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
		free (tmp);

	return r;
}
weak_alias (__chdir, chdir)
