/* ========================================================================== */
/*      Xtest07_4.c : Real Number Display without and with Sign on GLCD       */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <math.h>
#include <board.h>

#include <OK7S256gcc.h>
#include <OK7S256Korean.h>

void GLCD_1d1(double number)
{                                              /* floating-point number x.x */
  unsigned int i, j;

  j = (int)(number * 10. + 0.5);
  i = j / 10;                                  // 10^0
  GLCD_English(0, i + '0');
  GLCD_English(0, '.');
  i = j % 10;                                  // 10^-1
  GLCD_English(0, i + '0');
}

void GLCD_s1d1(double number)
{                                              /* floating-point number +x.x */
  if (number >= 0.)                            // sign
    GLCD_English(0, '+');
  else
    GLCD_English(0, '-');

  GLCD_1d1(fabs(number));                      // magnitude
}

void GLCD_2d2(double number)
{                                              /* floating-point number xx.xx */
  unsigned int i, j;

  j = (int)(number * 100. + 0.5);
  i = j / 1000;                                // 10^1
  if (i == 0)
    GLCD_English(0, ' ');
  else
    GLCD_English(0, i + '0');

  j = j % 1000;                                // 10^0
  i = j / 100;
  GLCD_English(0, i + '0');
  GLCD_English(0, '.');

  j = j % 100;                                 // 10^-1
  i = j / 10;
  GLCD_English(0, i + '0');

  i = j % 10;                                  // 10^-2
  GLCD_English(0, i + '0');
}

void GLCD_s2d2(double number)
{                                              /* floating-point number +xx.xx */
  if (number >= 0.)                            // sign
    GLCD_English(0, '+');
  else
    GLCD_English(0, '-');

  GLCD_2d2(fabs(number));                      // magnitude
}

int main(void)
{
  double i, j;
  double x, y;

  MCU_initialize();                            // initialize AT91SAM7S256 & kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD
  GLCD_clear();                                // initialize GLCD screen

  LCD_string(0x80, "Graphic LCD Test");        // display title on text LCD
  LCD_string(0xC0, "  Real Number   ");

  while (1) {
    GLCD_string(0, 0, 1, " 부호 없는 실수 "); // multiplication without sign
    GLCD_string(1, 0, 0, "                ");
    GLCD_string(2, 0, 0, "0.0 x 0.0 =00.00");
    GLCD_string(3, 0, 0, "                ");

    Beep();
    for (i = 1.1; i <= 9.9; i += 1.1)          // multiplication without sign
      for (j = 1.1; j <= 9.9; j += 1.1) {
        GLCD_xy(2, 0);
        GLCD_1d1(i);                           // display multiplicand
        GLCD_xy(2, 6);
        GLCD_1d1(j);                           // display multiplier
        GLCD_xy(2, 11);
        GLCD_2d2(i * j);                       // display multiplication
        Delay_ms(1000);
      }

    GLCD_string(0, 0, 1, " 부호 있는 실수 "); // multiplication with sign
    GLCD_string(1, 0, 0, "                ");
    GLCD_string(2, 0, 0, " (+0.0)x(+0.0)  ");
    GLCD_string(3, 0, 0, "   = +00.00     ");

    Beep();
    for (x = -9.9; x <= +9.9; x += 1.1)        // multiplication with sign
      for (y = -9.9; y <= +9.9; y += 1.1) {
        GLCD_xy(2, 2);
        GLCD_s1d1(x);                          // display multiplicand
        GLCD_xy(2, 9);
        GLCD_s1d1(y);                          // display multiplier
        GLCD_xy(3, 5);
        GLCD_s2d2(x * y);                      // display multiplication
        Delay_ms(1000);
      }
  }
}
