/*
 * fcntl() emulation for MiNT; written by Eric R. Smith and placed
 * in the public domain
 */

#include <errno.h>
#include <mintbind.h>
#include <fcntl.h>
#include <stdarg.h>

#include "lib.h"

#ifdef __STDC__
int __fcntl_v (int f, int cmd, va_list args)
#else
int __fcntl_v (f, cmd)
int f;
int cmd;
#endif
{
	long r;

	r = Fcntl(f, va_arg(args, void *), cmd);
	if (r == -ELOCKED)
		r = -EACCES;
	if (r < 0) {
		__set_errno (-r);
		r = -1L;
	}
	return (int) r;
}

#ifdef __STDC__
int __fcntl (int desc, int cmd, ...)
#else
int __fcntl (int desc, cmd)
	const char *_filename;
	int cmd;
#endif
{
#ifdef __STDC__
  va_list args;
  int retval;

  va_start (args, cmd);
  retval = __fcntl_v (desc, cmd, args);
  va_end (args);
    
  return retval;
#else
  retval = __fcntl_v (desc, cmd);
#endif
}
weak_alias (__fcntl, fcntl)
