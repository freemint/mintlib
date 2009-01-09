#ifndef _WCHAR_H
#define _WCHAR_H

/* Get size_t, wchar_t, wint_t and NULL from <stddef.h>.  */
#define __need_size_t
#define __need_wchar_t
#define __need_NULL
#define __need_wint_t
#include <stddef.h>

#ifndef WEOF
# define WEOF (0xffffffffu)
#endif

#endif /* _WCHAR_H */
