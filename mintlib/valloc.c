#include "lib.h"
#include <stdlib.h>
#include <malloc.h>


void *__valloc(size_t size)
{
	return memalign(getpagesize(), size);
}

weak_alias(__valloc, valloc)
