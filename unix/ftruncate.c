/*

Here is an implementation of truncate/ftruncate for the MiNTlib. There
is a special case for truncate, if the filesystem does not recognize
FTRUNCATE and the length is zero, Fcreate is used to truncate the
file. This only works for tosfs if the file isn't already open. The
rest is quite straight forward.

Andreas.

Andreas Schwab <schwab@issan.informatik.uni-dortmund.de>

*/

#include <compiler.h>
#include <limits.h>
#include <errno.h>
#include <mintbind.h>

#ifdef __TURBOC__
# include <sys\types.h>
# include <sys\ioctl.h>
#else
# include <sys/types.h>
# include <sys/ioctl.h>
#endif

#include "lib.h"

int
__ftruncate (fd, length)
     int fd;
     off_t length;
{
  int res;

  res = (int) Fcntl (fd, (long) &length, FTRUNCATE);

    if (res < 0)
    {
      __set_errno (-res);
      return -1;
    }
  return 0;
}

weak_alias (__ftruncate, ftruncate)
