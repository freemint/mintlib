/* This test comes from ISO C Corrigendum 1.  */
#include <stdio.h>

int
main (int argc, char *argv[])
{
  int d1, n1, n2, i;
# define NOISE 1234567
  int d2 = NOISE;

  i = sscanf ("123", "%d%n%n%d", &d1, &n1, &n2, &d2);

#ifdef NO_BUG_IN_ISO_C_CORRIGENDUM_1
  return i != 3 || d1 != 123 || n1 != 3 || n2 != 3 || d2 != NOISE;
#else
  return i != 1 || d1 != 123 || n1 != 3 || n2 != 3 || d2 != NOISE;
#endif
}
