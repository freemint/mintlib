#include <stdio.h>
#include <stdlib.h>

int
main (int argc, char *argv[])
{
  int n = -1;
  int n1 = -5;
  char c = '!';
  char c1 = '?';
  int ret;
  int failures = 0;
  
  ret = sscanf ("0x", "%i%c", &n, &c);
  printf ("ret: %d, n: %d, c: %c\n", ret, n, c);
  if (ret != 2 || n != 0 || c != 'x')
    failures++;
  
  c = '!';  
  ret = sscanf ("0Xy", "%i%c%c", &n, &c, &c1);
  printf ("ret: %d, n: %d, c: %c, c1: %c\n", ret, n, c, c1);
  if (ret != 3 || n != 0 || c != 'X' || c1 != 'y')
    failures++;
  
  c = '!';
  n = -1;
  ret = sscanf ("0x15", "%d%c", &n, &c);
  printf ("ret: %d, n: %d, c: %c\n", ret, n, c);
  if (ret != 2 || n != 0 || c != 'x')
    failures++;
    
  c = '!';
  n = -1;
  ret = sscanf ("0X15", "%o%c", &n, &c);
  printf ("ret: %d, n: %d, c: %c\n", ret, n, c);
  if (ret != 2 || n != 0 || c != 'X')
    failures++;

  c = '!';
  n = -1;
  ret = sscanf ("0x15x", "%x%c", &n, &c);
  printf ("ret: %d, n: 0x%x, c: %c\n", ret, (unsigned) n, c);
  if (ret != 2 || n != 0x15 || c != 'x')
    failures++;

  c = '!';
  c1 = '?';
  n = -1;
  ret = sscanf ("0xy5", "%x%c", &n, &c, &n1);
  printf ("ret: %d, n: %d, c: %c, c1: %c, n1: %d\n", ret, n, c, c1, n1);
  if (ret != 0 || n != -1 || c != '!' || c1 != '?' || n1 != -5)
    failures++;

  c = '!';
  c1 = '?';
  n = -1;
  n1 = -5;
  ret = sscanf ("0xy5", "%i%c%c%d", &n, &c, &c1, &n1);
  printf ("ret: %d, n: %d, c: %c, c1: %c, n1: %d\n", ret, n, c, c1, n1);
  if (ret != 4 || n != 0 || c != 'x' || c1 != 'y' || n1 != 5)
    failures++;

  return failures;
}
