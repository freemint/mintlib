/*
 * Errno defs to be included in *.ss floating point routines, from <errno.h>
 *   -- hyc@hanauma.jpl.nasa.gov, 9-17-92
 */

#include "errno.h"

	.globl	_errno

Edom	= EDOM
Erange	= ERANGE

#define Errno	_errno
#define Stderr	__iob+52

#ifdef __MSHORT__
#define Emove	movew
#else
#define Emove	movel
#endif
