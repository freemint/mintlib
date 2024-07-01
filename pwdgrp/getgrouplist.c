#include <grp.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <mint/mintbind.h>

__typeof__(getgrouplist) __getgrouplist;

#ifdef HAVE_WEAK_SYMBOLS
__typeof__(getgrouplist) __getgrouplist;
# define getgrouplist __getgrouplist
#endif

int getgrouplist(const char *user, gid_t group, gid_t *groups, int *ngroups)
{
	int sz = *ngroups;
	struct group *g;
	int n;

	n = 0;
	if (n < sz)
		groups[n] = group;
	n++;
	setgrent();
	while ((g = getgrent()) != NULL)
	{
		if (g->gr_gid != group)
		{
			char **m;

			for (m = g->gr_mem; *m != NULL; ++m)
				if (strcmp(*m, user) == 0)
				{
					if (n < sz)
						groups[n] = g->gr_gid;
					n++;
				}
		}
	}
	endgrent();
	if (sz > n)
		sz = n;
	if (sz < n)
		sz = -1;
	*ngroups = n;
	return sz;
}

#undef getgrouplist
weak_alias (__getgrouplist, getgrouplist)
