
#include <sys/stat.h>
#include "lib.h"

int
__stat (const char *path, struct stat *st)
{
	return __do_stat (path, st, 0);
}
weak_alias (__stat, stat)
