/* ========================================================================== */
/*             Xtest03_6.c : Test Time-Delay Function by Hardware             */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <board.h>

#include <OK7S256gcc.h>

volatile unsigned int ms_count = 0;            // ms count by PIT interrupt

void PIT_ISR(void)
{                                              /* PIT interrupt service routine */
  AT91F_PITGetPIVR(AT91C_BASE_PITC);           // clear PITS
  ms_count++;                                  // increment ms_count
}

void PIT_initialize(void)
{                                              /* initialize PIT and interrupt */
  AT91F_PITC_CfgPMC();                         // enable peripheral clock for PIT
  AT91F_PITInit(AT91C_BASE_PITC, 1, 48);       // enable and initialize PIT
  AT91F_PITSetPIV(AT91C_BASE_PITC, 3000 - 1);  // set period for PIT interrupt

  AT91F_PITDisableInt(AT91C_BASE_PITC);        // initialize PIT interrupt
  AT91F_AIC_ConfigureIt(AT91C_BASE_AIC, AT91C_ID_SYS, 7, 1, PIT_ISR);
  AT91F_AIC_EnableIt(AT91C_BASE_AIC, AT91C_ID_SYS);
}

void HW_delay_ms(unsigned int ms)
{                                              /* ms delay by PIT interrupt */
  if (ms == 0)
    return;

  ms_count = 0;                                // start time
  AT91F_PITEnableInt(AT91C_BASE_PITC);         // enable PIT interrupt
  while (ms_count < ms) ;                      // wait for ms

  AT91F_PITDisableInt(AT91C_BASE_PITC);        // disable PIT interrupt
}

int main(void)
{
  unsigned int i;

  MCU_initialize();                            // initialize AT91SAM7S256 & kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module

  LCD_string(0x80, " S/W Time Delay ");        // display title
  LED_off(LED2 | LED1);                        // LED2~LED1 off

  PIT_initialize();                            // initialize PIT and interrupt

  while (1) {
    LCD_string(0xC0, " 10ms delay test");      // output pulse by 10ms delay
    Beep();
    for (i = 0; i < 500; i++) {
      LED_on(LED2);                            // LED2 on
      HW_delay_ms(10);
      LED_off(LED2);                           // LED2 off
      HW_delay_ms(10);
    }

    LCD_string(0xC0, "100ms delay test");      // output pulse by 100ms delay
    Beep();
    for (i = 0; i < 50; i++) {
      LED_on(LED2);                            // LED2 on
      HW_delay_ms(100);
      LED_off(LED2);                           // LED2 off
      HW_delay_ms(100);
    }

    LCD_string(0xC0, "500ms delay test");      // output pulse by 500ms delay
    Beep();
    for (i = 0; i < 10; i++) {
      LED_on(LED2);                            // LED2 on
      Delay_ms(500);
      LED_off(LED2);                           // LED2 off
      Delay_ms(500);
    }
  }
}
