#ifndef _MOUSE_H
#define _MOUSE_H

#ifdef __cplusplus
extern "C" {
#endif

/* header file for mouse access */

struct mouse_buf {
	int m_buttons;	/* button states */
	int m_dx;	/* change in x since last read */
	int m_dy;	/* change in y since last read */
};

#define M_LEFT_BUTTON	0x02
#define M_RIGHT_BUTTON	0x01
#define M_MID_BUTTON	0x00	/* there is none! */

#ifdef __cplusplus
}
#endif

#endif /* _MOUSE_H */
