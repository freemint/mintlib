/* gethostname -- for now, fake by looking in environment */
/* (written by Eric R. Smith, placed in the public domain) */

/* Modified by Guido Flohr: If no domain name available
   return the empty string instead of "(none)".  */
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <support.h>

#define MAXLEN 127

int
getdomainname(buf, len)
	char *buf;
	size_t len;
{
	char *foo = 0;
	char xbuf[MAXLEN+1];
	int fd, r;

	fd = open("/etc/domainname", O_RDONLY);
	if (fd >= 0) {
		r = read(fd, xbuf, MAXLEN);
		if (r > 0) {
			xbuf[r] = 0;
			foo = xbuf;
			while (*foo) {
				if (*foo == '\r' || *foo == '\n')
					*foo = 0;
				foo++;
			}
			foo = xbuf;
		}
		close(fd);
	}
	strncpy(buf, foo ? foo : "", len);
	return 0;
}
