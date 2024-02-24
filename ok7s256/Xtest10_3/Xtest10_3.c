/* ========================================================================== */
/*     Xtest10_3.c : GLCD Digital Clock with Time Adjust by PIT Interrupt     */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <board.h>

#include <OK7S256gcc.h>
#include <OK7S256Korean.h>

volatile unsigned int PIT_count = 0;           // PIT interrupt count
volatile unsigned int cursor, second, minute, hour, ampm; // time variable

void GLCD_2d(unsigned int number)
{                                              /* display 2-digit decimal number */
  GLCD_English(0, number / 10 + '0');          // 10^1
  GLCD_English(0, number % 10 + '0');          // 10^0
}

void Cursor_left(void)
{                                              /* go cursor left */
  if (cursor != 3)
    cursor -= 3;
  else
    cursor = 15;
  ycursor = cursor;                            // set cursor position
  GLCD_xy(2, cursor);
}

void Increment(void)
{                                              /* increment time */
  switch (cursor) {
  case 3:
    if (hour != 12)
      hour++;                                  // in case of hour
    else
      hour = 1;
    GLCD_xy(2, 2);
    GLCD_2d(hour);
    GLCD_xy(2, cursor);
    break;
  case 6:
    if (minute != 59)
      minute++;                                // in case of minute
    else
      minute = 0;
    GLCD_xy(2, 5);
    GLCD_2d(minute);
    GLCD_xy(2, cursor);
    break;
  case 9:
    if (second != 59)
      second++;                                // in case of second
    else
      second = 0;
    GLCD_xy(2, 8);
    GLCD_2d(second);
    GLCD_xy(2, cursor);
    break;
  case 12:
    if (ampm == 'A')
      ampm = 'P';                              // in case of AM/PM
    else
      ampm = 'A';
    GLCD_xy(2, 11);
    GLCD_English(0, ampm);
    GLCD_xy(2, cursor);
    break;
  default:
    break;
  }
}

void PIT_ISR(void)
{                                              /* PIT interrupt service routine */
  AT91F_PITGetPIVR(AT91C_BASE_PITC);           // clear PITS

  PIT_count++;                                 // increment PIT_count
  if (PIT_count == 4)
    PIT_count = 0;                             // 4Hz/4 = 1Hz

  if (PIT_count == 0) {                        // blink semicolon
    GLCD_xy(2, 4);
    GLCD_English(0, ':');
    GLCD_xy(2, 7);
    GLCD_English(0, ':');
  } else if (PIT_count == 2) {
    GLCD_xy(2, 4);
    GLCD_English(0, ' ');
    GLCD_xy(2, 7);
    GLCD_English(0, ' ');
  }
  GLCD_xy(2, cursor);                          // go cursor position

  if (PIT_count == 0)
    second++;                                  // display time 4 times per second

  if (second == 60) {                          // if second = 60, second = 0
    second = 0;
    minute++;                                  // increment minute
    if (minute == 60) {                        // if minute = 60, minute = 0
      minute = 0;
      hour++;                                  // increment hour
      if (hour == 13)                          // if hour = 13, hour = 1
        hour = 1;
      if (hour == 12) {                        // if hour = 12, adjust AM/PM
        if (ampm == 'A')
          ampm = 'P';
        else
          ampm = 'A';
      }
    }
  }

  GLCD_xy(2, 2);
  GLCD_2d(hour);                               // display hour
  GLCD_xy(2, 5);
  GLCD_2d(minute);                             // display minute
  GLCD_xy(2, 8);
  GLCD_2d(second);                             // display second
  GLCD_xy(2, 11);
  GLCD_English(0, ampm);                       // display AM/PM
  GLCD_English(0, 'M');
  GLCD_xy(2, 15);
  GLCD_English(0, ' ');                        // clear cursor at x=2, y=15
  GLCD_xy(2, cursor);                          // go cursor position
}

int main(void)
{
  MCU_initialize();                            // initialize AT91SAM7S256 & kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module
  GLCD_clear();                                // initialize GLCD screen

  cursor = 15;                                 // initial cursor position
  xcursor = 2;
  ycursor = cursor;
  cursor_flag = 1;                             // cursor ON

  hour = 12;                                   // initial time
  minute = 0;
  second = 0;
  ampm = 'A';

  LCD_string(0x80, " Digital Clock  ");        // display title on text LCD
  LCD_string(0xC0, "    on GLCD     ");

  GLCD_string(0, 0, 0, "****************");    // display title on graphic LCD
  GLCD_string(1, 0, 0, "  디지털 시계   ");
  GLCD_string(2, 0, 0, "  12:00:00 AM   ");
  GLCD_string(3, 0, 0, "****************");
  Beep();

  AT91F_PITC_CfgPMC();                         // enable peripheral clock for PIT
  AT91F_PITInit(AT91C_BASE_PITC, 1, 48);       // enable and initialize PIT
  AT91F_PITSetPIV(AT91C_BASE_PITC, 750000 - 1); // 48MHz/16/750000 = 4Hz

  AT91F_PITEnableInt(AT91C_BASE_PITC);         // initialize PIT interrupt
  AT91F_AIC_ConfigureIt(AT91C_BASE_AIC, AT91C_ID_SYS, 7, 1, PIT_ISR);
  AT91F_AIC_EnableIt(AT91C_BASE_AIC, AT91C_ID_SYS);

  while (1) {
    switch (Key_input()) {                     // key input
    case 0x01:
      Increment();                             // if KEY1, increment time
      break;
    case 0x02:
      Cursor_left();                           // if KEY2, go cursor left
      break;
    default:
      break;
    }
  }
}
