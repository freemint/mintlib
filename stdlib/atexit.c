/* from Dale Schumacher's dLibs */
/* heavily modified by ers and jrb */
/* and separated from main.c 5/5/92 sb */

#include <stddef.h>
#include <stdlib.h>
#include <memory.h>

/* functions registered by user for calling at exit */
#ifdef __STDC__
typedef void (*ExitFn)(void);
#else
typedef void (*ExitFn)();
#endif
extern ExitFn *_at_exit;
extern int _num_at_exit;	/* number of functions registered - 1 */

/* register a function for execution on termination */
/* Ansi requires atleast 32 entries, we make it dynamic and hope
   it meets the ansi requirement */
 
int atexit(func)
	ExitFn func;
{
        ExitFn *new_at_exit = _at_exit;
    
	if (_num_at_exit == 0)
		new_at_exit = (ExitFn *)malloc((size_t)sizeof(ExitFn));
	else
		new_at_exit = (ExitFn *)realloc(new_at_exit,
			(size_t)((_num_at_exit + 1) * sizeof(ExitFn)));
	if(new_at_exit == (ExitFn *)NULL)
		return -1;	/* failure */

        _at_exit = new_at_exit;
	_at_exit[_num_at_exit++] = func;
	return 0;		/* success */
}
