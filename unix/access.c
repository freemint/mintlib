/* access() emulation; relies heavily on stat() */

#ifdef __TURBOC__
# include <sys\types.h>
# include <sys\stat.h>
#else
# include <sys/types.h>
# include <sys/stat.h>
#endif

#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

#include "lib.h"

extern int __mint;

int
__access(path, mode)
	const char *path;
	int mode;
{
	struct stat sb;
	gid_t groups[NGROUPS_MAX];
	int i, n;

	if (__quickstat (path, &sb, 0) < 0)
		return -1;	/* errno was set by stat() */
	if (mode == F_OK)
		return 0;	/* existence test succeeded */

	if (getuid() == 0) return 0; /* super user can access anything */

/* somewhat crufty code -- relies on R_OK, etc. matching the bits in the
   file mode, but what the heck, we can do this
 */
	if (__mint < 9 || ( getuid() == sb.st_uid ) ) {
		if ( ((sb.st_mode >> 6) & mode) == mode )
			return 0;
		else
			goto accdn;
	}

	if ( getgid() == sb.st_gid ) {
		if ( ((sb.st_mode >> 3) & mode) == mode )
			return 0;
		else
			goto accdn;
	}

	if ( __mint >= 0x10b ) {
		n = getgroups(NGROUPS_MAX, groups);
		for ( i = 0; i < n; i++ ) {
			if ( groups[i] == sb.st_gid ) {
				if ( ((sb.st_mode >> 3) & mode) == mode )
					return 0;
				else
					goto accdn;
			}
		}
	}

	if ( (sb.st_mode & mode) == mode)
		return 0;
accdn:
	errno = EACCES; return -1;
}
weak_alias (__access, access)
