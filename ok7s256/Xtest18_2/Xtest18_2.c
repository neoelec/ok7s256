/* ========================================================================== */
/*              Xtest18_2.c : Watchdog Timer Test(2) - Interrupt              */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <board.h>

#include <OK7S256gcc.h>

volatile unsigned int mode = 0;                // test mode

void WDT_ISR(void)
{                                              /* WDT interrupt service routine */
  unsigned int i;

  AT91F_WDTSGettatus(AT91C_BASE_WDTC);         // clear WDUNF

  LCD_string(0x80, " OK-7S256  V1.0 ");        // display interrupt
  LCD_string(0xC0, "  Watchdog Int. ");
  LED_on(LED2 | LED1);                         // blink LED2 and LED1
  Beep();
  for (i = 0; i < 10; i++) {                   // delay 1 sec
    Delay_ms(100);
    AT91F_WDTRestart(AT91C_BASE_WDTC);
  }
  LED_off(LED2 | LED1);

  mode = 0;                                    // return to mode=0
}

int main(void)
{
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
  *AT91C_WDTC_WDMR = 0x30001000 | (51 << 16) | 51;  // enable watchdog interrupt
  // WDD=WDV=51 for 200ms

  AT91F_AIC_ConfigureIt(AT91C_BASE_AIC, AT91C_ID_SYS, 7, 1, WDT_ISR); // enable interrupt
  AT91F_AIC_EnableIt(AT91C_BASE_AIC, AT91C_ID_SYS);

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
