/* $Id$ */

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <mint/mintbind.h>
#include "lib.h"

/*
 * Given a pathname for which some system call returned ENOTDIR, this function
 * decides if UNIX would have returned ENOENT instead.
 * 
 * FIXED: First check if the complete path itself is not a directory.  In
 * this case ENOTDIR is correct. --gfl
 */

int
_enoent (const char *path)
{
	register const char *s;
	long oldmask;
	int dir_seen = 0;
	char *tmp = NULL;

	if (!path)
		return 0;

	for (s = path; *s; s++)
		/* nop */;

	oldmask = Psigblock(~0L);

	for ( ; s != path; s--) {
		if (*s == '\\' || *s == '/') {
			struct stat st;
			long r;

			dir_seen = 1;

			if (!tmp)
			{
				tmp = malloc(s - path + 1);
				if (!tmp)
					return 0;

				strncpy(tmp, path, s - path);
			}

			tmp[s - path] = '\0';
			r = __sys_stat (tmp, &st, 0, 0);

			if (r == -ENOSYS 
			    || (r == 0 && ((st.st_mode & S_IFMT) != S_IFDIR))) {
				if (tmp)
					free(tmp);

				(void) Psigsetmask (oldmask);

				/* Either we don't have Fstat or existing
				 * non-directory in PATH.  ENOTDIR is ok in
				 * either case.  */
				return 0;
			}
		}
	}

	if (tmp)
		free(tmp);

	(void) Psigsetmask (oldmask);
	return dir_seen; /* should have been ENOENT */
}
