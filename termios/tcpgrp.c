/*
Public domain termios tc[get|set]pgrp() for the MiNT library
10 October 1993 entropy@terminator.rs.itd.umich.edu -- first attempt
*/

#include <mintbind.h>
#include <errno.h>
#include <limits.h>

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

#include <unistd.h>

pid_t
tcgetpgrp(fd)
  int fd;
{
  long pg;
  long r;

  r = Fcntl((short) fd, (long) &pg, TIOCGPGRP);
  if (r < 0) {
    errno = (int) -r;
    return -1;
  }
#if 0
  /* IEEE Std. 1003.1-1990: if there is no foreground process group, return
     a value greater than 1 that does not match an existing process group.
  */
  while ((pg == 0) || (r != -ENOENT)) {
    for (pg = 2; pg < INT_MAX; pg++) {
      r = Pkill((short) -pg, 0);
      if (r == -ENOENT)
        break;
    }
  }
#else
  /* Sigh.  Some programs (notably bash) rely on this giving an error. */
  if (pg == 0) {
    errno = ENOENT;
    return -1;
  }
#endif
  return (pid_t) pg;
}

int
tcsetpgrp(fd, pgrp)
  int fd;
  pid_t pgrp;
{
  long r;
  long pg;

  pg = (long) pgrp;
  r = Fcntl((short) fd, (long) &pg, TIOCSPGRP);
  if (r < 0) {
    errno = (int) -r;
    return -1;
  }
  return 0;
}
