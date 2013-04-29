/* readdir routine */

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


/* Important note: under Metados, some file systems can have opendir/readdir/
 * closedir, so we must not have a status variable for these ones.
 * Instead, check the directory struct if there was an opendir call.
 */

/* a new value for DIR->status, to indicate that the file system is not
 * case sensitive.
 */
#define _NO_CASE  8

struct dirent*
__readdir(DIR *d)
{
	struct dbuf {
		long ino;
		char name[NAME_MAX + 1];
	} dbuf;
	long r;
	_DTA *olddta;
	struct dirent *dd = &d->buf;

	if (d == NULL) {
		__set_errno (EBADF);
		return NULL;
	}
	
	if (d->handle != 0xff000000L)  {
		/* The directory descriptor was optained by calling Dopendir(), as
		 * there is a valid handle.
		 */
		r = (int)Dreaddir((int)(NAME_MAX+1+sizeof(long)), d->handle, (char *) &dbuf);
		if (r == -ENMFILES)
			return 0;
		else if (r) {
			__set_errno (-r);
			return 0;
		}
		else {
			dd->d_ino = dbuf.ino;
			dd->d_off++;
			dd->d_namlen = (short)strlen(dbuf.name);
			strcpy(dd->d_name, dbuf.name);

			/* if file system is case insensitive, transform name to lowercase */
			if (d->status == _NO_CASE)
				strlwr(dd->d_name);

			return dd;
		}
	}
/* ordinary TOS search, using Fsnext. Note that the first time through,
 * Fsfirst has already provided valid data for us; for subsequent
 * searches, we need Fsnext.
 */
	if (d->status == _NMFILE)
		return 0;
	if (d->status == _STARTSEARCH) {
		d->status = _INSEARCH;
	} else {
		olddta = Fgetdta();
		Fsetdta(&(d->dta));
		r = Fsnext();
		Fsetdta(olddta);
		if (r == -ENMFILES) {
			d->status = _NMFILE;
			return 0;
		} else if (r) {
			__set_errno (-r);
			return 0;
		}
	}
	dd->d_ino = __inode++;
	dd->d_off++;
	_dos2unx(d->dta.dta_name, dd->d_name, sizeof (dd->d_name));
	dd->d_namlen = (short)strlen(dd->d_name);
	return dd;
}

/* Reentrant version of the above, use is deprecated because it imposes
   a performance loss.  The ordinary readdir() is already thread-safe
   in the MiNTLib but the existence of readdir_r() may facilitate 
   writing or compiling portable code.  */
int readdir_r (DIR *dirp, struct dirent *entry, struct dirent **result)
{
  if (result == NULL || *result == NULL || entry == NULL)
    {
      __set_errno (EBADF);
      return -1;
    }
  *result = readdir (dirp);
  if (*result == NULL)
    return -1;
    
  *entry = **result;
  return 0;
}

weak_alias (__readdir, readdir)
