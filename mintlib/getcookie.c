/*
 * Getcookie for MiNTlib
 * 
 * Author: jerry g geiger
 * 
 * - Ssystem extension Draco
 * - corrected by Frank Naumann, 1998-09-09
 * 
 * returns:
 * 
 * 	- 0 if cookie was found
 * 	- EERROR if cookie is missing
 * 	
 * 	if p_value is set, cookie value is copied to *p_value
 * 
 */

#include <mintbind.h>
#ifdef __TURBOC__
# include <mint/ssystem.h>
#else
# include <mint/ssystem.h>
#endif
#include <errno.h> 
#include <sysvars.h>

extern int __has_no_ssystem;

int
Getcookie (long cookie, long *p_value)
{
	if (__has_no_ssystem)
	{
		/* old method */
		long *cookieptr = (long*) get_sysvar(_p_cookies);
		
		if (cookieptr)
		{
			while (*cookieptr)
			{
				if (*cookieptr == cookie)
				{
					if (p_value)
						*p_value = cookieptr [1];
					
					return 0;
				}
				
				cookieptr += 2;
			}
		}
		if (p_value)
			*p_value = 0;
		return EERROR;
	}
	else
	{
		/* Ssystem supported, use it */
		int	r;
		long	v = -42;

		/* Make sure that P_VALUE is zeroed if the cookie can't
		   be found.  Reported by Tommy Andersen
		   (tommya@post3.tele.dk).  */
		if (p_value)
			*p_value = 0;
			
		r = Ssystem(S_GETCOOKIE, cookie, &v);
		/*
		 * Backward compatibility for MiNT 1.14.7:
		 * Ssystems() returns cookie value and ignores arg2!!
		 */
		if (r != -1 && v == -42)				
			v = r;
 
		if (r == -1)							/* not found */
		{
			v = 0;
			r = EERROR;
		}
		else
			r = 0;
		if (p_value)
			*p_value = v;
		return r;
	}
}
