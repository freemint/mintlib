/* gethostname -- for now, fake by looking in environment */
/* (written by Eric R. Smith, placed in the public domain) */

#include <errno.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

/* Changed by Guido Flohr:  Include sys/param.h for maximum hostname
   length.  */
#include <sys/param.h>
#include <sys/types.h>

int
__gethostname (char *buf, size_t len)
{
    char *foo = 0;
    char xbuf[MAXHOSTNAMELEN + 1];
    int fd, r;
    size_t real_length;
    
    if (!buf) {
	__set_errno (EINVAL);
	return -1;
    }

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
		if (*foo == '\r' || *foo == '\n') {
		    *foo = 0;
		    break;
		}
		++foo;
	    }
	    foo = xbuf;
	}
	close(fd);
    }
    
    if (!foo)
	foo = getenv("HOSTNAME");
    
    /* Changed by Guido Flohr: Warn if buffer was too small.  */
    real_length = strlen (foo ? foo : "unknown");
    
    strncpy(buf, foo ? foo : "unknown", len < MAXHOSTNAMELEN  ? 
	    len : MAXHOSTNAMELEN);
    
    if (real_length > len) {
	__set_errno (ENAMETOOLONG);
	return -1;
    }
    
    return 0;
}
weak_alias (__gethostname, gethostname)

/* New stubs function:  sethostname.  */
int
__sethostname (name, length)
    const char* name;
    size_t length;
{
    __set_errno (ENOSYS);
    return -1;
}
weak_alias (__sethostname, sethostname)

