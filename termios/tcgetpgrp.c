/*
Public domain termios tc[get|set]pgrp() for the MiNT library
10 October 1993 entropy@terminator.rs.itd.umich.edu -- first attempt
*/

#include <errno.h>
#include <limits.h>
#include <termios.h>
#include <unistd.h>

#include <sys/ioctl.h>
#include <sys/file.h>
#include <mint/mintbind.h>

pid_t
tcgetpgrp(int fd)
{
  long pg;
  long r;

  r = Fcntl((short) fd, (long) &pg, TIOCGPGRP);
  if (r < 0) {
    __set_errno ((int) -r);
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
    __set_errno (ENOENT);
    return -1;
  }
#endif
  return (pid_t) pg;
}
