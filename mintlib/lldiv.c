/*  lldiv.c -- MiNTLib.
    Copyright (C) 2000 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/
   
#include <stdlib.h>

lldiv_t
lldiv (num, denom)
	long long int num, denom;
{
	lldiv_t res;
	
	res.quot = num / denom;
	res.rem = num % denom;

	/* FIXME: ANSI positively requires that 
	
		abs (RES) <= abs (NUM / DENOM)
	   
	   where NUM / DENOM is to be computed in infinite precision.
	   Seemingly the current implementation fulfills these
	   requirements.  If not #define DIV_RESULTS_NEED_CORRECTION 
	   when you compile this file.  You should also change
	   div.c accordingly then.  */

#ifdef DIV_RESULT_NEEDS_CORRECTION
	if (num >= 0 && res.rem < 0) {
      		res.quot++;
      		res.rem -= denom;
    	}
#endif

	return res;
}

weak_alias (lldiv, imaxdiv)
