/*
 * Include File vt52.h
 *
 * erstellt 26.03.86 von Th. Weinstein
 * ermoeglicht VT52 Escapesequenzen in C Programmen zu verwenden.
 *
 * Verwendung:
 *       printf( HOME ); fflush(stdout);
 * setzt z.B. den Cursor ganz oben in die linke Ecke.
 *       printf( CURS_LOC, 32+12, 32+10 ); fflush(stdout);
 * setzt den Cursor in die 12. Zeile und 10. Spalte.
 *
 * 29.04.90
 * translated to english by F. Ridderbusch
 * enables the usage of VT52 escape sequences in C programms.
 *
 * Usage:
 *	printf( HOME ); fflush(stdout);
 * moves the cursor to the upper left corner.
 *       printf( CURS_LOC, 32+12, 32+10 ); fflush(stdout);
 * moves the cursor to line 12 and column 10.
 *
 */

#ifndef _VT52_H
#define _VT52_H

#define C_UP            "\033A"       /* cursor one line up               */
#define C_DOWN          "\033B"       /*   "     "    "  down		  */
#define C_RIGHT         "\033C"       /*   "     "  column right	  */
#define C_LEFT          "\033D"       /*   "     "     "   left		  */
#define CLEAR_HOME      "\033E"       /* clear screen, cursor home	  */
#define HOME            "\033H"       /* cursor home                      */
#define SCROLL_UP       "\033I"       /* cursor one line up; when already */
				      /* in first line, the entire screen */
                                      /* is scrolled			  */
#define CLEAR_DOWN      "\033J"       /* clear screen from cursor position*/
                                      /* to end of screen		  */
#define DEL_EOL         "\033K"       /* clear screen until end of line   */
#define INS_LINE        "\033L"       /* insert line			  */
#define DEL_LINE        "\033M"       /* delete line			  */
#define CURS_LOC        "\033Y%c%c"   /* set cursor to position x, y	  */
#define CHAR_COLOR      "\033b%c"     /* select the character color       */
                                      /* Monochrom white= '0', black='1'  */
                                      /* Color 'A' to 'F' depends on      */
                                      /* Resolution			  */
#define BG_COLOR        "\033c%c"     /* as above for back ground color   */
#define DEL_BOP		"\033d"	      /* erase to start of page inc. cur  */
#define C_ON            "\033e"       /* switch cursor on		  */
#define C_OFF           "\033f"       /* switch cursor off		  */
#define C_SAVE          "\033j"       /* store cursor position		  */
#define C_RESTORE       "\033k"       /* restore cursor position	  */
#define ERASE_L         "\033l"       /* erase cursor line		  */
#define DEL_BOL         "\033o"       /* erase to beginning of line       */
#define REV_ON          "\033p"       /* inverse on			  */
#define REV_OFF         "\033q"       /* inverse off			  */
#define WRAP_ON         "\033v"       /* automatic line wrap on		  */
#define WRAP_OFF        "\033w"       /* automatic line wrap off	  */

#endif /* _VT_52_H */
