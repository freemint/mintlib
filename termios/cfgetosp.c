/*
Public domain termios cfgetospeed() for the MiNT library
10 October 1993 entropy@terminator.rs.itd.umich.edu -- first attempt
*/

#ifdef __TURBOC__
# include <sys\types.h>
# include <sys\termios.h>
#else
# include <sys/types.h>
# include <sys/termios.h>
#endif

speed_t
cfgetospeed(stp)
  const struct termios *stp;
{
  return stp->_c_ospeed;
}

