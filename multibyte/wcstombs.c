#include <stdlib.h>
#include <wchar.h>

size_t wcstombs(char *__restrict s, const wchar_t *__restrict ws, size_t n)
{
	return wcsrtombs(s, &(const wchar_t *){ws}, n, 0);
}
