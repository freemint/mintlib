/* Atari ST keyboard key bindings */

#ifndef _KEYCODES_H
#define _KEYCODES_H

#ifdef __cplusplus
extern "C" {
#endif

#define N_KEYCODES	0x82	/* key scan codes go from 0 to this - 1*/

/* some noteworthy keys */

#define K_ESC		0x01
#define K_RET		0x1c

/* function keys */
#define F_1		0x3b
#define F_2		0x3c
#define F_3		0x3d
#define F_4		0x3e
#define F_5		0x3f
#define F_6		0x40
#define F_7		0x41
#define F_8		0x42
#define F_9		0x43
#define F_10		0x44
/* shifted function keys */
#define SHF_1		0x54
#define SHF_2		0x55
#define SHF_3		0x56
#define SHF_4		0x57
#define SHF_5		0x58
#define SHF_6		0x59
#define SHF_7		0x5a
#define SHF_8		0x5b
#define SHF_9		0x5c
#define SHF_10		0x5d

#define K_INS		0x52
#define K_DEL		0x53
#define K_HOME		0x47
#define K_UNDO		0x61
#define K_HELP		0x62
#define CURS_UP		0x48
#define CURS_DN		0x50
#define CURS_RT		0x4d
#define CURS_LF		0x4b

#define KP_MINUS	0x4a
#define KP_PLUS		0x4e
#define KP_LP		0x63
#define KP_RP		0x64
#define KP_SLASH	0x65
#define KP_STAR		0x66
#define KP_7		0x67
#define KP_8		0x68
#define KP_9		0x69
#define KP_4		0x6a
#define KP_5		0x6b
#define KP_6		0x6c
#define KP_1		0x6d
#define KP_2		0x6e
#define KP_3		0x6f
#define KP_0		0x70
#define KP_DOT		0x71
#define KP_ENTER	0x72

#define ALT_1		0x78
#define ALT_2		0x79
#define ALT_3		0x7a
#define ALT_4		0x7b
#define ALT_5		0x7c
#define ALT_6		0x7d
#define ALT_7		0x7e
#define ALT_8		0x7f
#define ALT_9		0x80
#define ALT_0		0x81

#ifndef _COMPILER_H
#include <compiler.h>
#endif

__EXTERN unsigned int console_read_byte __PROTO((int handle));
__EXTERN int console_input_status __PROTO((int handle));
__EXTERN void console_write_byte __PROTO((int handle, int n));
__EXTERN void console_set_key __PROTO((int keycode, char *regular, char *shifted, char *alted));

#if defined(__cplusplus)
}
#endif

#endif /* _KEYCODES_H */
