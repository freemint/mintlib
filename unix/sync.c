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

#include <errno.h>
#include <support.h>
#include <mint/mintbind.h>

/*
 * FUNCTION
 *	int sync(void)
 *	
 * DESCRIPTION
 *	call MiNT's sync system call
 */
int
__sync (void)
{
	long res;

	res = Sync ();
	if (res < 0)
	{
		__set_errno (-res);
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
main (void)
{
	sync ();
	return 0;
}
#endif

