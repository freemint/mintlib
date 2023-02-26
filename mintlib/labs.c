/* return absolute values */
#include <stdlib.h>

#ifdef labs
#undef labs
#endif

strong_alias(abs, labs)
