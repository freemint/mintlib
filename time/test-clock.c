#include <signal.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

volatile int gotit = 0;

void
alarm_handler (int signal)
{
    gotit = 1;
}


int
main (int argc, char ** argv)
{
  clock_t start, stop;
  double deviation;
  int status = 0;
  
  if (signal(SIGALRM, alarm_handler) == SIG_ERR)
    {
      perror ("signal");
      exit (1);
    }
  alarm(1);
  start = clock ();
  while (!gotit);
  stop = clock ();

  printf ("%ld clock ticks per second (start=%ld,stop=%ld)\n",
	  stop - start, start, stop);

  deviation = ((double) (stop - start)) / (double) CLOCKS_PER_SEC;
  
  if (deviation < 0.8 || deviation > 1.2) {
  	fflush (stdout);
  	fprintf (stderr, "error: deviation %g (> 20 %%)\n", deviation);
  	fflush (stderr);
  	status = 1;
  }
#if 0
  /* _SC_CKL_TCK not yet supported.  */
  printf ("CLOCKS_PER_SEC=%d, sysconf(_SC_CLK_TCK)=%ld\n",
	  CLOCKS_PER_SEC, sysconf(_SC_CLK_TCK));
#else
  printf ("CLOCKS_PER_SEC=%ld\n",
	  CLOCKS_PER_SEC);
#endif
  return status;
}
