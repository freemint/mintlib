/*  llabs.c -- MiNTLib.
    Copyright (C) 2000 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/
   
#include <stdlib.h>

#undef llabs

/* Return the absolute value of I.  */
long long int
llabs (long long int i)
{
  	return i < 0 ? -i : i;
}

weak_alias (llabs, imaxabs)
