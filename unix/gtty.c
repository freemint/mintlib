/*
 * Written by Eric R. Smith for the Atari ST
 */

#include <sys/ioctl.h>

int
__gtty (int fd, struct sgttyb *_tty)
{
	return ioctl (fd, TIOCGETP, _tty);
}
weak_alias (__gtty, gtty)
