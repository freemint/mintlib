/* seekdir routine */

/* under MiNT (v0.9 or better) these use the appropriate system calls.
 * under TOS or older versions of MiNT, they use Fsfirst/Fsnext
 *
 * Written by Eric R. Smith and placed in the public domain
 */

#ifdef __TURBOC__
# include <sys\types.h>
#else
# include <sys/types.h>
#endif

#include <limits.h>
#include <dirent.h>
#include "lib.h"

/* not POSIX */

void
seekdir(dirp, loc)
	DIR *dirp;
	off_t loc;
{
	rewinddir(dirp);
	while (dirp->buf.d_off != loc) {
		if (!readdir(dirp))
			break;
	}
}
