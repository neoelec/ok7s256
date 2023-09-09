/* NOTE: https://github.com/arduino-libraries/LiquidCrystal/ */
#ifndef __LCD_H__
#define __LCD_H__

#include <board.h>
/* - */
#include <stdint.h>

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

extern void LCD_Configure(uint8_t cols, uint8_t lines, uint8_t dotsize);
extern void LCD_Clear(void);
extern void LCD_Home(void);
extern void LCD_NoDisplay(void);
extern void LCD_Display(void);
extern void LCD_NoBlink(void);
extern void LCD_Blink(void);
extern void LCD_NoCursor(void);
extern void LCD_Cursor(void);
extern void LCD_ScrollDisplayLeft(void);
extern void LCD_ScrollDisplayRight(void);
extern void LCD_LeftToRight(void);
extern void LCD_RightToLeft(void);
extern void LCD_Autoscroll(void);
extern void LCD_NoAutoscroll(void);
extern void LCD_CreateChar(uint8_t location, const uint8_t charmap[]);
extern void LCD_SetCursor(uint8_t col, uint8_t row);
extern void LCD_Command(uint8_t value);
extern void LCD_PutChar(char ch);
extern void LCD_PutCharAt(uint8_t col, uint8_t row, char ch);
extern void LCD_PutString(const char *str);
extern void LCD_PutStringAt(uint8_t col, uint8_t row, const char *str);

#endif /* __LCD_H__ */
