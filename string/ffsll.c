/*  ffsll.c -- MiNTLib.
    Copyright (C) 2000 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#define ffsll foobar_ffsll
#include <string.h>
#undef ffsll

int 
ffsll (bits)
	long long int bits;
{
	unsigned long long int ind = (bits & -bits);
	
	if (ind <= 0xffffffff)
		return __ffsl (bits);
	else
    		return 32 + __ffsl (bits >> 32);
}
