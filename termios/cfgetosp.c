/*
Public domain termios cfgetospeed() for the MiNT library
10 October 1993 entropy@terminator.rs.itd.umich.edu -- first attempt
*/

#include <termios.h>

speed_t
cfgetospeed(const struct termios *stp)
{
  return stp->_c_ospeed;
}
