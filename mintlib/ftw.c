/*
**  FTW
**  Walk a directory hierarchy from a given point, calling a user-supplied
**  function at each thing we find.  If we go below a specified depth,
**  recycle file descriptors.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/dir.h>
#include <ftw.h>

#define EQ(a, b)	(strcmp((a), (b)) == 0)

#if 0
#define DEEP_LIMIT
#endif

int
ftw(char *directory, int (*funcptr)(const char *, struct stat *, int), int depth)
{
    struct stat stats;
    struct direct *entp;
    register DIR *dirp;
    register char *p;
    register long i;
    char *fullpath;
#ifdef DEEP_LIMIT
    long seekpoint = 0;
#endif

    /* If can't stat, tell the user so. */
    if (stat(directory, &stats) < 0)
	return (*funcptr)(directory, &stats, FTW_NS);

    /* If it's not a directory, call the user's function. */
    if ((stats.st_mode & S_IFMT) != S_IFDIR)
	/* Saying "FTW_F" here is lying; what if this is a symlink? */
	return (*funcptr)(directory, &stats, FTW_F);

    /* Open directory; if we can't, tell the user so. */
    dirp = opendir(directory);
    if (dirp == NULL)
	return (*funcptr)(directory, &stats, FTW_DNR);

    /* See if user wants to go further. */
    i = (*funcptr)(directory, &stats, FTW_D);
    if (i) {
	closedir(dirp);
	return (int)i;
    }

    /* Get ready to hold the full paths. */
    i = strlen(directory);
    fullpath = malloc( (size_t) (i + 1 + MAXNAMLEN + 1) );
    if (fullpath == NULL) {
	closedir(dirp);
	return -1;
    }
    (void)strcpy(fullpath, directory);
    p = &fullpath[i];
    if (i && p[-1] != '/')
	*p++ = '/';

    /* Read all entries in the directory.. */
    while ((entp = readdir(dirp)) != 0)
	if (!EQ(entp->d_name, ".") && !EQ(entp->d_name, "..")) {
#ifdef DEEP_LIMIT
	    if (depth <= 1) {
		/* Going too deep; checkpoint and close this directory. */
		seekpoint = telldir(dirp);
		closedir(dirp);
		dirp = NULL;
	    }
#endif
	    /* Process the file. */
	    (void)strcpy(p, entp->d_name);
	    i = ftw(fullpath, funcptr, depth - 1);
	    if (i) {
		/* User's finished; clean up. */
		free(fullpath);
		if (dirp)
		    closedir(dirp);
		return (int)i;
	    }

#ifdef DEEP_LIMIT
	    /* Reopen the directory if necessary. */
	    if (dirp == NULL) {
		dirp = opendir(directory);
		if (dirp == NULL) {
		    free(fullpath);
		    return -1;
		}
		seekdir(dirp, seekpoint);
	    }
#endif
	}

    /* Clean up. */
    free(fullpath);
    closedir(dirp);
    return 0;
}
