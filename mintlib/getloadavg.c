
#include <errno.h>
#include <unistd.h>
#include <sys/param.h>
#include <mint/mintbind.h>

int
getloadavg(double *loadavg, int nelem)
{
  long uptime, avenrun[3], r;
  int i;

  r = Suptime(&uptime, avenrun);
  if (r < 0)
    {
      __set_errno(-r);
      return -1;
    }

  for (i = 0; i < nelem && i < 3; i++)
    loadavg[i] = (double) avenrun[i] / FSCALE;

  return i;
}
