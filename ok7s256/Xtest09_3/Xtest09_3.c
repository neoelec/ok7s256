/* ========================================================================== */
/*                 Xtest09_3.c : Stop Watch by PIT Interrupt                  */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <board.h>

#include <OK7S256gcc.h>

void LCD_2d(unsigned int number)
{                                              /* display 2-digit decimal number */
  LCD_data(number / 10 + '0');                 // 10^1
  LCD_data(number % 10 + '0');                 // 10^0
}

volatile unsigned int second, minute, hour;    // time variable
volatile unsigned int run_flag;                // stop watch run flag

void PIT_ISR(void)
{                                              /* PIT interrupt service routine */
  AT91F_PITGetPIVR(AT91C_BASE_PITC);           // clear PITS

  second++;                                    // increment 1/100 second
  if (second == 6000) {                        // second = 60 ?
    second = 0;                                // if yes, second = 0 and minute++
    minute++;
    if (minute == 60) {                        // minute = 60 ?
      minute = 0;                              // if yes, minute = 0 and hour++
      hour++;
      if (hour == 100)                         // hour = 100 ?
        hour = 0;                              // if yes, hour = 0
    }
  }

  LCD_command(0xC2);                           // display hour
  LCD_2d(hour);
  LCD_command(0xC5);                           // display minute
  LCD_2d(minute);
  LCD_command(0xC8);                           // display second
  LCD_2d(second / 100);
  LCD_command(0xCB);                           // display 1/100 second
  LCD_2d(second % 100);
}

void Clear_time(void)
{                                              /* clear time */
  second = 0;                                  // clear time
  minute = 0;
  hour = 0;
  LCD_string(0xC0, "  00:00:00.00   ");        // clear display
}

int main(void)
{
  MCU_initialize();                            // initialize AT91SAM7S256 & kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module
  Beep();

  AT91F_PITC_CfgPMC();                         // enable peripheral clock for PIT
  AT91F_PITInit(AT91C_BASE_PITC, 1, 48);       // enable and initialize PIT
  AT91F_PITSetPIV(AT91C_BASE_PITC, 30000 - 1); // 48MHz/16/30000 = 100Hz

  AT91F_PITEnableInt(AT91C_BASE_PITC);         // initialize PIT interrupt
  AT91F_AIC_ConfigureIt(AT91C_BASE_AIC, AT91C_ID_SYS, 7, 1, PIT_ISR);
  AT91F_AIC_DisableIt(AT91C_BASE_AIC, AT91C_ID_SYS);

  LCD_string(0x80, "** STOP WATCH **");        // display title
  Clear_time();                                // clear time and display
  run_flag = 0;                                // default state

  while (1) {
    switch (Key_input()) {                     // key input
    case 0x01:
      if (run_flag == 0) {                     // if KEY1 & run_flag=0, strat
        run_flag = 1;
        AT91F_AIC_EnableIt(AT91C_BASE_AIC, AT91C_ID_SYS);
      } else {                                 // if KEY1 & run_flag=1, stop
        run_flag = 0;
        AT91F_AIC_DisableIt(AT91C_BASE_AIC, AT91C_ID_SYS);
      }
      break;
    case 0x02:
      if (run_flag == 1)
        break;                                 // if KEY2 & run_flag=1, ignore
      Clear_time();                            // if KEY2 & run_flag=0, clear time
      break;
    default:
      break;
    }
  }
}
