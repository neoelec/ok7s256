/* ========================================================================== */
/*                    Xtest04_1.c : Basic Text LCD Display                    */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <board.h>

#include <OK7S256gcc.h>

int main(void)
{
  unsigned int i;

  MCU_initialize();                            // initialize AT91SAM7S256 & kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD

  while (1) {
    Beep();
    LCD_string(0x80, " OK-7S256  V1.0 ");      // logo title 1
    LCD_string(0xC0, "AT91SAM7S256 ARM");
    Delay_ms(2000);
    LCD_string(0xC0, "   2007/06/01   ");      // logo title 2
    Delay_ms(2000);
    LCD_string(0xC0, "  Ohm Books Co. ");      // logo title 3
    Delay_ms(2000);

    Beep();
    LCD_string(0x80, "0123456789ABCDEF0123456789ABCDEF"); // display long line
    LCD_string(0xC0, "Go shift left and right 16 times");
    Delay_ms(1000);

    for (i = 0; i < 16; i++) {                 // shift left
      LCD_command(0x18);
      Delay_ms(300);
    }
    Delay_ms(1000);

    for (i = 0; i < 16; i++) {                 // shift right
      LCD_command(0x1C);
      Delay_ms(300);
    }
    Delay_ms(1000);
  }
}
