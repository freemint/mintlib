/*
Public domain termios tcsendbreak() for the MiNT library
10 October 1993 entropy@terminator.rs.itd.umich.edu -- first attempt
*/

#include <mintbind.h>
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

int
tcsendbreak(fd, duration)
  int fd;
  int duration;
{
  long oldmask;
  long r;

  oldmask = Psigblock(~0L);
  r = Fcntl((short) fd, (long) 0, TIOCSBRK);
  if (r < 0) {
    errno = (int) -r;
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
      errno = (int) -r;
      r = -1;
    } else {
      r = 0;
    }
  }
  (void) Psigsetmask(oldmask);
  return (int) r;
}
