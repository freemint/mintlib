/*
Public domain termios tcdrain() for the MiNT library
10 October 1993 entropy@terminator.rs.itd.umich.edu
*/

#include <errno.h>
#include <termios.h>

#include <sys/ioctl.h>
#include <mint/mintbind.h>

int
tcdrain(int fd)
{
  long outq;
  long r;

  do
  {
    r = Fcntl((short) fd, &outq, TIOCOUTQ);
    if (r < 0) {
      __set_errno (-r);
      return -1;
    }
  } while (outq != 0);
  return 0;
}

