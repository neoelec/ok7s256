/* ========================================================================== */
/*       Xtest10_2.c : Digital Clock with Time Adjust by PIT Interrupt        */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <board.h>

#include <OK7S256gcc.h>

volatile unsigned int PIT_count = 0;           // PIT interrupt count
volatile unsigned int cursor, second, minute, hour, ampm; // time variable

void LCD_2d(unsigned int number)
{                                              /* display 2-digit decimal number */
  LCD_data(number / 10 + '0');                 // 10^1
  LCD_data(number % 10 + '0');                 // 10^0
}

void Cursor_left(void)
{                                              /* go cursor left */
  if (cursor != 0xC3)
    cursor -= 3;
  else
    cursor = 0xCF;
  LCD_command(cursor);
}

void Increment(void)
{                                              /* increment time */
  switch (cursor) {
  case 0xC3:
    if (hour != 12)
      hour++;                                  // in case of hour
    else
      hour = 1;
    LCD_command(0xC2);
    LCD_2d(hour);
    LCD_command(cursor);
    break;
  case 0xC6:
    if (minute != 59)
      minute++;                                // in case of minute
    else
      minute = 0;
    LCD_command(0xC5);
    LCD_2d(minute);
    LCD_command(cursor);
    break;
  case 0xC9:
    if (second != 59)
      second++;                                // in case of second
    else
      second = 0;
    LCD_command(0xC8);
    LCD_2d(second);
    LCD_command(cursor);
    break;
  case 0xCC:
    if (ampm == 'A')
      ampm = 'P';                              // in case of AM/PM
    else
      ampm = 'A';
    LCD_command(0xCB);
    LCD_data(ampm);
    LCD_command(cursor);
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
    LCD_command(0xC4);
    LCD_data(':');
    LCD_command(0xC7);
    LCD_data(':');
  } else if (PIT_count == 2) {
    LCD_command(0xC4);
    LCD_data(' ');
    LCD_command(0xC7);
    LCD_data(' ');
  }
  LCD_command(cursor);                         // go cursor position

  if (PIT_count != 0)
    return;                                    // display time once per second

  second++;                                    // increment second
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

  LCD_command(0xC2);
  LCD_2d(hour);                                // display hour
  LCD_command(0xC5);
  LCD_2d(minute);                              // display minute
  LCD_command(0xC8);
  LCD_2d(second);                              // display second
  LCD_command(0xCB);
  LCD_data(ampm);                              // display AM/PM
  LCD_command(cursor);                         // go cursor position
}

int main(void)
{
  MCU_initialize();                            // initialize AT91SAM7S256 & kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module

  cursor = 0xCF;                               // initial cursor position
  LCD_command(0x0F);                           // cursor ON

  hour = 12;                                   // initial time
  minute = 0;
  second = 0;
  ampm = 'A';

  LCD_string(0x80, " Digital Clock  ");        // display title
  LCD_string(0xC0, "  12:00:00 AM   ");
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
