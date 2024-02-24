/* ========================================================================== */
/*               Xtest18_4.c : Idle Mode and Watchdog Timer(2)                */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <board.h>

#include <OK7S256gcc.h>

void WDT_ISR(void)
{                                              /* WDT interrupt service routine */
  AT91F_WDTSGettatus(AT91C_BASE_WDTC);         // clear WDUNF

  LCD_string(0xC0, " WDT Interrupt !");        // display interrupt
  Beep();
  Delay_ms(1000);
  LCD_string(0xC0, "Now, sleep mode!");        // display sleep mode
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
  LCD_string(0xC0, "Now, sleep mode!");        // display sleep mode

  AT91F_WDTC_CfgPMC();                         // enable peripheral clock for WDT
  *AT91C_WDTC_WDMR = 0x10001000 | (1280 << 16) | 1280;  // enable watchdog interrupt
  // WDD=WDV=1280 for 5 sec

  AT91F_AIC_ConfigureIt(AT91C_BASE_AIC, AT91C_ID_SYS, 7, 1, WDT_ISR); // enable interrupt
  AT91F_AIC_EnableIt(AT91C_BASE_AIC, AT91C_ID_SYS);

  while (1) {                                  // blink LED2 and LED1
    AT91F_PMC_CfgSysClkDisableReg(AT91C_BASE_PMC, AT91C_PMC_PCK); // go in idle mode

    LED_off(LED2);
    LED_on(LED1);
    Delay_ms(100);
    LED_on(LED2);
    LED_off(LED1);
    Delay_ms(100);
  }
}
