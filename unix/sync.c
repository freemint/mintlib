/*
 * FILE
 *	sync.c
 *	
 * DESCRIPTION
 *	syncing filesystems, makes only sense with mint
 *	
 * BUGS
 *	fsync does the same as sync()
 */

#include <mintbind.h>
#include <support.h>

extern int errno;

/*
 * FUNCTION
 *	int sync(void)
 *	
 * DESCRIPTION
 *	call MiNT's sync system call
 */
int
__sync()
{
	long res;
	
	res = Sync();
	if (res < 0)
	{
		errno = -res;
		return -1;
	}
	return 0;
}

weak_alias (__sync, sync)

#ifdef TEST

/*
 * Im not in the mood to write a tricky test routine,
 * so just do 'cat junk1 >junk2;sync' from your shell
 * and listen to your harddisk.
 */
int
main()
{
	sync();
	return 0;
}

#endif

