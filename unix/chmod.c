/* chmod -- change the permissions of a file */
/* written by Eric R. Smith and placed in the public domain */

#ifdef __TURBOC__
# include <sys\types.h>
# include <sys\stat.h>
#else
# include <sys/types.h>
# include <sys/stat.h>
#endif

#include <osbind.h>
#include <mintbind.h>
#include <limits.h>
#include <errno.h>
#include <unistd.h>
#include "lib.h"


int
__chmod(_path, mode)
	const char *_path;
	mode_t   mode;
{
	int  dosattrib = 0, r;
	char buf[PATH_MAX];
	char* path = (char*) _path;

	if (!__libc_unix_names)
	  {
	    path = buf;
	    (void)_unx2dos(_path, path, sizeof (buf));
	  }
	  
	r = (int)Fchmod(path, mode);
#if 1
	/* Kludge:  on dos filesystems return success for dirs
	   even though we failed */
	if ((r == -ENOENT) && (Dpathconf(path, 5) == 2) &&
	    (Fattrib(path, 0, 0) == FA_DIR))
		return 0;
#endif
	if (r && (r != -ENOSYS)) {
		errno = -r;
		return -1;
	}
	else if (r != -ENOSYS)   /* call was successfull */
		return 0;


/* The following lines ensure that the archive bit isn't cleared */
	r = Fattrib(path, 0, 0);
	if (r < 0)
	  {
	    errno = -r;
	    return -1;
	  }
 	if (r & FA_CHANGED)
		dosattrib |= FA_CHANGED;

	if (r & FA_DIR)
	  dosattrib |= FA_DIR;
#if 0
	if (!(mode & S_IREAD))
		dosattrib |= FA_HIDDEN;
#endif
	if (!(mode & S_IWRITE))
		dosattrib |= FA_RDONLY;
	r = Fattrib(path, 1, dosattrib);
	if (r < 0) {
/* GEMDOS doesn't allow chmod on a directory, so pretend it worked */
		if (dosattrib & FA_DIR)
		  return 0;
		errno = -r;
		return -1;
	}
	return 0;
}
weak_alias (__chmod, chmod)
