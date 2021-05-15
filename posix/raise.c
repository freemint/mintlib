/* I think ANSI wants this. It's useful, at any rate.
   -- ERS
*/

#include <unistd.h>
#include <signal.h>

int
raise (int sig)
{
  return __kill (__getpid (), sig);
}
weak_alias (raise, gsignal)
