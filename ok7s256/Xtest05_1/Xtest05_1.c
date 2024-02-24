/* ========================================================================== */
/*                  Xtest05_1.c : Basic Graphic LCD Display                   */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <board.h>

#include <OK7S256gcc.h>
#include <OK7S256GLCD.h>

int main(void)
{
  unsigned int i;

  MCU_initialize();                            // initialize AT91SAM7S256 & kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD
  GLCD_clear();                                // initialize GLCD screen

  LCD_string(0x80, "Graphic LCD Test");        // display title on text LCD
  LCD_string(0xC0, " ASCII(English) ");
  Beep();

  while (1) {
    GLCD_string(0, 0, 1, " OK-7S256 Kit  V1.0 "); // display screen 1
    GLCD_string(1, 0, 0, "     2007/06/01     ");
    GLCD_string(2, 0, 0, "                    ");
    GLCD_string(3, 0, 0, "     Designed by    ");
    GLCD_string(4, 0, 0, "   Duck-Yong Yoon.  ");
    GLCD_string(5, 0, 0, "                    ");
    GLCD_string(6, 0, 0, "      Made by       ");
    GLCD_string(7, 0, 0, "    Ohm Books Co.   ");
    Delay_ms(5000);

    GLCD_string(0, 0, 1, "     Hyundai LCD    "); // display screen 2
    GLCD_string(1, 0, 1, "    HG12605NY-LY    ");
    GLCD_string(2, 0, 0, "                    ");
    GLCD_string(3, 0, 0, "    Yellow/Green    ");
    GLCD_string(4, 0, 0, " LED Backlight Type ");
    GLCD_string(5, 0, 0, "                    ");
    GLCD_string(6, 0, 0, "128 x 64 Graphic LCD");
    GLCD_string(7, 0, 0, " 6x8 Box, 5x7 ASCII ");
    Delay_ms(5000);

    GLCD_string(0, 0, 0, "===================="); // display screen 3
    GLCD_string(1, 0, 1, "  ASCII Characters  ");
    GLCD_string(2, 0, 0, "====================");
    GLCD_string(7, 0, 0, "                    ");

    GLCD_xy(3, 0);
    for (i = 0x20; i < 0x7F; i++)              // from 0x20 to 0x7E
      GLCD_English(0, i);
    Delay_ms(5000);
  }
}
