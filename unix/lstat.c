
#include <sys/stat.h>
#include "lib.h"

int
__lstat (const char *path, struct stat *st)
{
	return __do_stat (path, st, 1);
}
weak_alias (__lstat, lstat)
