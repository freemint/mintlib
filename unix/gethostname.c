/* gethostname -- for now, fake by looking in environment */
/* (written by Eric R. Smith, placed in the public domain) */

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

/* Changed by Guido Flohr:  Include sys/param.h for maximum hostname
   length.  */
#ifdef __TURBOC__
# include <sys\param.h>
# include <sys\types.h>
#else
# include <sys/param.h>
# include <sys/types.h>
#endif

int
gethostname(buf, len)
	char *buf;
	size_t len;
{
	char *foo = 0;
	char xbuf[MAXHOSTNAMELEN + 1];
	int fd, r;
  size_t real_length;
  
#if 0
	if (!foo) {
#endif
/* try looking for the file /etc/hostname; if it's present,
 * it contains the name, otherwise we try the environment
 */
		fd = open("/etc/hostname", O_RDONLY);
		if (fd >= 0) {
			r = read(fd, xbuf, MAXHOSTNAMELEN);
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
#if 0
	}
#endif
	if (!foo)
		foo = getenv("HOSTNAME");

  /* Changed by Guido Flohr: Warn if buffer was too small.  */
  real_length = strlen (foo ? foo : "unknown");
  
	strncpy(buf, foo ? foo : "unknown", len < MAXHOSTNAMELEN  ? 
	                                        len : MAXHOSTNAMELEN);
	
	if (real_length > len) {
	  errno = ENAMETOOLONG;
	  return -1;
	}
	
	return 0;
}

/* New stubs function:  sethostname.  */
int
sethostname (name, length)
     const char* name;
     size_t length;
{
  errno = ENOSYS;
  return -1;
}
