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
    __set_errno ((int) -r);
    return -1;
  }
  return 0;
}
