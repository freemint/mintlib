/*  getitimer.c -- MiNTLib, 64bit version */

#include <errno.h>
#include <sys/time.h>
#include <mint/mintbind.h>
#include "lib.h"

int __setitimer64(enum __itimer_which which, const struct itimerval64 *new, struct itimerval64 *old)
{
  long int retval;
  long int new_interval; 
  long int new_value;
  long int old_interval = 0;
  long int old_value = 0;

  if (new) 
    {
      new_interval = new->it_interval.tv_sec * 1000;
      new_interval += ((new->it_interval.tv_usec + 999) / 1000);
      new_value = new->it_value.tv_sec * 1000;
      new_value += ((new->it_value.tv_usec + 999) / 1000);
    }

  retval = Tsetitimer (which, new ? (long int) &new_interval : 0L, 
                              new ? (long int) &new_value : 0L,
                              old ? (long int) &old_interval : 0L, 
                              old ? (long int) &old_value : 0L);
  if (retval < 0)
    {
      __set_errno(-retval);
      return -1;
    }

  if (old)
    {
      old->it_interval.tv_sec = old_interval / 1000;
      old->it_interval.tv_usec = (old_interval % 1000) * 1000;
      old->it_value.tv_sec = old_value / 1000;
      old->it_value.tv_usec = (old_value % 1000) * 1000;
    }

  return 0;
}
