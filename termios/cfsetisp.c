/*
Public domain termios cfsetispeed() for the MiNT library
10 October 1993 entropy@terminator.rs.itd.umich.edu -- first attempt
*/

#include <termios.h>

int
cfsetispeed(struct termios *stp, speed_t baudcode)
{
  stp->_c_ispeed = baudcode;
  return 0;
}
