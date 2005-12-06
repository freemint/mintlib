#include <stdio.h>
#include <unistd.h>

/* Imitate old definitions.  */
typedef	struct			/* Old FILE structure */
{
	long		_cnt;		/* # of bytes in buffer */
	unsigned char	*_ptr;		/* current buffer pointer */
	unsigned char	*_base;		/* base of file buffer */
	unsigned int	_flag;		/* file status flags */
	int		_file;		/* file handle */
	long		_bsiz;		/* buffer size */
	unsigned char	_ch;		/* tiny buffer, for "unbuffered" i/o */
} OLDFILE;

extern OLDFILE _iob[];
extern int _filbuf (OLDFILE *);

#define _IOBIN 0x4
#define oldstdin (&_iob[0])
#define oldstdout (&_iob[1])
#define oldstderr (&_iob[2])
#define oldgetc(__fp) \
({   int __c; \
     OLDFILE* __lfp = (OLDFILE*) (__fp); \
    do { \
	__c = (--__lfp->_cnt >= 0) ? ((int)*__lfp->_ptr++) : _filbuf(__lfp); \
    } while ((!(__lfp->_flag & _IOBIN)) && (__c == '\r')); \
    __c; \
})

#define oldfileno(s) ((s)->_file)

int
main (int argc, char* argv[])
{
	int c;
	int status = 0;
	
	if (oldfileno (oldstdin) != STDIN_FILENO) {
		fflush (stdout);
		fprintf (stderr, "*** error: oldfileno (stdin): %d\n", 
			 oldfileno (oldstdin));
		status = 1;
	}
	
	if (oldfileno (oldstdout) != STDOUT_FILENO) {
		fflush (stdout);
		fprintf (stderr, "*** error: oldfileno (stdout): %d\n", 
			 oldfileno (oldstdout));
		status = 1;
	}
	
	if (oldfileno (oldstderr) != STDERR_FILENO) {
		fflush (stdout);
		fprintf (stderr, "*** error: oldfileno (stderr): %d\n", 
			 oldfileno (oldstderr));
		status = 1;
	}
	
	fputs ("This must go to stdout.\n", (FILE*) oldstdout);
	fputs ("In case you're a human being: Type something and press CTRL-D!\n",
		stdout);

	while ((c = oldgetc (oldstdin)) != EOF)
		fputc (c, stdout);

	return status;
}
