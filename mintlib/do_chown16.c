/* chown16 -- change the owner and group of a file */
/* by Standa Opichal */
/* originaly chown by Eric R. Smith and placed in the public domain */
/* this is faked if MiNT is not running */

#include <errno.h>
#include <limits.h>
#include <unistd.h>
#include <sys/types.h>
#include <mint/mintbind.h>
#include "lib.h"

int
__do_chown16 (const char *_name, uid_t uid, gid_t gid, int follow_links)
{
	char namebuf[PATH_MAX];
	char *name = (char *) _name;
	int r;

	if (_name == NULL) {
		__set_errno (EFAULT);
		return -1;
	}

	if (!__libc_unix_names) {
		name = namebuf;
		(void)_unx2dos(_name, name, sizeof (namebuf));
	}

	r = (int)Fchown16(name, uid, gid, follow_links);
	if (r == -ENOSYS)
		// fallback to Fchown if Fchown16 is not available
		r = (int)Fchown(name, uid, gid);

	if (r && (r != -ENOSYS)) {
		__set_errno (-r);
		return -1;
	}
	return 0;
}


