/*
Public domain termios cfsetospeed() for the MiNT library
10 October 1993 entropy@terminator.rs.itd.umich.edu -- first attempt
*/

#ifdef __TURBOC__
# include <sys\types.h>
# include <sys\termios.h>
#else
# include <sys/types.h>
# include <sys/termios.h>
#endif

int
cfsetospeed(stp, baudcode)
  struct termios *stp;
  speed_t baudcode;
{
  stp->_c_ospeed = baudcode;
  return 0;
}

