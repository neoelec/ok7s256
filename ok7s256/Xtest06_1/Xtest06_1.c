/* ========================================================================== */
/*                   Xtest06_1.c : Function Display on GLCD                   */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <board.h>

#include <OK7S256gcc.h>
#include <OK7S256GLCD.h>

int main(void)
{
  unsigned int i, x, y;

  MCU_initialize();                            // initialize AT91SAM7S256 & kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD
  GLCD_clear();                                // initialize GLCD screen
  Beep();

  LCD_string(0x80, "Graphic LCD Test");        // display title on text LCD

  while (1) {
    LCD_string(0xC0, "   (1) Lines    ");      // graphic show 1
    Rectangle(0, 0, 63, 127);
    Delay_ms(300);
    for (i = 0, x = 7, y = 15; i <= 7; i++, x += 8, y += 16) {
      Line(x, 0, 0, y);
      Line(0, 127 - y, x, 127);
      Delay_ms(300);
    }
    for (i = 0, x = 7, y = 15; i <= 7; i++, x += 8, y += 16) {
      Line(63, y, x, 127);
      Line(x, 0, 63, 127 - y);
      Delay_ms(300);
    }
    Delay_ms(2000);
    Clear_screen();

    LCD_string(0xC0, " (2) Rectangles ");      // graphic show 2
    for (i = 0, x = 0, y = 0; i <= 7; i++, x += 4, y += 8) {
      Rectangle(x, y, 63 - x, 127 - y);
      Delay_ms(300);
    }
    Delay_ms(1000);
    for (i = 0; i <= 63; i++) {                // (scroll up)
      GLCD_command(GLCD_CS2 | GLCD_CS1, 0xC0 + i);
      Delay_ms(100);
    }
    GLCD_command(GLCD_CS2 | GLCD_CS1, 0xC0);
    Delay_ms(2000);
    Clear_screen();

    for (i = 0, x = 0, y = 0; i <= 7; i++, x += 4, y += 4) {  // (two)
      Rectangle(x, y, 63 - x, 63 - y);
      Rectangle(x, y + 64, 63 - x, 127 - y);
      Delay_ms(300);
    }
    Delay_ms(2000);
    Clear_screen();

    LCD_string(0xC0, "  (3) Circles   ");      // graphic show 3
    Rectangle(0, 0, 63, 127);
    Delay_ms(300);
    for (i = 7; i <= 63; i += 8) {
      Circle(31, 63, i);
      Delay_ms(300);
    }
    Delay_ms(1000);
    for (i = 63; i != 0; i--) {                // (scroll down)
      GLCD_command(GLCD_CS2 | GLCD_CS1, 0xC0 + i);
      Delay_ms(100);
    }
    GLCD_command(GLCD_CS2 | GLCD_CS1, 0xC0);
    Delay_ms(2000);
    Clear_screen();

    for (i = 3; i <= 31; i += 4) {             // (two)
      Circle(31, 31, i);
      Circle(31, 95, i);
      Delay_ms(300);
    }
    Delay_ms(2000);
    Clear_screen();

    LCD_string(0xC0, " (4) Sine Curve ");      // graphic show 4
    Line(32, 0, 32, 127);                      // (X axis)
    Line(29, 124, 32, 127);
    Line(35, 124, 32, 127);
    Line(31, 33, 33, 33);
    Line(31, 63, 33, 63);
    Line(31, 93, 33, 93);
    Line(31, 123, 33, 123);
    Line(0, 3, 63, 3);                         // (Y axis)
    Line(3, 0, 0, 3);
    Line(3, 6, 0, 3);
    for (i = 5; i <= 30; i += 5) {
      Sine(i);
      Delay_ms(300);
    }
    Delay_ms(2000);
    Clear_screen();

    LCD_string(0xC0, "(5) Cosine Curve");      // graphic show 5
    Line(32, 0, 32, 127);                      // (X axis)
    Line(29, 124, 32, 127);
    Line(35, 124, 32, 127);
    Line(31, 33, 33, 33);
    Line(31, 63, 33, 63);
    Line(31, 93, 33, 93);
    Line(31, 123, 33, 123);
    Line(0, 3, 63, 3);                         // (Y axis)
    Line(3, 0, 0, 3);
    Line(3, 6, 0, 3);
    for (i = 5; i <= 30; i += 5) {
      Cosine(i);
      Delay_ms(300);
    }
    Delay_ms(2000);
    Clear_screen();
  }
}
