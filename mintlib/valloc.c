#include "lib.h"
#include <stdlib.h>
#include <malloc.h>
#include <unistd.h>

__typeof__(valloc) __valloc;

void *__valloc(size_t size)
{
	return memalign(getpagesize(), size);
}

weak_alias(__valloc, valloc)
