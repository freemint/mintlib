#include <net/if.h>
#include <stdlib.h>

__typeof__(if_freenameindex) __if_freenameindex;

void 
__if_freenameindex(struct if_nameindex *idx)
{
	free(idx);
}

weak_alias (__if_freenameindex, if_freenameindex)