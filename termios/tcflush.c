/*
Public domain termios tcflush() for the MiNT library
10 October 1993 entropy@terminator.rs.itd.umich.edu -- first attempt
*/

#include <mintbind.h>
#include <errno.h>

#ifdef __TURBOC__
# include <sys\ioctl.h>
# include <sys\file.h>
# include <sys\types.h>
# include <sys\termios.h>
#else
# include <sys/ioctl.h>
# include <sys/file.h>
# include <sys/types.h>
# include <sys/termios.h>
#endif

int
tcflush(fd, action)
  int fd;
  int action;
{
  long flushtype;
  long r;

  switch (action)
  {
    case TCIFLUSH:
      flushtype = FREAD;
      break;
    case TCOFLUSH:
      flushtype = FWRITE;
      break;
    case TCIOFLUSH:
      flushtype = 0;
      break;
    default:
      errno = EINVAL;
      return -1;
  }
  r = Fcntl((short) fd, &flushtype, TIOCFLUSH);
  if (r < 0) {
    errno = (int) -r;
    return -1;
  }
  return 0;
}

