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
int __fcntl_v (int fd, int cmd, va_list args)
#else
int __fcntl_v (fd, cmd)
int f;
int cmd;
#endif
{
	long r;

	r = Fcntl(fd, va_arg(args, void *), cmd);
	if (r == -ELOCKED)
		r = -EACCES;
#ifndef __PURE_MINT_SUPPORT__
	if (r == -ENOSYS && !__mint) {
		switch (cmd) {
			case F_GETFL: {
				switch (fd) {
					case 0:
						r = O_RDONLY;
						break;
					case 1:
						r = O_WRONLY;
						break;
					case 2:
					default:
						r = O_RDWR;
						break;
						
				}
				break;
			}
		}
	}
#endif
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
