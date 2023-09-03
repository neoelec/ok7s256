/***********************************************************************************/
/*    OK7S256GLCD.c : English(ASCII) and Graphic Display on 128x64 GLCD Module     */
/***********************************************************************************/

#include <board.h>

#include "OK7S256gcc.h"
#include "OK7S256GLCD.h"

/* ------------------------------------------------------------------------------- */
/*        6x8 Dot English(ASCII) Character Font                                    */
/* ------------------------------------------------------------------------------- */
const unsigned char font[95][5] = {            /* real 5x7 ASCII character font */
  { 0x00, 0x00, 0x00, 0x00, 0x00 },            // 0x20 space
  { 0x00, 0x00, 0x4f, 0x00, 0x00 },            // 0x21 !
  { 0x00, 0x07, 0x00, 0x07, 0x00 },            // 0x22 "
  { 0x14, 0x7f, 0x14, 0x7f, 0x14 },            // 0x23 #
  { 0x24, 0x2a, 0x7f, 0x2a, 0x12 },            // 0x24 $
  { 0x23, 0x13, 0x08, 0x64, 0x62 },            // 0x25 %
  { 0x36, 0x49, 0x55, 0x22, 0x50 },            // 0x26 &
  { 0x00, 0x05, 0x03, 0x00, 0x00 },            // 0x27 '
  { 0x00, 0x1c, 0x22, 0x41, 0x00 },            // 0x28 (
  { 0x00, 0x41, 0x22, 0x1c, 0x00 },            // 0x29 )
  { 0x14, 0x08, 0x3e, 0x08, 0x14 },            // 0x2a *
  { 0x08, 0x08, 0x3e, 0x08, 0x08 },            // 0x2b +
  { 0x00, 0x50, 0x30, 0x00, 0x00 },            // 0x2c ,
  { 0x08, 0x08, 0x08, 0x08, 0x08 },            // 0x2d -
  { 0x00, 0x60, 0x60, 0x00, 0x00 },            // 0x2e .
  { 0x20, 0x10, 0x08, 0x04, 0x02 },            // 0x2f /
  { 0x3e, 0x51, 0x49, 0x45, 0x3e },            // 0x30 0
  { 0x00, 0x42, 0x7f, 0x40, 0x00 },            // 0x31 1
  { 0x42, 0x61, 0x51, 0x49, 0x46 },            // 0x32 2
  { 0x21, 0x41, 0x45, 0x4b, 0x31 },            // 0x33 3
  { 0x18, 0x14, 0x12, 0x7f, 0x10 },            // 0x34 4
  { 0x27, 0x45, 0x45, 0x45, 0x39 },            // 0x35 5
  { 0x3c, 0x4a, 0x49, 0x49, 0x30 },            // 0x36 6
  { 0x01, 0x71, 0x09, 0x05, 0x03 },            // 0x37 7
  { 0x36, 0x49, 0x49, 0x49, 0x36 },            // 0x38 8
  { 0x06, 0x49, 0x49, 0x29, 0x1e },            // 0x39 9
  { 0x00, 0x36, 0x36, 0x00, 0x00 },            // 0x3a :
  { 0x00, 0x56, 0x36, 0x00, 0x00 },            // 0x3b ;
  { 0x08, 0x14, 0x22, 0x41, 0x00 },            // 0x3c <
  { 0x14, 0x14, 0x14, 0x14, 0x14 },            // 0x3d =
  { 0x00, 0x41, 0x22, 0x14, 0x08 },            // 0x3e >
  { 0x02, 0x01, 0x51, 0x09, 0x06 },            // 0x3f ?
  { 0x32, 0x49, 0x79, 0x41, 0x3e },            // 0x40 @
  { 0x7e, 0x11, 0x11, 0x11, 0x7e },            // 0x41 A
  { 0x7f, 0x49, 0x49, 0x49, 0x36 },            // 0x42 B
  { 0x3e, 0x41, 0x41, 0x41, 0x22 },            // 0x43 C
  { 0x7f, 0x41, 0x41, 0x22, 0x1c },            // 0x44 D
  { 0x7f, 0x49, 0x49, 0x49, 0x41 },            // 0x45 E
  { 0x7f, 0x09, 0x09, 0x09, 0x01 },            // 0x46 F
  { 0x3e, 0x41, 0x49, 0x49, 0x7a },            // 0x47 G
  { 0x7f, 0x08, 0x08, 0x08, 0x7f },            // 0x48 H
  { 0x00, 0x41, 0x7f, 0x41, 0x00 },            // 0x49 I
  { 0x20, 0x40, 0x41, 0x3f, 0x01 },            // 0x4a J
  { 0x7f, 0x08, 0x14, 0x22, 0x41 },            // 0x4b K
  { 0x7f, 0x40, 0x40, 0x40, 0x40 },            // 0x4c L
  { 0x7f, 0x02, 0x0c, 0x02, 0x7f },            // 0x4d M
  { 0x7f, 0x04, 0x08, 0x10, 0x7f },            // 0x4e N
  { 0x3e, 0x41, 0x41, 0x41, 0x3e },            // 0x4f O
  { 0x7f, 0x09, 0x09, 0x09, 0x06 },            // 0x50 P
  { 0x3e, 0x41, 0x51, 0x21, 0x5e },            // 0x51 Q
  { 0x7f, 0x09, 0x19, 0x29, 0x46 },            // 0x52 R
  { 0x26, 0x49, 0x49, 0x49, 0x32 },            // 0x53 S
  { 0x01, 0x01, 0x7f, 0x01, 0x01 },            // 0x54 T
  { 0x3f, 0x40, 0x40, 0x40, 0x3f },            // 0x55 U
  { 0x1f, 0x20, 0x40, 0x20, 0x1f },            // 0x56 V
  { 0x3f, 0x40, 0x38, 0x40, 0x3f },            // 0x57 W
  { 0x63, 0x14, 0x08, 0x14, 0x63 },            // 0x58 X
  { 0x07, 0x08, 0x70, 0x08, 0x07 },            // 0x59 Y
  { 0x61, 0x51, 0x49, 0x45, 0x43 },            // 0x5a Z
  { 0x00, 0x7f, 0x41, 0x41, 0x00 },            // 0x5b [
  { 0x02, 0x04, 0x08, 0x10, 0x20 },            // 0x5c (\)
  { 0x00, 0x41, 0x41, 0x7f, 0x00 },            // 0x5d ]
  { 0x04, 0x02, 0x01, 0x02, 0x04 },            // 0x5e ^
  { 0x40, 0x40, 0x40, 0x40, 0x40 },            // 0x5f _
  { 0x00, 0x01, 0x02, 0x04, 0x00 },            // 0x60 `
  { 0x20, 0x54, 0x54, 0x54, 0x78 },            // 0x61 a
  { 0x7f, 0x48, 0x44, 0x44, 0x38 },            // 0x62 b
  { 0x38, 0x44, 0x44, 0x44, 0x20 },            // 0x63 c
  { 0x38, 0x44, 0x44, 0x48, 0x7f },            // 0x64 d
  { 0x38, 0x54, 0x54, 0x54, 0x18 },            // 0x65 e
  { 0x08, 0x7e, 0x09, 0x01, 0x02 },            // 0x66 f
  { 0x0c, 0x52, 0x52, 0x52, 0x3e },            // 0x67 g
  { 0x7f, 0x08, 0x04, 0x04, 0x78 },            // 0x68 h
  { 0x00, 0x04, 0x7d, 0x00, 0x00 },            // 0x69 i
  { 0x20, 0x40, 0x44, 0x3d, 0x00 },            // 0x6a j
  { 0x7f, 0x10, 0x28, 0x44, 0x00 },            // 0x6b k
  { 0x00, 0x41, 0x7f, 0x40, 0x00 },            // 0x6c l
  { 0x7c, 0x04, 0x18, 0x04, 0x7c },            // 0x6d m
  { 0x7c, 0x08, 0x04, 0x04, 0x78 },            // 0x6e n
  { 0x38, 0x44, 0x44, 0x44, 0x38 },            // 0x6f o
  { 0x7c, 0x14, 0x14, 0x14, 0x08 },            // 0x70 p
  { 0x08, 0x14, 0x14, 0x18, 0x7c },            // 0x71 q
  { 0x7c, 0x08, 0x04, 0x04, 0x08 },            // 0x72 r
  { 0x48, 0x54, 0x54, 0x54, 0x20 },            // 0x73 s
  { 0x04, 0x3f, 0x44, 0x40, 0x20 },            // 0x74 t
  { 0x3c, 0x40, 0x40, 0x20, 0x7c },            // 0x75 u
  { 0x1c, 0x20, 0x40, 0x20, 0x1c },            // 0x76 v
  { 0x3c, 0x40, 0x30, 0x40, 0x3c },            // 0x77 w
  { 0x44, 0x28, 0x10, 0x28, 0x44 },            // 0x78 x
  { 0x0c, 0x50, 0x50, 0x50, 0x3c },            // 0x79 y
  { 0x44, 0x64, 0x54, 0x4c, 0x44 },            // 0x7a z
  { 0x00, 0x08, 0x36, 0x41, 0x00 },            // 0x7b {
  { 0x00, 0x00, 0x77, 0x00, 0x00 },            // 0x7c |
  { 0x00, 0x41, 0x36, 0x08, 0x00 },            // 0x7d }
  { 0x08, 0x04, 0x08, 0x10, 0x08 },            // 0x7e ~
};

unsigned int xcharacter, ycharacter;           // x character(0-7), y character(0-19)
unsigned int xcursor, ycursor;                 // x and y cursor position(0-7, 0-19)
unsigned int cursor_flag = 0;

/* ------------------------------------------------------------------------------- */
/*    Write a Command                                                              */
/* ------------------------------------------------------------------------------- */
void GLCD_command(unsigned int cs, unsigned int command)
{
  AT91F_PIO_ClearOutput(AT91C_BASE_PIOA, GLCD_CS2 | GLCD_CS1);  // CS0 = CS1 = 0
  AT91F_PIO_SetOutput(AT91C_BASE_PIOA, cs);    // CS0 or CS1 = 1
  AT91F_PIO_ClearOutput(AT91C_BASE_PIOA, GLCD_DI);  // D/-I = 0
  Delay_1us();

  AT91F_PIO_SetOutput(AT91C_BASE_PIOA, command << 24);  // output command
  AT91F_PIO_ClearOutput(AT91C_BASE_PIOA, (~command) << 24);
  AT91F_PIO_SetOutput(AT91C_BASE_PIOA, GLCD_E); // E = 1
  Delay_1us();
  AT91F_PIO_ClearOutput(AT91C_BASE_PIOA, GLCD_E); // E = 0

  Delay_us(10);                                // wait for GLCD busy
}

/* ------------------------------------------------------------------------------- */
/*    Write a DD RAM Data                                                          */
/* ------------------------------------------------------------------------------- */
void GLCD_data(unsigned int cs, unsigned int data)
{
  AT91F_PIO_ClearOutput(AT91C_BASE_PIOA, GLCD_CS2 | GLCD_CS1);  // CS0 = CS1 = 0
  AT91F_PIO_SetOutput(AT91C_BASE_PIOA, cs);    // CS0 or CS1 = 1
  AT91F_PIO_SetOutput(AT91C_BASE_PIOA, GLCD_DI);  // D/-I = 1
  Delay_1us();

  AT91F_PIO_SetOutput(AT91C_BASE_PIOA, data << 24); // output data
  AT91F_PIO_ClearOutput(AT91C_BASE_PIOA, (~data) << 24);
  AT91F_PIO_SetOutput(AT91C_BASE_PIOA, GLCD_E); // E = 1
  Delay_1us();
  AT91F_PIO_ClearOutput(AT91C_BASE_PIOA, GLCD_E); // E = 0

  Delay_us(10);                                // wait for GLCD busy
}

/* ------------------------------------------------------------------------------- */
/*    Clear GLCD Screen                                                            */
/* ------------------------------------------------------------------------------- */
void GLCD_clear(void)
{
  unsigned int i, j, x;

  AT91F_PIO_CfgOutput(AT91C_BASE_PIOA, GLCD_ALL); // clear all GLCD control signals
  AT91F_PIO_ClearOutput(AT91C_BASE_PIOA, GLCD_ALL);
  AT91F_PIO_Opendrain(AT91C_BASE_PIOA, GLCD_ALL);

  GLCD_command(GLCD_CS2 | GLCD_CS1, 0x3F);     // CS1,CS2 display ON
  GLCD_command(GLCD_CS2 | GLCD_CS1, 0xC0);     // CS1,CS2 display position

  x = 0xB8;
  for (i = 0; i <= 7; i++) {
    GLCD_command(GLCD_CS2 | GLCD_CS1, x);      // X start addtess
    GLCD_command(GLCD_CS2 | GLCD_CS1, 0x40);   // Y start address
    for (j = 0; j <= 63; j++)
      GLCD_data(GLCD_CS2 | GLCD_CS1, 0x00);    // clear CS1 and CS2 screen
    x++;
  }
}

/* ------------------------------------------------------------------------------- */
/*    Set English(ASCII) Character Position                                        */
/* ------------------------------------------------------------------------------- */
void GLCD_xy(unsigned int x, unsigned int y)
{
  xcharacter = x;
  ycharacter = y;

  GLCD_command(GLCD_CS2 | GLCD_CS1, 0xB8 + xcharacter); // X address

  if (ycharacter <= 9)                         // if y <= 9, CS1 Y address
    GLCD_command(GLCD_CS1, 0x40 + ycharacter * 6 + 4);
  else                                         // if y >= 10, CS2 Y address
    GLCD_command(GLCD_CS2, 0x40 + (ycharacter - 10) * 6);
}

/* ------------------------------------------------------------------------------- */
/*    Display a 6x8 Dot English(ASCII)                                             */
/* ------------------------------------------------------------------------------- */
void GLCD_English(unsigned int attribute, unsigned char character)
{
  unsigned int i, cs, x;

  GLCD_xy(xcharacter, ycharacter);
  if (ycharacter <= 9)                         // if y <= 9, CS1
    cs = GLCD_CS1;
  else                                         // if y >= 10, CS2
    cs = GLCD_CS2;
  for (i = 0; i <= 4; i++) {
    x = font[character - 0x20][i];
    if ((cursor_flag == 1) && (xcharacter == xcursor) && (ycharacter == ycursor))
      x |= 0x80;
    if (attribute == 0x01)                     // reverse ?
      x = ~x;
    GLCD_data(cs, x);
  }
  x = 0x00;                                    // last byte of font
  if (attribute == 0x01)
    x = ~x;
  GLCD_data(cs, x);

  ycharacter++;                                // go next character position
  if (ycharacter == 20) {
    ycharacter = 0;
    xcharacter++;
  }
}

/* ------------------------------------------------------------------------------- */
/*    Display a String(attribute : 0x00 = normal, 0x01 = reverse)                  */
/* ------------------------------------------------------------------------------- */
void GLCD_string(unsigned int x, unsigned int y, unsigned int attribute, char *string)
{
  xcharacter = x;
  ycharacter = y;

  while (*string != '\0') {
    GLCD_English(attribute, *string);          // display a charcater
    string++;
  }
}

/* ------------------------------------------------------------------------------- */
/*        Graphic Functions on GLCD Module                                         */
/* ------------------------------------------------------------------------------- */
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

unsigned char screen[8][128];                  // GLCD screen buffer

void Axis_xy(unsigned int x, unsigned int y)
{                                              /* set x, y axis position */
  GLCD_command(GLCD_CS2 | GLCD_CS1, 0xB8 + x); // X address(0 - 7)

  if (y <= 63)                                 // if y <= 63, CS1 Y address
    GLCD_command(GLCD_CS1, 0x40 + y);
  else                                         // if y >= 64, CS2 Y address
    GLCD_command(GLCD_CS2, 0x40 + y - 64);
}

void Draw(void)
{                                              /* draw screen with buffer data */
  unsigned int x, y;

  for (x = 0; x <= 7; x++) {
    Axis_xy(x, 0);                             // draw CS1 area
    for (y = 0; y <= 63; y++)
      GLCD_data(GLCD_CS1, screen[x][y]);
    Axis_xy(x, 64);                            // draw CS2 area
    for (y = 64; y <= 127; y++)
      GLCD_data(GLCD_CS2, screen[x][y]);
  }
}

void Clear_screen(void)
{                                              /* clear buffer and GLCD screen */
  unsigned int x, y;

  AT91F_PIO_CfgOutput(AT91C_BASE_PIOA, GLCD_ALL); // clear all GLCD control signals
  AT91F_PIO_ClearOutput(AT91C_BASE_PIOA, GLCD_ALL);
  AT91F_PIO_Opendrain(AT91C_BASE_PIOA, GLCD_ALL);

  GLCD_command(GLCD_CS2 | GLCD_CS1, 0x3F);     // CS1,CS2 display ON
  GLCD_command(GLCD_CS2 | GLCD_CS1, 0xC0);     // CS1,CS2 display position

  for (x = 0; x <= 7; x++)                     // clear screen buffer
    for (y = 0; y <= 127; y++)
      screen[x][y] = 0;

  Draw();                                      // clear screen
}

void Dot(unsigned int xx, unsigned int y)
{                                              /* draw a dot on GLCD */
  unsigned int x, i;

  if ((xx > 63) || (y > 127))
    return;

  x = xx / 8;                                  // calculate x address
  i = xx % 8;
  if (i == 0)
    i = 0x01;
  else if (i == 1)
    i = 0x02;
  else if (i == 2)
    i = 0x04;
  else if (i == 3)
    i = 0x08;
  else if (i == 4)
    i = 0x10;
  else if (i == 5)
    i = 0x20;
  else if (i == 6)
    i = 0x40;
  else
    i = 0x80;
  screen[x][y] |= i;                           // OR old data with new data

  Axis_xy(x, y);                               // draw dot on GLCD screen
  if (y <= 63)
    GLCD_data(GLCD_CS1, screen[x][y]);
  else
    GLCD_data(GLCD_CS2, screen[x][y]);
}

void Line(int xx1, int yy1, int xx2, int yy2)
{                                              /* draw a straight line */
  int x, y;

  if (yy1 != yy2) {                            // if yy1 != yy2, y is variable
    if (yy1 < yy2)                             //              x is function
      for (y = yy1; y <= yy2; y++) {
        x = xx1 + (y - yy1) * (xx2 - xx1) / (yy2 - yy1);
        Dot(x, y);
    } else
      for (y = yy1; y >= yy2; y--) {
        x = xx1 + (y - yy1) * (xx2 - xx1) / (yy2 - yy1);
        Dot(x, y);
      }
  } else if (xx1 != xx2) {                     // if xx1 != xx2, x is variable
    if (xx1 < xx2)                             //              y is function
      for (x = xx1; x <= xx2; x++) {
        y = yy1 + (x - xx1) * (yy2 - yy1) / (xx2 - xx1);
        Dot(x, y);
    } else
      for (x = xx1; x >= xx2; x--) {
        y = yy1 + (x - xx1) * (yy2 - yy1) / (xx2 - xx1);
        Dot(x, y);
      }
  } else                                       // if xx1 == xx2 and yy1 == yy2,
    Dot(xx1, yy1);                             //             it is a dot
}

void Rectangle(int xx1, int yy1, int xx2, int yy2)
{                                              /* draw a rectangle */
  Line(xx1, yy1, xx1, yy2);                    // horizontal line
  Line(xx2, yy1, xx2, yy2);
  Line(xx1, yy1, xx2, yy1);                    // vertical line
  Line(xx1, yy2, xx2, yy2);
}

void Circle(int xx1, int yy1, int r)
{                                              /* draw a circle */
  int x, y;
  float s;

  for (y = yy1 - r * 3 / 4; y <= yy1 + r * 3 / 4; y++) {  // draw with y variable
    s = sqrt(r * r - (y - yy1) * (y - yy1)) + 0.5;
    x = xx1 + (unsigned int)s;
    Dot(x, y);
    x = xx1 - (unsigned int)s;
    Dot(x, y);
  }

  for (x = xx1 - r * 3 / 4; x <= xx1 + r * 3 / 4; x++) {  // draw with x variable
    s = sqrt(r * r - (x - xx1) * (x - xx1)) + 0.5;
    y = yy1 + (unsigned int)s;
    Dot(x, y);
    y = yy1 - (unsigned int)s;
    Dot(x, y);
  }
}

void Sine(int peak)
{                                              /* draw a sine curve */
  int x, y;

  if (peak > 30)
    return;

  for (y = 0; y <= 120; y++) {
    x = 32 - (int)(sin((float)y * 3. * M_PI / 180.) * peak + 0.5);
    Dot(x, y + 3);
  }
}

void Cosine(int peak)
{                                              /* draw a cosine curve */
  int x, y;

  if (peak > 30)
    return;

  for (y = 0; y <= 120; y++) {
    x = 32 - (int)(cos((float)y * 3. * M_PI / 180.) * peak + 0.5);
    Dot(x, y + 3);
  }
}
