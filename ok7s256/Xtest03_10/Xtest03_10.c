/* ========================================================================== */
/*                      Xtest03_10.c : Infinite Loop(2)                       */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <board.h>

#include <OK7S256gcc.h>

int main(void)
{
  MCU_initialize();                            // initialize AT91SAM7S256 & kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module

  LCD_string(0x80, "Infinite Loop(2)");        // display title
  LCD_string(0xC0, "                ");

  while (1) {                                  // infinite loop
    Beep();                                    // beep

    LED_on(LED1);                              // LED1 on
    Delay_ms(500);
    LED_off(LED1);                             // LED1 off
    Delay_ms(500);

    LED_on(LED2);                              // LED2 on
    Delay_ms(500);
    LED_off(LED2);                             // LED2 off
    Delay_ms(500);
  }
}
