#ifndef _WIDGET_H
#define _WIDGET_H

#ifndef _COMPILER_H
#include <compiler.h>
#endif

/*****************************************************************************
 *  FILE:		widget.h
 *  DATE:		August 1988.
 *  AUTHOR:		Richard A. Culshaw.
 *  DESCRIPTION:	Contains the definitions of the widget structures.
 *			It should be included by all programs that want to
 *			use the widget library.
 * DISCLAIMER:		This file is deemed to be public-domain, on the simple
 *			provisos that this section remains in this file and
 *			that code using it do not do so for monetary gain.
 *			Neither the author, nor the authors employees at the
 *			time of developing this code, accept any liability or
 *			responsibility for the use, abuse or misuse of this
 *			code.
 *****************************************************************************/

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <curses.h>

#ifdef __cplusplus
extern "C" {
#endif

/* definition for command widget entry in linked list */
struct    cmdwid{
    		WINDOW		*widget;
    		int		id;
    		char		msg[100];
    		char		acpt;
    		int		(*func)();
    		int		length;	
    		int		x,y;
		int		active;
    		struct cmdwid	*next;
    	} *cmdlist;

/* definition for label widget entry in linked list */
struct    lblwid{
    		WINDOW		*widget;
    		int		id;
    		char		msg[100];
    		char		pos;
    		int		length;	
		int		difference;
    		int		x,y;
    		struct lblwid	*next;
    	} *lbllist;

/* definition for togle widget entry in linked list */
struct     tglwid{
    		WINDOW		*widget;
    		int		id;
    		char		msg[100];
    		char		tgl[10][20];
    		char		toggle;
    		int		cur;
	 	int 		total;
    		int		length;
    		int 		xtgl;
    		int		x,y;
		int		active;
    		struct tglwid	*next;
    	} *tgllist;

/* definition for input widget entry in linked list */
struct inpwid{
    		WINDOW		*widget;
    		int 		id;
		char		msg[100];
    		char		acpt;
    		char		*input;
		int		sofi;
		int		exec;
    		int		lofs;
    		int		length;
    		int		x,y;
		int		active;
    		struct inpwid	*next;
    	} *inplist;
    
/* linked list of characters used for activating widgets */	
struct chentry {
    		char		  ch;
    		int	 	  type;
    		int		  id;
		struct chentry    *next;
    	} *actlist;

/* null entries in the various linked list */
#define NULLCMD		(struct cmdwid *)NULL
#define NULLLBL 	(struct lblwid *)NULL
#define NULLTGL 	(struct tglwid *)NULL
#define NULLINP 	(struct inpwid *)NULL
#define NULLCH 		(struct chentry *)NULL

/* part of the specifications for label widgets */
#define CENTRE		1
#define	LEFTJUST	2
#define RIGHTJUST	4
#define NOHIGH		8

/* the types of the widgets */
#define CMD		1
#define TGL		2
#define LBL		3
#define INP		4

#define BLANK		1
#define NOBLANK		0

#define NULLWIDGET	0

#define EXEC		1
#define NOEXEC		0

#define VERTICAL	1
#define HORIZONTAL	2

typedef int WIDGET;
typedef int WIDGETTYPE;

__EXTERN int activate __PROTO((WIDGET));
__EXTERN int addtochlist __PROTO((int, int, WIDGETTYPE));

__EXTERN void boxwidget __PROTO((WINDOW *, int));

__EXTERN int chactive __PROTO((WIDGET, int, int));
__EXTERN int changelblwidget __PROTO((WIDGET, char *, int));
__EXTERN void cleartextwindow __PROTO((void));

__EXTERN int deactivate __PROTO((WIDGET, int));
__EXTERN int dehighlight __PROTO((WIDGET));
__EXTERN void deletechentry __PROTO((int));
__EXTERN void drawcmdwidget __PROTO((WINDOW *, char *, int, int, int));
__EXTERN void drawinpwidget __PROTO((WINDOW *, char *, int, int, int, int));
__EXTERN void drawlblwidget __PROTO((WINDOW *, char *, int, int, int, int));
__EXTERN void drawtextwindow __PROTO((int));
__EXTERN void drawtglwidget __PROTO((WINDOW *, char *, char *, int, int, int));

__EXTERN void endwidgets __PROTO((void));

__EXTERN int getinput __PROTO((WIDGET));

__EXTERN int highlight __PROTO((WIDGET));
__EXTERN void home __PROTO((void));

__EXTERN void initialisewidgets __PROTO((void));

__EXTERN void killcmdwidget __PROTO((WIDGET));
__EXTERN void killinpwidget __PROTO((WIDGET));
__EXTERN void killlblwidget __PROTO((WIDGET));
__EXTERN void killtextwindow __PROTO((void));
__EXTERN void killtglwidget __PROTO((WIDGET));
__EXTERN int killwidget __PROTO((WIDGET));

__EXTERN int light __PROTO((WIDGET, int));

__EXTERN WIDGET mkcmdwidget __PROTO((char *, int, int (*)(), int));
__EXTERN WIDGET mkinpwidget __PROTO((char *, int, char *, int, int, int, int));
__EXTERN WIDGET mklblwidget __PROTO((char *, int, int, int));
__EXTERN WIDGET mktglwidget __PROTO((char *, int, char **, int, int));

__EXTERN int opentextwindow __PROTO((int, int));

__EXTERN void report __PROTO((char *));

__EXTERN void screenrefresh __PROTO((void));

__EXTERN void togglewidget __PROTO((WIDGET));
__EXTERN int tsttglwidget __PROTO((WIDGET));

__EXTERN WIDGET widgetinput __PROTO((void));
__EXTERN WIDGETTYPE  widgettype __PROTO((WIDGET));

#ifdef __cplusplus
}
#endif

#endif /* _WIDGET_H */
