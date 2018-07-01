#include "lib.h"
#include <stdlib.h>
#include <malloc.h>
#include <unistd.h>


void *__valloc(size_t size)
{
	return memalign(getpagesize(), size);
}

weak_alias(__valloc, valloc)
