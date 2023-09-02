/***********************************************************************************/
/*    OK7S256GLCD.h : English(ASCII) and Graphic Display on 128x64 GLCD Module     */
/***********************************************************************************/

#ifndef __OK7S256GLCD_H__
#define __OK7S256GLCD_H__

extern const unsigned char font[95][5];

extern unsigned int xcharacter, ycharacter;    // x character(0-7), y character(0-19)
extern unsigned int xcursor, ycursor;          // x and y cursor position(0-7, 0-19)
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
/*    Set English(ASCII) Character Position                                        */
/* ------------------------------------------------------------------------------- */
extern void GLCD_xy(unsigned int x, unsigned int y);

/* ------------------------------------------------------------------------------- */
/*    Display a 6x8 Dot English(ASCII)                                             */
/* ------------------------------------------------------------------------------- */
extern void GLCD_English(unsigned int attribute, unsigned char character);

/* ------------------------------------------------------------------------------- */
/*    Display a String(attribute : 0x00 = normal, 0x01 = reverse)                    */
/* ------------------------------------------------------------------------------- */
extern void GLCD_string(unsigned int x, unsigned int y, unsigned int attribute, char *string);

/* ------------------------------------------------------------------------------- */
/*    Graphic Functions on GLCD Module                                             */
/* ------------------------------------------------------------------------------- */

extern unsigned char screen[8][128];

extern void Axis_xy(unsigned int x, unsigned int y);  /* set x, y axis position */
extern void Draw(void);                        /* draw screen with buffer data */
extern void Clear_screen(void);                /* clear buffer and GLCD screen */
extern void Dot(unsigned int xx, unsigned int y); /* draw a dot on GLCD */
extern void Line(int xx1, int yy1, int xx2, int yy2); /* draw a straight line */
extern void Rectangle(int xx1, int yy1, int xx2, int yy2);  /* draw a rectangle */
extern void Circle(int xx1, int yy1, int r);   /* draw a circle */
extern void Sine(int peak);                    /* draw a sine curve */
extern void Cosine(int peak);                  /* draw a cosine curve */

#endif /* __OK7S256GLCD_H__ */
