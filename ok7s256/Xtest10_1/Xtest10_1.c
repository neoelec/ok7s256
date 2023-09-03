/* ========================================================================== */
/*                Xtest10_1.c : Digital Clock by PIT Interrupt                */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <board.h>

#include <OK7S256gcc.h>

volatile unsigned int PIT_count = 0;           // PIT interrupt count
volatile unsigned int second, minute, hour, ampm; // time variable

void LCD_2d(unsigned int number)
{                                              /* display 2-digit decimal number */
  LCD_data(number / 10 + '0');                 // 10^1
  LCD_data(number % 10 + '0');                 // 10^0
}

void PIT_ISR(void)
{                                              /* PIT interrupt service routine */
  AT91F_PITGetPIVR(AT91C_BASE_PITC);           // clear PITS

  PIT_count++;                                 // increment PIT_count
  if (PIT_count == 4)
    PIT_count = 0;                             // 4Hz/4 = 1Hz

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
}

int main(void)
{
  MCU_initialize();                            // initialize AT91SAM7S256 & kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module

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

  while (1) ;                                  // wait for interrupt
}
