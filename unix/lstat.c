#ifdef __TURBOC__
# include <sys\stat.h>
#else
# include <sys/stat.h>
#endif

#include "lib.h"

__EXTERN int _do_stat __PROTO((const char *_path, struct stat *st, int lflag));

int
__lstat(path, st)
	const char *path;
	struct stat *st;
{
	return _do_stat(path, st, 1);
}

weak_alias (__lstat, lstat)
