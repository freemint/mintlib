/*
**  SCANDIR
**  Scan a directory, collecting all (selected) items into a an array.
*/

#include <compiler.h>
#include <stdlib.h>	/* for qsort */
#include <string.h>

#ifdef __TURBOC__
#include <sys\types.h>
#include <sys\dir.h>
#else
#include <sys/types.h>
#include <sys/dir.h>
#endif

#ifndef NULL
#define NULL 0
#endif

/* Initial guess at directory size. */
#define INITIAL_SIZE	20

int scandir __PROTO((char *name, struct direct ***list,
	int (*selector)(struct direct *),
	int (*sorter)(const void *, const void *)));

int
scandir(name, list, selector, sorter)
    char		  *name;
    struct direct	***list;
    int			 (*selector) __PROTO((struct direct *));
    int			 (*sorter) __PROTO((const void *, const void *));
{
    register struct direct	 **names;
    register struct direct	  *entp;
    register DIR	  *dirp;
    register int	   i;
    register int	   size;

    /* Get initial list space and open directory. */
    size = INITIAL_SIZE;
    names = (struct direct **)malloc(size * sizeof(struct direct *));
    if (names == NULL)
	return -1;
    dirp = opendir(name);
    if (dirp == NULL)
	return -1;

    /* Read entries in the directory. */
    for (i = 0; (entp = readdir(dirp)) != NULL; )
	if (selector == NULL || (*selector)(entp)) {
	    /* User wants them all, or he wants this one. */
	    if (++i >= size) {
		size <<= 1;
		names = (struct direct **)
		    realloc((char *)names, size * sizeof names[0]);
		if (names == NULL) {
		    closedir(dirp);
		    return -1;
		}
	    }

	    /* Copy the entry. */
	    names[i - 1] = (struct direct *)malloc(DIRSIZ(entp));
	    if (names[i - 1] == NULL) {
		closedir(dirp);
		return -1;
	    }
	    names[i - 1]->d_ino = entp->d_ino;
	    names[i - 1]->d_reclen = entp->d_reclen;
	    names[i - 1]->d_namlen = entp->d_namlen;
	    (void)strcpy(names[i - 1]->d_name, entp->d_name);
	}

    /* Close things off. */
    names[i] = NULL;
    *list = names;
    closedir(dirp);

    /* Sort? */
    if (i && sorter)
	qsort((char *)names, i, sizeof names[0], sorter);

    return i;
}
