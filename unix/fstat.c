
#include <sys/stat.h>
#include "lib.h"

int
__fstat (int fd, struct stat *st)
{
	return __do_fstat (fd, st, 1);
}
weak_alias (__fstat, fstat)
