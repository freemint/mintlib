/* console I/O routines */
/* written by Eric R. Smith, placed in the public domain */

/* BUGS: under TOS, all tty input is assumed to come from the keyboard
 * (unless we can figure out otherwise)
 */

#include <osbind.h>
#include <mintbind.h>
#include <support.h>
#include <errno.h>

#define CTRL(x) (x & 0x1f)
#define CBUFSIZ 80

int
_console_read_byte(fd)
	int fd;
{
	short f;
	int retvalue;

	if ((retvalue = (int)Fgetchar(fd, 0)) != -ENOSYS)
		return retvalue;

	if (fd == 0)
		return (int)Crawcin();
	if (fd == 2)
		return (int)Cauxin();

	f = fd;
	if (f < 0 && f >= -3)
		return (int)Bconin(f+3);
	return (int)Bconin(2);
}

void
_console_write_byte(fd, outc)
	int fd, outc;
{
	unsigned char c;

	c = outc;
	(void)Fwrite(fd, 1L, &c);
}
