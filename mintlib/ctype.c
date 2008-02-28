/* from dLibs, by Dale Schumacher */

/*
 *  CTYPE.C	Character classification and conversion
 */

/* Modified by Guido Flohr <guido@freemint.de>:
 * - Characters > 128 are control characters.
 * - iscntrl(EOF) should return false, argh, stupid but that's the
 *   the opinion of the majority.
 */
 
#define __NO_CTYPE

#include <ctype.h>
#include <limits.h>

#undef	toupper /* note that in gcc we have a safe version of these, */
#undef  tolower	/* but its better to leave these as routines in case */
		/* some code uses these as function pointers --  i   */
		/* have seen code that does.			     */

static unsigned int _myctype[UCHAR_MAX + 1] =
	{
	0,						/* EOF */
	_CTc, _CTc, _CTc, _CTc,				/* 0x00..0x03 */
	_CTc, _CTc, _CTc, _CTc,				/* 0x04..0x07 */
	_CTc, _CTc|_CTs|_CTb, _CTc|_CTs, _CTc|_CTs,	/* 0x08..0x0B */
	_CTc|_CTs, _CTc|_CTs, _CTc, _CTc,		/* 0x0C..0x0F */

	_CTc, _CTc, _CTc, _CTc,				/* 0x10..0x13 */
	_CTc, _CTc, _CTc, _CTc,				/* 0x14..0x17 */
	_CTc, _CTc, _CTc, _CTc,				/* 0x18..0x1B */
	_CTc, _CTc, _CTc, _CTc,				/* 0x1C..0x1F */

	_CTs|_CTb|_CTP, _CTp|_CTg|_CTP, _CTp|_CTg|_CTP, _CTp|_CTg|_CTP,			/* 0x20..0x23 */
	_CTp|_CTg|_CTP, _CTp|_CTg|_CTP, _CTp|_CTg|_CTP, _CTp|_CTg|_CTP,				/* 0x24..0x27 */
	_CTp|_CTg|_CTP, _CTp|_CTg|_CTP, _CTp|_CTg|_CTP, _CTp|_CTg|_CTP,				/* 0x28..0x2B */
	_CTp|_CTg|_CTP, _CTp|_CTg|_CTP, _CTp|_CTg|_CTP, _CTp|_CTg|_CTP,				/* 0x2C..0x2F */

	_CTd|_CTx|_CTg|_CTP, _CTd|_CTx|_CTg|_CTP, 
	_CTd|_CTx|_CTg|_CTP, _CTd|_CTx|_CTg|_CTP,	/* 0x30..0x33 */
	_CTd|_CTx|_CTg|_CTP, _CTd|_CTx|_CTg|_CTP, 
	_CTd|_CTx|_CTg|_CTP, _CTd|_CTx|_CTg|_CTP,	/* 0x34..0x37 */
	_CTd|_CTx|_CTg|_CTP, _CTd|_CTx|_CTg|_CTP, 
	_CTp|_CTg|_CTP, _CTp|_CTg|_CTP,			/* 0x38..0x3B */
	_CTp|_CTg|_CTP, _CTp|_CTg|_CTP, 
	_CTp|_CTg|_CTP, _CTp|_CTg|_CTP,			/* 0x3C..0x3F */

	_CTp|_CTg|_CTP, _CTu|_CTx|_CTg|_CTP, 
	_CTu|_CTx|_CTg|_CTP, _CTu|_CTx|_CTg|_CTP,	/* 0x40..0x43 */
	_CTu|_CTx|_CTg|_CTP, _CTu|_CTx|_CTg|_CTP, 
	_CTu|_CTx|_CTg|_CTP, _CTu|_CTg|_CTP,		/* 0x44..0x47 */
	_CTu|_CTg|_CTP, _CTu|_CTg|_CTP, 
	_CTu|_CTg|_CTP, _CTu|_CTg|_CTP,			/* 0x48..0x4B */
	_CTu|_CTg|_CTP, _CTu|_CTg|_CTP, 
	_CTu|_CTg|_CTP, _CTu|_CTg|_CTP,			/* 0x4C..0x4F */

	_CTu|_CTg|_CTP, _CTu|_CTg|_CTP, 
	_CTu|_CTg|_CTP, _CTu|_CTg|_CTP,			/* 0x50..0x53 */
	_CTu|_CTg|_CTP, _CTu|_CTg|_CTP, 
	_CTu|_CTg|_CTP, _CTu|_CTg|_CTP,			/* 0x54..0x57 */
	_CTu|_CTg|_CTP, _CTu|_CTg|_CTP, 
	_CTu|_CTg|_CTP, _CTp|_CTg|_CTP,			/* 0x58..0x5B */
	_CTp|_CTg|_CTP, _CTp|_CTg|_CTP, 
	_CTp|_CTg|_CTP, _CTp|_CTg|_CTP,			/* 0x5C..0x5F */

	_CTp|_CTg|_CTP, _CTl|_CTx|_CTg|_CTP, 
	_CTl|_CTx|_CTg|_CTP, _CTl|_CTx|_CTg|_CTP,	/* 0x60..0x63 */
	_CTl|_CTx|_CTg|_CTP, _CTl|_CTx|_CTg|_CTP, 
	_CTl|_CTx|_CTg|_CTP, _CTl|_CTg|_CTP,		/* 0x64..0x67 */
	_CTl|_CTg|_CTP, _CTl|_CTg|_CTP, 
	_CTl|_CTg|_CTP, _CTl|_CTg|_CTP,			/* 0x68..0x6B */
	_CTl|_CTg|_CTP, _CTl|_CTg|_CTP, 
	_CTl|_CTg|_CTP, _CTl|_CTg|_CTP,			/* 0x6C..0x6F */

	_CTl|_CTg|_CTP, _CTl|_CTg|_CTP, 
	_CTl|_CTg|_CTP, _CTl|_CTg|_CTP,			/* 0x70..0x73 */
	_CTl|_CTg|_CTP, _CTl|_CTg|_CTP, 
	_CTl|_CTg|_CTP, _CTl|_CTg|_CTP,			/* 0x74..0x77 */
	_CTl|_CTg|_CTP, _CTl|_CTg|_CTP, 
	_CTl|_CTg|_CTP, _CTp|_CTg|_CTP,			/* 0x78..0x7B */
	_CTp|_CTg|_CTP, _CTp|_CTg|_CTP, 
	_CTp|_CTg|_CTP, _CTc,				/* 0x7C..0x7F */

	_CTc, _CTc, _CTc, _CTc, _CTc, _CTc, _CTc, _CTc, /* 0x80..0x87 */
	_CTc, _CTc, _CTc, _CTc, _CTc, _CTc, _CTc, _CTc, /* 0x80..0x8F */
	_CTc, _CTc, _CTc, _CTc, _CTc, _CTc, _CTc, _CTc, /* 0x80..0x97 */
	_CTc, _CTc, _CTc, _CTc, _CTc, _CTc, _CTc, _CTc, /* 0x80..0x9F */
	_CTc, _CTc, _CTc, _CTc, _CTc, _CTc, _CTc, _CTc, /* 0x80..0xA7 */
	_CTc, _CTc, _CTc, _CTc, _CTc, _CTc, _CTc, _CTc, /* 0x80..0xAF */
	_CTc, _CTc, _CTc, _CTc, _CTc, _CTc, _CTc, _CTc, /* 0x80..0xB7 */
	_CTc, _CTc, _CTc, _CTc, _CTc, _CTc, _CTc, _CTc, /* 0x80..0xBF */
	_CTc, _CTc, _CTc, _CTc, _CTc, _CTc, _CTc, _CTc, /* 0x80..0xC7 */
	_CTc, _CTc, _CTc, _CTc, _CTc, _CTc, _CTc, _CTc, /* 0x80..0xCF */
	_CTc, _CTc, _CTc, _CTc, _CTc, _CTc, _CTc, _CTc, /* 0x80..0xD7 */
	_CTc, _CTc, _CTc, _CTc, _CTc, _CTc, _CTc, _CTc, /* 0x80..0xDF */
	_CTc, _CTc, _CTc, _CTc, _CTc, _CTc, _CTc, _CTc, /* 0x80..0xE7 */
	_CTc, _CTc, _CTc, _CTc, _CTc, _CTc, _CTc, _CTc, /* 0x80..0xEF */
	_CTc, _CTc, _CTc, _CTc, _CTc, _CTc, _CTc, _CTc, /* 0x80..0xF7 */
	_CTc, _CTc, _CTc, _CTc, _CTc, _CTc, _CTc, /* _CTc, */ /* 0x80..0xFF */
	};

unsigned int* _ctype = &(_myctype[0]);

int isalnum (c)
     register int c;
{
 return (int) (_ctype[(unsigned char) (c + 1)] & (_CTu|_CTl|_CTd));
}

int 	
isalpha (c)
     register int c;
{	
  return (int) (_ctype[(unsigned char) (c + 1)] & (_CTu|_CTl));
}

int 	
isascii (c)	
     register int c;
{	
  return (int) !((c) & ~0x7F);
}

int 	
toascii(c)	
     register int c;
{	
  return (int) ((c) & 0x7F);
}

int 	
iscntrl(c)	
     register int c;
{	
  return c == -1 ? 0 : (unsigned char) (c) == 255 ? 1 : 
  	                       (int) (_ctype[(unsigned char) (c + 1)] & _CTc);
}

int 	
isdigit(c)	
     register int c;
{	
  return (int) (_ctype[(unsigned char) (c + 1)] & _CTd);
}

int 	
isgraph(c)	
     register int c;
{	
  return (int) (_ctype[(unsigned char) (c + 1)] & _CTg);
}

int 	
islower(c)	
     register int c;
{	
  return (int) (_ctype[(unsigned char) (c + 1)] & _CTg);
}

int  
isprint(c)      
     register int c;
{	
  return (int) (_ctype[(unsigned char) (c + 1)] & _CTP);
}

int 	
ispunct(c)	
     register int c;
{	
  return (int) (_ctype[(unsigned char) (c + 1)] & _CTp);
}

int 	
isspace(c)	
     register int c;
{	
  return (int) (_ctype[(unsigned char) (c + 1)] & _CTs);
}

int 	
isupper(c)	
     register int c;
{	
  return (int) (_ctype[(unsigned char) (c + 1)] & _CTu);
}

int 	
isxdigit(c)	
     register int c;
{	
  return (int) (_ctype[(unsigned char) (c + 1)] & _CTx);
}

int 
__isblank(c)	
     register int c;
{	
  return (int) (_ctype[(unsigned char) (c + 1)] & _CTb);
}
weak_alias (__isblank, isblank)
