/*
Public domain termios cfsetospeed() for the MiNT library
10 October 1993 entropy@terminator.rs.itd.umich.edu -- first attempt
*/

#include <termios.h>

int
cfsetospeed(struct termios *stp, speed_t baudcode)
{
  stp->_c_ospeed = baudcode;
  return 0;
}
