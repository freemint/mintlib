#ifdef __TURBOC__
# include <sys\types.h>
#else
# include <sys/types.h>
#endif

ino_t __inode = 32; /* used in readdir, _do_stat, fstat */

