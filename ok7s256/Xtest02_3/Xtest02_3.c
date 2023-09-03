/* ========================================================================== */
/*                       Xtest02_3.c : Text LCD Display                       */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <board.h>

#include <OK7S256gcc.h>

int main(void)
{
  MCU_initialize();                            // initialize AT91SAM7S256 & kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD

  while (1) {
    Beep();                                    // beep

    LCD_string(0x80, " OK-7S256  V1.0 ");      // logo title 1
    LCD_string(0xC0, "AT91SAM7S256 ARM");
    Delay_ms(2000);

    LCD_string(0xC0, "   2007/06/01   ");      // logo title 2
    Delay_ms(2000);

    LCD_string(0xC0, " Duck-Yong Yoon ");      // logo title 3
    Delay_ms(2000);
  }
}
