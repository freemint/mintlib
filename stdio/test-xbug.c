#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Modified by Guido Flohr <guido@freemint.de>:
   - Find cat in $PATH and not only in /bin.  */
char* catname = NULL;
#define DEFAULT_CAT "/bin/cat"
extern char* _buffindfile (const char* fname, char* fpath,
                           char* const *fext, char buf[]);
#include <limits.h>
char buf[PATH_MAX];

typedef struct _Buffer {
  char *buff;
  int  room, used;
} Buffer;

#if __STDC__ - 0
void InitBuffer (Buffer *b);
void AppendToBuffer (register Buffer *b, const char *str, register int len);
void ReadFile (register Buffer *buffer, FILE *input);
#endif

#define INIT_BUFFER_SIZE 10000

void InitBuffer(b)
     Buffer *b;
{
  b->room = INIT_BUFFER_SIZE;
  b->used = 0;
  b->buff = (char *)malloc(INIT_BUFFER_SIZE*sizeof(char));
}

void AppendToBuffer(b, str, len)
     register Buffer *b;
     const char *str;
     register int len;
{
  while (b->used + len > b->room) {
    b->buff = (char *)realloc(b->buff, 2*b->room*(sizeof(char)));
    b->room *= 2;
  }
  strncpy(b->buff + b->used, str, len);
  b->used += len;
}

void ReadFile(buffer, input)
     register Buffer *buffer;
     FILE *input;
{
  char       buf[BUFSIZ + 1];
  register int        bytes;

  buffer->used = 0;
  while (!feof(input) && (bytes = fread(buf, 1, BUFSIZ, input)) > 0) {
    AppendToBuffer(buffer, buf, bytes);
  }
  AppendToBuffer(buffer, "", 1);
}

int
main(int argc, char *argv[])
{
  char filename[] = "test-xbug.c";
  FILE *input;
  Buffer buffer;
  char* path;
  
  InitBuffer(&buffer);

  if (!freopen (filename, "r", stdin))
    fprintf(stderr, "cannot open file\n");

  unsetenv ("LD_LIBRARY_PATH");

  /* Find a cat binary.  */
  if ((path = getenv ("PATH")) != NULL)
      catname = _buffindfile ("cat", path, NULL, buf);

  if (catname == NULL)
    catname = DEFAULT_CAT;
  else
    /* Arrrrgh, ...  */
    {
      char* ptr = catname;
      while (*ptr != '\0')
        {
          if (*ptr == '\\')
            *ptr = '/';
          ptr++;
        }
    }
  
  if (!(input = popen(catname, "r")))
    fprintf(stderr, "cannot run %s\n", catname);

  ReadFile(&buffer, input);
  pclose(input);

  return 0;
}
