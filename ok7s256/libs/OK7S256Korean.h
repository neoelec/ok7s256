/***********************************************************************************/
/*       OK7S256Korean.h : Korean Language Display on 128x64 GLCD Module           */
/***********************************************************************************/

#ifndef __OK7S256KOREAN_H__
#define __OK7S256KOREAN_H__

extern const unsigned char E_font[128][16];
extern const unsigned char K_font[360][32];

extern unsigned int xcharacter, ycharacter;    // x character(0-3), y character(0-15)
extern unsigned int xcursor, ycursor;          // x and y cursor position(0-3, 0-15)
extern unsigned int cursor_flag;

/* ------------------------------------------------------------------------------- */
/*    Write a Command                                                              */
/* ------------------------------------------------------------------------------- */
extern void GLCD_command(unsigned int cs, unsigned int command);

/* ------------------------------------------------------------------------------- */
/*    Write a DD RAM Data                                                          */
/* ------------------------------------------------------------------------------- */
extern void GLCD_data(unsigned int cs, unsigned int data);

/* ------------------------------------------------------------------------------- */
/*    Clear GLCD Screen                                                            */
/* ------------------------------------------------------------------------------- */
extern void GLCD_clear(void);

/* ------------------------------------------------------------------------------- */
/*    Set English Character Position                                               */
/* ------------------------------------------------------------------------------- */
extern void GLCD_xy(unsigned int x, unsigned int y);

/* ------------------------------------------------------------------------------- */
/*    Set Character Upper/Lower Row                                                */
/* ------------------------------------------------------------------------------- */
extern void GLCD_xy_row(unsigned int x, unsigned int y, unsigned int row);

/* ------------------------------------------------------------------------------- */
/*    Display a 8x16 Dot English(ASCII)                                            */
/* ------------------------------------------------------------------------------- */
extern void GLCD_English(unsigned int attribute, unsigned char Ecode);

/* ------------------------------------------------------------------------------- */
/*    Display a 16x16 Dot Korean                                                   */
/* ------------------------------------------------------------------------------- */
extern void GLCD_Korean(unsigned int attribute, unsigned int Kcode);

/* ------------------------------------------------------------------------------- */
/*   Display a String(attribute : 0x00=normal, 0x01 = reverse, 0x02 = underline)   */
/* ------------------------------------------------------------------------------- */
extern void GLCD_string(unsigned int x, unsigned int y, unsigned int attribute, char *string);

#endif /* __OK7S256KOREAN_H__ */
