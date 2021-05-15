/*
 * Written by Eric R. Smith for the Atari ST
 */

#include <sys/ioctl.h>

__typeof__(stty) __stty;

int
__stty (int fd, struct sgttyb *_tty)
{
	return ioctl (fd, TIOCSETP, _tty);
}
weak_alias (__stty, stty)
