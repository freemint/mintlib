/*
 * Ffdopendir implemented by Alan Hourihane <alanh@fairlite.co.uk>
 */
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include <limits.h>
#include <dirent.h>
#include <errno.h>
#include <mint/mintbind.h>
#include "lib.h"

DIR *
__fdopendir (int fd)
{
	DIR *d;
	long r;

	d = malloc(sizeof(DIR));
	if (!d) {
		__set_errno (ENOMEM);
		return d;
	}

	r = Ffdopendir(fd);
	if (r < 0) {
		free(d);
		__set_errno(-r);
		return NULL;
	}

	d->handle = r;
	d->buf.d_off = 0;
	d->status = 0;

	return d;
}
weak_alias (__fdopendir, fdopendir)
