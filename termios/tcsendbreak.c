/*
Public domain termios tcsendbreak() for the MiNT library
10 October 1993 entropy@terminator.rs.itd.umich.edu -- first attempt
*/

#include <errno.h>
#include <termios.h>

#include <sys/ioctl.h>
#include <mint/mintbind.h>

int
tcsendbreak(int fd, int duration)
{
  long oldmask;
  long r;

  oldmask = Psigblock(~0L);
  r = Fcntl((short) fd, (long) 0, TIOCSBRK);
  if (r < 0) {
    __set_errno ((int) -r);
    r = -1;
  } else {
    /* POSIX says a duration of 0 sends a break 250 to 500 ms long. */
    if (duration == 0)
      duration = 250;
    /* POSIX does not specify the units for duration.
       We use milliseconds.
    */
    (void) Fselect((short) duration, 0L, 0L, 0L);
    r = Fcntl((short) fd, (long) 0, TIOCCBRK);
    if (r < 0) {
      __set_errno ((int) -r);
      r = -1;
    } else {
      r = 0;
    }
  }
  (void) Psigsetmask(oldmask);
  return (int) r;
}
