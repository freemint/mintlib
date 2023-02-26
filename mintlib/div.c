/*  div.c -- MiNTLib.
    Copyright (C) 2000 Frank Naumann <fnaumann@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

/* Modified by Guido Flohr <guido@freemint.de>:
   - Make ldiv a strong alias for div when not compiling mshort.  */
   
#include <stdlib.h>

div_t
div(int num, int denom)
{
	div_t res;
	
	res.quot = num / denom;
	res.rem = num % denom;
	
	return res;
}
strong_alias (div, ldiv)

