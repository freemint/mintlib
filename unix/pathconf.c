/*
 * pathconf() for TOS/MiNT (kinda POSIXy)
 * Written by Dave Gymer and placed in the Public Domain
 *
 * NOTE: this file will have to be updated as and when MiNT gains
 * new Sysconf() and Dpathconf() variables, as will unistd.h, so that
 * TOS programs get the correct values back. (But who uses TOS? :-)
 */

#include <errno.h>
#include <limits.h>
#include <unistd.h>
#include <mint/mintbind.h>
#include "lib.h"

#define UNLIMITED	(0x7fffffffL)

long
__pathconf (const char *_path, int var)
{
	long r;
	char pathbuf[PATH_MAX];
	char* path = (char*) _path;
	
	if (!__libc_unix_names)
	  {
	    path = pathbuf;
	    _unx2dos (_path, path, sizeof (pathbuf));
	  }

	if ((r = Dpathconf(path, var)) != -ENOSYS) {
		if (var == _PC_NO_TRUNC)
			return r ? -1 : 0;
		return r;
	}

	switch(var) {
	case _PC_LAST:
		return 4;
	case _PC_IOPEN_MAX:
		return 45; /* -ish, maybe... */
	case _PC_LINK_MAX:
		return 1;
	case _PC_PATH_MAX:
		return 128; /* I'm sure I read that this is 64 in TOS 1.0 */
	case _PC_NAME_MAX:
		return 12;
	case _PC_NO_TRUNC:
		return -1;  /* file names are automatically truncated */
        case _MINT_PC_NAME_CASE:
		return 1;  /* case-insensitive, changing to upper case
			      (or lower case) MJK */
	default: /* note that _PC_PIPE_BUF is invalid */
		/* The only way to determine whether -1 signifies an error
		   or is "no limit", is to set errno to 0, and check for
		   a possible error after the call again.  */
		__set_errno (EINVAL);
		return -1;
	}
}
weak_alias (__pathconf, pathconf)
