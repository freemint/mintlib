/*
Public domain termios tcflush() for the MiNT library
10 October 1993 entropy@terminator.rs.itd.umich.edu -- first attempt
*/

#include <errno.h>
#include <termios.h>

#include <sys/ioctl.h>
#include <sys/file.h>
#include <mint/mintbind.h>

int
tcflush(int fd, int action)
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
      flushtype = FREAD | FWRITE;
      break;
    default:
      __set_errno (EINVAL);
      return -1;
  }
  r = Fcntl((short) fd, &flushtype, TIOCFLUSH);
  if (r < 0) {
    __set_errno ((int) -r);
    return -1;
  }
  return 0;
}
