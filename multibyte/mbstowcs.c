#include <stdlib.h>
#include <wchar.h>

size_t mbstowcs(wchar_t *__restrict ws, const char *__restrict s, size_t wn)
{
	return mbsrtowcs(ws, (void*)&s, wn, 0);
}
