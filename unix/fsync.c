/*
 * FILE
 *	fsync.c
 *	
 * DESCRIPTION
 *	syncing filesystems, makes only sense with mint
 *	
 * BUGS
 *	fsync does the same as sync()
 */

#include <errno.h>
#include <mint/mintbind.h>

int __sync (void);

/*
 * FUNCTION
 *	int fsync(int fd)
 *	
 * DESCRIPTION
 *	sync all buffers related to file descriptor fd
 *  for now, just call the sync() function.
 */
int
__fsync (int fd)
{
	static int have_Fsync = 1;
	
	if (have_Fsync) {
		long r;

		r = Fsync (fd);
		if (r == -ENOSYS) {
			have_Fsync = 0;
		}
		else {
			if (r < 0) {
				__set_errno (-r);
				return -1;
			}
			return 0;
		}
	}

	return __sync ();
}
weak_alias (__fsync, fsync)
