/*  binmode.c -- MiNTLib.
    Copyright (C) 2000 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

/*
 * If called with non-zero argument, then subsequently all fopens have 
 * __binary set in __mode.
 */

#include <stdio.h>

extern __io_mode __default_mode__;

void 
__binmode (int binmode)
{
    if (binmode)
	__default_mode__.__binary = 1;
    else
	__default_mode__.__binary = 0;
}
/* For backwards compatibility:  */
strong_alias (__binmode, _binmode)

/* Set binary mode on open STREAM.  This has no other effect than setting
   the __binary mode when called for non-file streams.  */
void
__set_binmode (FILE* stream, int binmode)
{
	if (binmode && stream->__io_funcs.__read 
		       == __default_text_io_functions.__read)
		stream->__io_funcs = __default_io_functions;
	else if (!binmode && stream->__io_funcs.__read 
		       == __default_io_functions.__read)
		stream->__io_funcs = __default_text_io_functions;
	stream->__mode.__binary = binmode;
}
