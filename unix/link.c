/* make a hard link */

#include <errno.h>
#include <unistd.h>
#include <limits.h>

#include <sys/param.h>
#include <sys/stat.h>
#include <mint/mintbind.h>

#include "lib.h"

/*
 * if MiNT is not active, we try to fail gracefully
 */

int
__link (const char *_old, const char *_new)
{
	long r;
	char oldbuf[PATH_MAX], newbuf[PATH_MAX];
	char *old = (char *) _old;
	char *new = (char *) _new;
	
	if (!__libc_unix_names)
	  {
	    old = oldbuf;
	    new = newbuf;
	    _unx2dos (_old, old, sizeof (oldbuf));
	    _unx2dos (_new, new, sizeof (newbuf));
	  }
	  
	r = Flink(old, new);
	if (r < 0 && r != -ENOSYS) {
		struct stat sb;

		if ((r == -ENOTDIR)) {
			if (_enoent (__sys_stat (old, &sb, 1, 0) ? old : new))
				r = -ENOENT;
		} else if ((r == -EACCES) && (!__sys_stat (new, &sb, 1, 0)))
			r = -EEXIST;
		__set_errno ((int) -r);
		return -1;
	}
	else if (r == -ENOSYS) {
		__set_errno (EXDEV);
		return -1;
	}	
	return 0;
}
weak_alias (__link, link)
