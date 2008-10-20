/* access() emulation; relies heavily on stat() */

#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>

#include "lib.h"

int
__access (const char *path, int imode)
{
	unsigned int mode = (unsigned int) imode;
	struct stat sb;

	if (__quickstat (path, &sb, 0) < 0)
		/* errno was set by stat() */
		return -1;

	if (mode == F_OK)
		/* existence test succeeded */
		return 0;

	if (getuid() == 0)
		/* super user can access anything */
		return 0;

	/* somewhat crufty code -- relies on R_OK, etc. matching the bits in the
	 * file mode, but what the heck, we can do this
	 */
	if (__mint < 9 || (getuid() == sb.st_uid)) {
		if (((sb.st_mode >> 6) & mode) == mode)
			return 0;
		else
			goto accdn;
	}

	if (getgid() == sb.st_gid) {
		if (((sb.st_mode >> 3) & mode) == mode)
			return 0;
		else
			goto accdn;
	}

	if (__mint >= 0x10b) {
		gid_t groups[NGROUPS_MAX];
		int i, n;

		n = getgroups(NGROUPS_MAX, groups);
		for (i = 0; i < n; i++) {
			if (groups[i] == sb.st_gid) {
				if ( ((sb.st_mode >> 3) & mode) == mode )
					return 0;
				else
					goto accdn;
			}
		}
	}

	if ((sb.st_mode & mode) == mode)
		return 0;

accdn:
	__set_errno (EACCES);
	return -1;
}
weak_alias (__access, access)
