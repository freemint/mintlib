#include <crypt.h>
#include <string.h>
#include <stdio.h>

int
main (int argc, char *argv[])
{
  const char salt[] = "$1$saltstring";
  char *cp;
  int result = 0;

  cp = crypt ("Hello world!", salt);
  result |= strcmp ("$1$saltstri$YMyguxXMBpd2TEZ.vS/3q1", cp);

  if (result != 0) {
  	fprintf (stderr, "md5-test failed (got: %s)!\n", cp);
  } else {
  	printf ("md5-test successful!\n");
  }
  
  return result;
}
