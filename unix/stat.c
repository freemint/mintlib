#ifdef __TURBOC__
# include <sys\stat.h>
#else
# include <sys/stat.h>
#endif

__EXTERN int _do_stat __PROTO((const char *_path, struct stat *st, int lflag));

int
__stat(path, st)
	const char *path;
	struct stat *st;
{
	return _do_stat(path, st, 0);
}

weak_alias (__stat, stat)
