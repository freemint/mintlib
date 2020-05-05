/*  mkdtemp.c -- MiNTLib.

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <stdlib.h>
#include <sys/stat.h>

char *mkdtemp(char *template)
{
	if (mktemp(template) == NULL)
		return NULL;

	if (mkdir(template, 0700) < 0)
		return NULL;

	return template;
}
