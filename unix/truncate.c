/*

Here is an implementation of truncate/ftruncate for the MiNTlib. There
is a special case for truncate, if the filesystem does not recognize
FTRUNCATE and the length is zero, Fcreate is used to truncate the
file. This only works for tosfs if the file isn't already open. The
rest is quite straight forward.

Andreas.

Andreas Schwab <schwab@issan.informatik.uni-dortmund.de>

*/

#include <errno.h>
#include <limits.h>
#include <mint/mintbind.h>
#include <sys/types.h>
#include <sys/ioctl.h>

#include "lib.h"

int
__truncate (const char *_filename, off_t length)
{
  int fh, res;
  char filenamebuf[PATH_MAX];
  char* filename = (char*) _filename;
  
  if (!__libc_unix_names)
    {
      filename = filenamebuf;
      (void) _unx2dos (_filename, filename, sizeof (filenamebuf));
    }
  res = -ENOSYS;

  res = (int) Dcntl(FTRUNCATE, (long) filename, (long) &length);

  if (res == 0)
    return res;
  if (res != -ENOSYS)
  {
     if (res < 0)
     {
      if ((res == -ENOTDIR) && (_enoent(filename)))
        res = -ENOENT;
      __set_errno ((int) -res);
      return -1;
      }
     return 0;
   }

  fh = (int)Fopen (filename, 2);
  if (fh < 0)
    {
      if ((fh == -ENOTDIR) && (_enoent(filename)))
	fh = -ENOENT;
      __set_errno (-fh);
      return -1;
    }

  res = (int) Fcntl (fh, (long) &length, FTRUNCATE);
  Fclose (fh);

  if (res == -ENOSYS && length == 0)
    {
      res = (int)Fcreate (filename, 0);
      if (res >= 0)
	Fclose (res);
    }
  if (res < 0)
    {
      __set_errno (-res);
      return -1;
    }
  return 0;
}
weak_alias (__truncate, truncate)
