/*
 * statfs() emulation for MiNT/TOS
 *
 * Written by Adrian Ashley (adrian@secret.uucp)
 * and placed in the public domain.
 *
 * Modified for MiNT 1.15 by Chris Felsch.
 */

#include <errno.h>
#include <osbind.h>
#include <mintbind.h>
#include <unistd.h>
#include <limits.h> 
#include <support.h>
#include <string.h>

#include <sys/stat.h>
#include <sys/statfs.h>
#include <mint/dcntl.h>    /* From kernel source!  */

#include "lib.h"

int
__statfs (const char *path, struct statfs *buf)
{
	struct stat statbuf;
	struct fs_info info;
	struct fs_usage usage;
	long r;

	if (!buf || !path) {
	 	__set_errno (EFAULT);
	 	return -1;
	}

	r = __quickstat (path, &statbuf, 0);
	if (r == -1)
		return -1;

	r = Dcntl (FS_INFO, path, &info);
	if (r == 0)
		buf->f_type = info.type;
	else
		buf->f_type = FS_OLDTOS; /* default: TOS */

	r = Dcntl (FS_USAGE, path, &usage);
	if (r == 0) {
		buf->f_bsize = usage.blocksize;
		buf->f_blocks = usage.blocks;
		buf->f_bfree = buf->f_bavail = usage.free_blocks;
		buf->f_files = usage.inodes;
		buf->f_ffree = usage.free_inodes;
		buf->f_fsid = -1LL;
	}
	else if (r == -ENOSYS) {
		_DISKINFO free;

		/* Hack by HPP 02/06/1993: since MiNT 0.99 only returns		*/
		/* valid dfree info for pseudo-drives if they are the 		*/
		/* current directory, change directories for the occasion.	*/
		if ((__mint >= 99) && (statbuf.st_dev >= 32)) {
			char oldpath[PATH_MAX];

			if (getcwd (oldpath, PATH_MAX) != NULL) {
				chdir (path);
				r = Dfree (&free, statbuf.st_dev + 1);
				chdir (oldpath);
			}
			else
				r = Dfree (&free, statbuf.st_dev + 1);
		}
		else
			r = Dfree (&free, statbuf.st_dev + 1);

		if (r == 0) {
			buf->f_bsize = free.b_secsiz * free.b_clsiz;
			buf->f_blocks = free.b_total;
			buf->f_bfree = buf->f_bavail = free.b_free;
			buf->f_files = buf->f_ffree = -1L;
			buf->f_fsid = -1LL;
		}
	}

	/* An error occured (e.g. no medium in removable drive) */
	if (r < 0) {
		__set_errno (-r);
		return -1;
	}

	return 0;
}
weak_alias (__statfs, statfs)

int
get_fsname (const char *path, char *xfs_name, char *type_name)
{
	struct fs_info info;
	char xname[32];
	char tname[32];
		
  	if (!path) {
	 	__set_errno (EFAULT);
	 	return -1;
  	}

	if (Dcntl (FS_INFO, path, &info) >= 0) {
		/* MiNT 1.15 */
		strcpy (xname, info.name);
		strcpy (tname, info.type_asc);
	}
	else {
		if (Dcntl (MX_KER_XFSNAME, path, xname) >= 0) {
			/* MagiC: only one name available */
			strcpy (tname, xname);
		}
		else {
			strcpy (xname, "tos-fs");
			strcpy (tname, "tos");
		}
	}

	if (xfs_name)
		strcpy (xfs_name, xname);
	if (type_name)
		strcpy (type_name, tname);

	return 0;
}
