
#include <grp.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <mint/mintbind.h>

#ifdef HAVE_WEAK_SYMBOLS
__typeof__(initgroups) __initgroups;
# define initgroups __initgroups
#endif

int
initgroups (const char *user, gid_t group)
{
  struct group *g;
  unsigned short groups[NGROUPS_MAX];
  int n;
  long r;

  n = 0;
  groups[n++] = group;
  setgrent ();
  while (n < NGROUPS_MAX && (g = getgrent ()) != NULL)
    if (g->gr_gid != group)
      {
        char **m;

        for (m = g->gr_mem; *m != NULL; ++m)
          if (!strcmp (*m, user))
            groups[n++] = g->gr_gid;
      }
  endgrent ();
  r = Psetgroups (n, groups);
  if (r < 0)
    {
      __set_errno (-r);
      return -1;
    }
  return 0;
}

#undef initgroups
weak_alias (__initgroups, initgroups)
