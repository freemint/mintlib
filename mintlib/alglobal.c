/*
 * lineA globals for both inline and non-inline lineA bindings
 */
#include <mint/linea.h>
	/* global vars */
/* Pointer to line a parameter block returned by init 	*/
 __LINEA *__aline;

/* Array of pointers to the three system font  headers 
   returned by init (in register A1)	           	*/
 __FONT  **__fonts;

/* Array of pointers to the 16 line a functions returned
   by init (in register A2) only valid in ROM'ed TOS     */
#ifdef __STDC__
 short  (**__funcs)(void);
#else
 short  (**__funcs)();
#endif
