/*
 * getpagesize() for MiNT
 * written by Eric R. Smith and placed in the public
 * domain
 */

#include <unistd.h>
#include <osbind.h>
#include <string.h>
#include <mintbind.h>

#define DEF_PAGESIZE 8192	/* default page size for TOS */

extern int __mint;

static void memstats __PROTO((long *));

/*
 * memstats: get information about memory usage, and put it into
 * the 4 long words pointed to by "meminfo" as follows:
 * 	meminfo[0]	number of free pages
 *	meminfo[1]	total number of pages being managed
 *	meminfo[2]	page size
 *	meminfo[3]	reserved, always 1
 * works only under MiNT
 */

static void
memstats(meminfo)
	long *meminfo;
{
	int olddrv;
	char oldpath[128];

	olddrv = Dgetdrv();	/* save current drive */
	Dsetdrv('U'-'A');	/* change to drive U: */
	Dgetpath(oldpath, 0);	/* save current path for drive U: */
	if (oldpath[0] == 0)
		strcpy(oldpath, "\\");
	Dsetpath("U:\\PROC");	/* change to the PROC directory */
				/* note that Dfree() on drive U: is sensitive
				 * to the path, so we must do this!
				 */

	Dfree((_DISKINFO*)meminfo, 0); /* get memory statistics */

	Dsetpath(oldpath);	/* restore old path for drive U: */
	Dsetdrv(olddrv);	/* restore old drive */
}

int
getpagesize()
{
	long meminfo[4];

	if (__mint < 9)
		return DEF_PAGESIZE;

/* get the page size by looking at U:\PROC */
	memstats(meminfo);
	return (int) ((meminfo[2] > DEF_PAGESIZE) ? meminfo[2] : DEF_PAGESIZE);
}
