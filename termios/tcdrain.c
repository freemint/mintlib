/*
Public domain termios tcdrain() for the MiNT library
10 October 1993 entropy@terminator.rs.itd.umich.edu
*/

#include <errno.h>

#ifdef __TURBOC__
# include <sys\ioctl.h>
# include <sys\types.h>
# include <sys\termios.h>
#else
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/termios.h>
#endif

#include <mintbind.h>

int
tcdrain(fd)
  int fd;
{
  long outq;
  long r;

  do
  {
    r = Fcntl((short) fd, &outq, TIOCOUTQ);
    if (r < 0) {
      errno = (int) -r;
      return -1;
    }
  } while (outq != 0);
  return 0;
}

