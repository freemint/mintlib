/* SVR4 ABI requires <wait.h> rather than <sys/wait.h> */

#ifdef __TURBOC__
# include <sys\wait.h>
#else
# include <sys/wait.h>
#endif
