/*  xtoy.c -- MiNTLib.
    Copyright (C) 2000 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <endian.h>
#include <netinet/in.h>

#if BYTE_ORDER != BIG_ENDIAN
# error You lose with this file on little-endian machines.
#endif

uint16_t 
__x2short (uint16_t x)
{
	return x;
}

uint32_t 
__x2long (uint32_t x)
{
	return x;
}

#undef htons
#undef ntohs
#undef htonl
#undef ntohl

strong_alias (__x2short, htons)
strong_alias (__x2short, ntohs)
strong_alias (__x2long, htonl)
strong_alias (__x2long, ntohl)
