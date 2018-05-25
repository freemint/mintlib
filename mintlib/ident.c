#include <features.h>

char __Ident_gnulib[] = "$Version: MiNTLib "
#if defined(__mc68020__) || defined(__mc68030__) || defined(__mc68040__) || defined(__mc68060__)
"-m68020-60 "
#endif
#ifdef __mcoldfire__
"-mcpu=5475 "
#endif
#ifdef __M68881__
"-m68881 "
#endif
#ifdef __MSHORT__
"-mshort "
#endif
VERSION" $";
