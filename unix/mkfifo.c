/* fake mkfifo -- should even work sometimes now :)  */
/* No, it never works. In fact it is pure nonsense!  
   (Personal opinion of Guido Flohr).  */

#include <errno.h>
#include <limits.h>
#include <support.h>
#include <unistd.h>
#include <mint/mintbind.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "lib.h"

int
__mkfifo (const char *_path, mode_t mode)
{
	static unsigned long timelast;
	char pathbuf[PATH_MAX], linkf[30] = "u:\\pipe\\n$", *s, c;
	unsigned long l;
	unsigned short x;
	long r;
	int i;
	char* path = (char*) _path;
	
	/* create symlink to /pipe/n$ mode id (see open.c)
	   for id code pid&0x7fff and time>>1 in base-36, this just fits
	   in pipefs' limit of 14 chars...  */

	if (!__libc_unix_names)
	  {
	    path = pathbuf;
	    _unx2dos(_path, path, sizeof (pathbuf));
	  }
	  
	s = linkf + sizeof "u:\\pipe\\n$" - 1;
	*s++ = ((mode >> 6) & 7) + '0';
	*s++ = ((mode >> 3) & 7) + '0';
	*s++ = (mode & 7) + '0';
#if 0
#define FMODE (FA_HIDDEN)
	*s++ = ((FMODE & 0xf0) >> 4) + '@';
	*s++ = (FMODE & 0xf) + '@';
#endif
	x = (unsigned short)36 * (unsigned short)36 * (unsigned short)36 - 1 - (unsigned short)(getpid () & 0x7fff);
	c = x % 36;
	if (c > 9)
		c += 'a' - '9' - 1;
	s[2] = c + '0';
	x /= 36;
	c = x % 36;
	if (c > 9)
		c += 'a' - '9' - 1;
	s[1] = c + '0';
	*s = (x / 36) - 10 + 'a';

	/* BUG:  14 char names in /pipe should work but they do not
	   everywhere... (MiNT 1.10, readdir gets no \0 char)  ok so
	   then try to squeeze the pid in 2 chars, this is possible
	   because they are always <= 999 at least in 1.10.  */
	if (*s == 'z' && s[1] > '7') {
		*s = s[1];
		s[1] = s[2];
		--s;
	}
	s += 3;
	/* make sure time is uniqe, if necessary sleep. */
	for (; (l = time((time_t *)0) >> 1) == timelast;
	    (void) Fselect (1000, 0L, 0L, 0L))
		;
	timelast = l;
	for (i = 0; i < 6; ++i, l /= 36) {
		c = l % 36;
		if (c > 9)
			c += 'a' - '9' - 1;
		*s++ = c + '0';
	}
	*s = 0;
	r = Fsymlink(linkf, path);
	if (r == -ENOSYS) {
		__set_errno (EINVAL);
		return -1;
	}
	if (r) {
		struct stat sb;

		if ((r == -ENOTDIR)) {
			if (_enoent(path))
				r = -ENOENT;
		} else if ((r == -EACCES) && (!__sys_stat (path, &sb, 1, 0)))
			r = -EEXIST;
		__set_errno (-r);
		return -1;
	}
	return (int) r;
}
weak_alias (__mkfifo, mkfifo)
