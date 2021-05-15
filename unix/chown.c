/* chown -- change the owner and group of a file */
/* while _following_ the symbolic links */
/* written by Standa Opichal */

#include <errno.h>
#include <limits.h>
#include <sys/types.h>
#include <unistd.h>
#include "lib.h"

__typeof__(chown) __chown;

int
__chown (const char *_name, uid_t uid, gid_t gid)
{
	return __do_chown16( _name, uid, gid, 1 );
}
weak_alias (__chown, chown)
