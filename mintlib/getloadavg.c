#include <compiler.h>
#ifdef __TURBOC__
#include <sys\param.h>
#else
#include <sys/param.h>
#endif
#include <unistd.h>
#include <errno.h>
#include <mintbind.h>

int
getloadavg (loadavg, nelem)
     double *loadavg;
     int nelem;
{
  long uptime, avenrun[3], r;
  int i;

  r = Suptime (&uptime, avenrun);
  if (r < 0)
    {
      errno = (int) -r;
      return -1;
    }

  for (i = 0; i < nelem && i < 3; i++)
    loadavg[i] = (double) avenrun[i] / FSCALE;

  return i;
}
