/* lchown -- change the owner and group of a file */
/* while _not_ following the symbolic links */
/* written by Standa Opichal */

#include <errno.h>
#include <limits.h>
#include <sys/types.h>
#include "lib.h"

int
__lchown (const char *_name, uid_t uid, gid_t gid)
{
	return __do_chown16( _name, uid, gid, 0 );
}
weak_alias (__lchown, lchown)
