/*
 * Written by Eric R. Smith for the Atari ST
 */

#ifdef __TURBOC__
# include <sys\ioctl.h>
#else
# include <sys/ioctl.h>
#endif

int
__stty(fd, _tty)
	int fd;
	struct sgttyb *_tty;
{
	return ioctl(fd, TIOCSETP, _tty);
}

weak_alias (__stty, stty)
