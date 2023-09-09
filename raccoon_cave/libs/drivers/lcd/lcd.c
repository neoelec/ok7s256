#include <pio/pio.h>
#include <stdlib.h>
#include <utility/delay.h>

#include "lcd.h"

#define RS_CMD 0
#define RS_DATA 1

static uint8_t displayFunction = LCD_8BITMODE | LCD_1LINE | LCD_5x8DOTS;
static uint8_t displayControl;
static uint8_t displayMode;

static uint8_t numLines;
static uint8_t rowOffsets[4];

static void __InitHW(void);
static void __Command(uint8_t value);
static inline void __Write4Bits(uint8_t value);
static inline void __Write8Bits(uint8_t value);
static void __Write(uint8_t value);
static inline void __Delay1Microsecond(void);
static inline void __DelayMicroseconds(unsigned int value);
static inline void __DelayMillisecond(unsigned int value);

static void __SetRowOffsets(int row0, int row1, int row2, int row3)
{
    rowOffsets[0] = row0;
    rowOffsets[1] = row1;
    rowOffsets[2] = row2;
    rowOffsets[3] = row3;
}

// When the display powers up, it is configured as follows:
//
// 1. Display clear
// 2. Function set:
//    DL = 1; 8-bit interface data
//    N = 0; 1-line display
//    F = 0; 5x8 dot character font
// 3. Display on/off control:
//    D = 0; Display off
//    C = 0; Cursor off
//    B = 0; Blinking off
// 4. Entry mode set:
//    I/D = 1; Increment by 1
//    S = 0; No shift

void LCD_Configure(uint8_t cols, uint8_t lines, uint8_t dotsize)
{
    __InitHW();

    if (lines > 1)
        displayFunction |= LCD_2LINE;

    numLines = lines;

    __SetRowOffsets(0x00, 0x40, 0x00 + cols, 0x40 + cols);

    // for some 1 line displays you can select a 10 pixel high font
    if ((dotsize != LCD_5x8DOTS) && (lines == 1))
        displayFunction |= LCD_5x10DOTS;

    //put the LCD into 4 bit or 8 bit mode
    if (!(displayFunction & LCD_8BITMODE)) {
        // this is according to the Hitachi HD44780 datasheet
        // figure 24, pg 46

        // we start in 8bit mode, try to set 4 bit mode
        __Write4Bits(0x03);
        __DelayMillisecond(5);;                // wait min 4.1ms

        // second try
        __Write4Bits(0x03);
        __DelayMillisecond(5);                 // wait min 4.1ms

        // third go!
        __Write4Bits(0x03);
        __DelayMicroseconds(150);

        // finally, set to 4-bit interface
        __Write4Bits(0x02);
    } else {
        // this is according to the Hitachi HD44780 datasheet
        // page 45 figure 23

        // Send function set command sequence
        __Command(LCD_FUNCTIONSET | displayFunction);
        __DelayMillisecond(5);                 // wait more than 4.1 ms

        // second try
        __Command(LCD_FUNCTIONSET | displayFunction);
        __DelayMicroseconds(150);

        // third go
        __Command(LCD_FUNCTIONSET | displayFunction);
    }

    // finally, set # lines, font size, etc.
    __Command(LCD_FUNCTIONSET | displayFunction);

    displayControl = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
    LCD_Display();

    // clear it off
    LCD_Clear();

    // Initialize to default text direction (for romance languages)
    displayMode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
    // set the entry mode
    __Command(LCD_ENTRYMODESET | displayMode);
}

/********** high level commands, for the user! */

void LCD_Clear(void)
{
    __Command(LCD_CLEARDISPLAY);               // clear display, set cursor position to zero
    __DelayMillisecond(2);                     // this __Command takes a long time!
}

void LCD_Home(void)
{
    __Command(LCD_RETURNHOME);                 // set cursor position to zero
    __DelayMillisecond(2);                     // this __Command takes a long time!
}

// Turn the display on/off (quickly)
void LCD_NoDisplay(void)
{
    displayControl &= ~LCD_DISPLAYON;
    __Command(LCD_DISPLAYCONTROL | displayControl);
}

void LCD_Display(void)
{
    displayControl |= LCD_DISPLAYON;
    __Command(LCD_DISPLAYCONTROL | displayControl);
}

// Turn on and off the blinking cursor
void LCD_NoBlink(void)
{
    displayControl &= ~LCD_BLINKON;
    __Command(LCD_DISPLAYCONTROL | displayControl);
}

void LCD_Blink(void)
{
    displayControl |= LCD_BLINKON;
    __Command(LCD_DISPLAYCONTROL | displayControl);
}

// Turns the underline cursor on/off
void LCD_NoCursor(void)
{
    displayControl &= ~LCD_CURSORON;
    __Command(LCD_DISPLAYCONTROL | displayControl);
}

void LCD_Cursor(void)
{
    displayControl |= LCD_CURSORON;
    __Command(LCD_DISPLAYCONTROL | displayControl);
}

// These commands scroll the display without changing the RAM
void LCD_ScrollDisplayLeft(void)
{
    __Command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}

void LCD_ScrollDisplayRight(void)
{
    __Command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

// This is for text that flows Left to Right
void LCD_LeftToRight(void)
{
    displayMode |= LCD_ENTRYLEFT;
    __Command(LCD_ENTRYMODESET | displayMode);
}

// This is for text that flows Right to Left
void LCD_RightToLeft(void)
{
    displayMode &= ~LCD_ENTRYLEFT;
    __Command(LCD_ENTRYMODESET | displayMode);
}

// This will 'right justify' text from the cursor
void LCD_Autoscroll(void)
{
    displayMode |= LCD_ENTRYSHIFTINCREMENT;
    __Command(LCD_ENTRYMODESET | displayMode);
}

// This will 'left justify' text from the cursor
void LCD_NoAutoscroll(void)
{
    displayMode &= ~LCD_ENTRYSHIFTINCREMENT;
    __Command(LCD_ENTRYMODESET | displayMode);
}

// Allows us to fill the first 8 CGRAM locations
// with custom characters
void LCD_CreateChar(uint8_t location, const uint8_t charmap[])
{
    size_t i;

    location &= 0x7;                           // we only have 8 locations 0-7
    __Command(LCD_SETCGRAMADDR | (location << 3));

    for (i = 0; i < 8; i++)
        __Write(charmap[i]);
}

void LCD_SetCursor(uint8_t col, uint8_t row)
{
    const size_t max_lines = sizeof(rowOffsets) / sizeof(*rowOffsets);
    if (row >= max_lines)
        row = max_lines - 1;                   // we count rows starting w/ 0

    if (row >= numLines)
        row = numLines - 1;                    // we count rows starting w/ 0

    __Command(LCD_SETDDRAMADDR | (col + rowOffsets[row]));
}

void LCD_Command(uint8_t value)
{
    __Command(value);
}

void LCD_PutChar(char ch)
{
    __Write(ch);
}

void LCD_PutCharAt(uint8_t col, uint8_t row, char ch)
{
    LCD_SetCursor(col, row);
    __Write(ch);
}

void LCD_PutString(const char *str)
{
    while (*str)
        __Write(*str++);
}

void LCD_PutStringAt(uint8_t col, uint8_t row, const char *str)
{
    LCD_SetCursor(col, row);

    while (*str)
        __Write(*str++);
}

/* HW glue layer */

static const Pin __pinLcdRS = PIN_LCD_RS;
static const Pin __pinLcdE = PIN_LCD_E;
static const Pin *pinLcdRS = &__pinLcdRS;
static const Pin *pinLcdE = &__pinLcdE;
static const Pin pinsLcdDATA[] = { PINS_LCD_DATA };

static const unsigned int numLcdDATA = PIO_LISTSIZE(pinsLcdDATA);

#ifdef PIN_LCD_RW
static const Pin __pinLcdRW = PIN_LCD_RW;
static const Pin *pinLcdRW = &__pinLcdRW;
#else
static const Pin *pinLcdRW = NULL;
#endif

static inline void __Delay1Microsecond(void)
{
    DELAY_1us();
}

static inline void __DelayMicroseconds(unsigned int value)
{
    DELAY_us(value);
}

static inline void __DelayMillisecond(unsigned int value)
{
    DELAY_ms(value);
}

static void __InitHW(void)
{
    PIO_Configure(pinLcdRS, 1);
    PIO_Configure(pinLcdE, 1);
    PIO_Configure(pinsLcdDATA, numLcdDATA);

    // we can save 1 pin by not using RW. Indicate by passing 255 instead of pin#
    if (pinLcdRW != NULL)
        PIO_Configure(pinLcdRW, 1);

    // SEE PAGE 45/46 FOR INITIALIZATION SPECIFICATION!
    // according to datasheet, we need at least 40 ms after power rises above 2.7 V
    // before sending commands. Arduino can turn on way before 4.5 V so we'll wait 50
    DELAY_ms(50);

    if (numLcdDATA == 4)
        displayFunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;
    else
        displayFunction = LCD_8BITMODE | LCD_1LINE | LCD_5x8DOTS;
}

/************ low level data pushing commands **********/

static void __PulseEnable(void)
{
    PIO_Clear(pinLcdE);
    __Delay1Microsecond();
    PIO_Set(pinLcdE);
    __Delay1Microsecond();                     // enable pulse must be >450 ns
    PIO_Clear(pinLcdE);
    __DelayMicroseconds(100);                  // commands need >37 us to settle
}

static inline void __Write4Bits(uint8_t value)
{
    uint8_t i;

    for (i = 0; i < 4; i++) {
        if (value & (1 << i))
            PIO_Set(&pinsLcdDATA[i]);
        else
            PIO_Clear(&pinsLcdDATA[i]);
    }

    __PulseEnable();
}

static inline void __Write8Bits(uint8_t value)
{
    uint8_t i;

    for (i = 0; i < 8; i++) {
        if (value & (1 << i))
            PIO_Set(&pinsLcdDATA[i]);
        else
            PIO_Clear(&pinsLcdDATA[i]);
    }

    __PulseEnable();
}

static void __Send(uint8_t value, uint8_t mode)
{
    if (mode != 0)
        PIO_Set(pinLcdRS);
    else
        PIO_Clear(pinLcdRS);

    // if there is a RW pin indicated, set it low to Write
    if (pinLcdRW != NULL)
        PIO_Clear(pinLcdRW);

    if (numLcdDATA == 4) {
        __Write4Bits(value >> 4);
        __Write4Bits(value);
    } else {
        __Write8Bits(value);
    }
}

/*********** mid level commands, for sending data/cmds */

static void __Command(uint8_t value)
{
    __Send(value, RS_CMD);
}

static void __Write(uint8_t value)
{
    __Send(value, RS_DATA);
}
