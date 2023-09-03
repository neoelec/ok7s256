/* ========================================================================== */
/*             Xtest08_3.c : PIO Interrupt Program by KEY1 & KEY2             */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <board.h>

#include <OK7S256gcc.h>

void PIO_ISR(void)
{                                              /* PIO interrupt service routine */
  unsigned int i, status;

  status = (AT91F_PIO_GetInterruptStatus(AT91C_BASE_PIOA) >> 7) & 0x00000003;
  if (status == 1) {                           // if KEY1, blink LED1 by 3 times
    LCD_string(0xC0, "    by KEY1     ");
    for (i = 1; i <= 3; i++) {
      LED_on(LED1);
      Delay_ms(300);
      LED_off(LED1);
      Delay_ms(300);
    }
  } else if (status == 2) {                    // if KEY2, blink LED2 by 3 times
    LCD_string(0xC0, "    by KEY2     ");
    for (i = 1; i <= 3; i++) {
      LED_on(LED2);
      Delay_ms(300);
      LED_off(LED2);
      Delay_ms(300);
    }
  }
}

int main(void)
{
  MCU_initialize();                            // initialize AT91SAM7S256 & kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD

  LCD_string(0x80, " PIO Interrupt  ");        // display title on text LCD
  LCD_string(0xC0, "                ");
  Beep();

  AT91F_PIO_InputFilterEnable(AT91C_BASE_PIOA, KEY2 | KEY1);  // initialize PIO interrupt
  AT91F_PIO_InterruptEnable(AT91C_BASE_PIOA, KEY2 | KEY1);
  AT91F_AIC_ConfigureIt(AT91C_BASE_AIC, AT91C_ID_PIOA, 7, 1, PIO_ISR);
  AT91F_AIC_EnableIt(AT91C_BASE_AIC, AT91C_ID_PIOA);

  while (1) ;                                  // wait for interrupts
}
