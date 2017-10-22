#include "lib.h"

#include <wchar.h>
#include <wctype.h>
#include <ctype.h>
#include <string.h>

int wcscoll(const wchar_t *ws1, const wchar_t *ws2)
{
	size_t i;

	for (i = 0; ws1[i] != 0 && ws2[i] != 0; i++) {
		if (ws1[i] < ws2[i])
			return -1;
		else if (ws1[i] > ws2[i])
			return 1;
	}

	return (ws1[i] - ws2[i]);
}
