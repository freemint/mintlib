/* closedir routine */

/* under MiNT (v0.9 or better) these use the appropriate system calls.
 * under TOS or older versions of MiNT, they use Fsfirst/Fsnext
 *
 * Written by Eric R. Smith and placed in the public domain
 */

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include <limits.h>
#include <dirent.h>
#include <errno.h>
#include <osbind.h>
#include <mintbind.h>
#include "lib.h"


/* Important note: the same comment for the status variable of
 * opendir/readdir under Metados applies also here.
 */

int
__closedir(DIR *dirp)
{
	long r;

	/* The GNU libc closedir returns gracefully if a NULL pointer is
	   passed.  We follow here.  */
	if (dirp == NULL) {
		__set_errno (EBADF);
		return -1;
	}
	
	if (dirp->handle != 0xff000000L)
		r = Dclosedir(dirp->handle);
	else
		r = 0;
	if (r == -ENOSYS) {
		/* hmm, something went wrong, just ignore it. */
		r = 0;
	}
	free(dirp);
	return r;
}
weak_alias (__closedir, closedir)
