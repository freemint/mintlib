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
#include <mintbind.h>

extern int errno;

__EXTERN int sync __PROTO ((void));

/*
 * FUNCTION
 *	int fsync(int fd)
 *	
 * DESCRIPTION
 *	sync all buffers related to file descriptor fd
 *  for now, just call the sync() function.
 */
int
__fsync(fd)
	int	fd;
{
	static int have_Fsync = 1;
	
	if (have_Fsync)
	  {
  	    long r = Fsync (fd);
	    if (r == -ENOSYS)
	      have_Fsync = 0;
	    else
	      {
	        if (r < 0)
	          {
	            __set_errno (-r);
	            return -1;
	          }
	        return 0;
	      }
	  }
	
	return sync();
}

weak_alias (__fsync, fsync)

#ifdef TEST

/*
 * Im not in the mood to write a tricky test routine,
 * so just do 'cat junk1 >junk2;sync' from your shell
 * and listen to your harddisk.
 */
int
main()
{
	fsync(0xdead);
	return 0;
}

#endif
