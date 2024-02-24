/* ========================================================================== */
/*                Xtest18_1.c : Watchdog Timer Test(1) - Reset                */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <board.h>

#include <OK7S256gcc.h>

int main(void)
{
  unsigned int mode = 0;

  MCU_initialize();                            // initialize AT91SAM7S256 & kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module

  LCD_string(0x80, " OK-7S256  V1.0 ");        // display title
  LCD_string(0xC0, " Watchdog Reset ");
  Beep();

  LED_on(LED2 | LED1);                         // blink LED2 and LED1
  Delay_ms(1000);
  LED_off(LED2 | LED1);

  AT91F_WDTC_CfgPMC();                         // enable peripheral clock for WDT
  *AT91C_WDTC_WDMR = 0x30002000 | (51 << 16) | 51;  // enable watchdog reset
  // WDD=WDV=51 for 200ms

  while (1) {
    LCD_string(0x80, " KEY1 = 100 ms  ");      // display title
    LCD_string(0xC0, " KEY2 = 300 ms  ");

    switch (Key_input()) {                     // key input
    case 1:
      mode = 1;                                // if KEY1, mode=1
      break;
    case 2:
      mode = 2;                                // if KEY2. mode=2
      break;
    default:
      if (mode == 0) {
        AT91F_WDTRestart(AT91C_BASE_WDTC);     // restart WDT
        break;
      }
      LED_on(LED2);                            // if mode=1, 100ms interval
      if (mode == 1)
        Delay_ms(100);                         // if mode=2, 300ms interval
      else if (mode == 2)
        Delay_ms(300);
      AT91F_WDTRestart(AT91C_BASE_WDTC);       // restart WDT
      LED_off(LED2);
      if (mode == 1)
        Delay_ms(100);
      else if (mode == 2)
        Delay_ms(300);
      AT91F_WDTRestart(AT91C_BASE_WDTC);       // restart WDT
      break;
    }
  }
}
