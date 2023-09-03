/* ========================================================================== */
/*                        Xtest02_2.c : LED Display(2)                        */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <board.h>

#include <OK7S256gcc.h>

int main(void)
{
  MCU_initialize();                            // initialize AT91SAM7S256 & kit

  while (1) {
    LED_on(LED1);                              // LED1 on
    Delay_ms(100);
    LED_off(LED1);                             // LED1 off
    Delay_ms(100);

    LED_on(LED2);                              // LED2 on
    Delay_ms(100);
    LED_off(LED2);                             // LED2 off
    Delay_ms(100);

    LED_on(LED2 | LED1);                       // LED2 and LED1 on
    Delay_ms(100);
    LED_off(LED2 | LED1);                      // LED2 and LED1 off
    Delay_ms(100);
  }
}
