#include <compiler.h>
#include <stddef.h>
#include <stdlib.h>	/* both of these added for malloc() */
#include <limits.h>
#include <errno.h>
#include <string.h>
#include <osbind.h>
#include <mintbind.h>
#include <unistd.h>
#include "lib.h"

/*******************************************************************
getcwd: returns current working directory. By ERS.
This routine is in the public domain.
********************************************************************/

extern char _rootdir;	/* in main.c: user's preferred root directory */

char *__getcwd(buf, size)
char *buf; int size;
{
	char _path[PATH_MAX];
	char *path;
	char drv;
	int buf_malloced = 0;
	int r;

	if (!buf) {
	        if (size == 0)
	          size = PATH_MAX;
	          
		if ((buf = malloc((size_t)size)) == 0)
			return NULL;
		buf_malloced = 1;
	}

	drv = Dgetdrv() + 'a';
	_path[0] = drv;
	_path[1] = ':';
	_path[2] = '\0';
	path = _path + 2;

	r = (int) Dgetcwd(path, 0, size - 2);

	if (r != 0 && r != -ENOSYS) {
			if (buf_malloced)
				free(buf);
			__set_errno (-r);
			return NULL;
	} else if (r == -ENOSYS) {
		(void)Dgetpath(path, 0);
	}

	if (_rootdir && drv == _rootdir) {
		if (!*path) {
			path[0] = '\\';
			path[1] = '\0';
		}
		_dos2unx((char *)path, buf, size);
		return buf;
	}
	_dos2unx(_path, buf, size);	/* convert DOS filename to unix */
	
	if (buf_malloced) {
	  size_t len = strlen (buf) + 1;
	  (void) realloc (buf, len);
	}
	
	return buf;
}

weak_alias (__getcwd, getcwd)
