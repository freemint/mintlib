/*
 * Written by Eric R. Smith for the Atari ST
 */

#ifdef __TURBOC__
# include <sys\ioctl.h>
#else
# include <sys/ioctl.h>
#endif

int
__gtty(fd, _tty)
	int fd;
	struct sgttyb *_tty;
{
	return ioctl(fd, TIOCGETP, _tty);
}

weak_alias (__gtty, gtty)
