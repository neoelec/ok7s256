/* ========================================================================== */
/*     Xtest07_3.c : Integer Number Display without and with Sign on GLCD     */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <stdlib.h>
#include <board.h>

#include <OK7S256gcc.h>
#include <OK7S256Korean.h>

void GLCD_2d(unsigned int number)
{                                              /* display 2-digit decimal number */
  unsigned int i;

  i = number / 10;                             // 10^1
  if (i == 0)
    GLCD_English(0, ' ');
  else
    GLCD_English(0, i + '0');

  i = number % 10;                             // 10^0
  GLCD_English(0, i + '0');
}

void GLCD_s2d(signed int number)
{                                              /* display signed 2-digit decimal number */
  if (number >= 0)                             // sign
    GLCD_English(0, '+');
  else
    GLCD_English(0, '-');

  GLCD_2d(abs(number));                        // magnitude
}

void GLCD_4d(unsigned int number)
{                                              /* display 4-digit decimal number */
  unsigned int i, flag;

  flag = 0;
  i = number / 1000;                           // 10^3
  if (i == 0)
    GLCD_English(0, ' ');
  else {
    GLCD_English(0, i + '0');
    flag = 1;
  }

  number = number % 1000;                      // 10^2
  i = number / 100;
  if ((i == 0) && (flag == 0))
    GLCD_English(0, ' ');
  else {
    GLCD_English(0, i + '0');
    flag = 1;
  }

  number = number % 100;                       // 10^1
  i = number / 10;
  if ((i == 0) && (flag == 0))
    GLCD_English(0, ' ');
  else {
    GLCD_English(0, i + '0');
    flag = 1;
  }

  i = number % 10;                             // 10^0
  GLCD_English(0, i + '0');
}

void GLCD_s4d(signed int number)
{                                              /* display signed 4-digit decimal number */
  if (number >= 0)                             // sign
    GLCD_English(0, '+');
  else
    GLCD_English(0, '-');

  GLCD_4d(abs(number));                        // magnitude
}

int main(void)
{
  unsigned int i, j;
  signed int x, y;

  MCU_initialize();                            // initialize AT91SAM7S256 & kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD
  GLCD_clear();                                // initialize GLCD screen

  LCD_string(0x80, "Graphic LCD Test");        // display title on text LCD
  LCD_string(0xC0, " Integer Number ");

  while (1) {
    GLCD_string(0, 0, 1, " 부호 없는 정수 "); // multiplication without sign
    GLCD_string(1, 0, 0, " 00 x 00 = 0000 ");
    GLCD_string(2, 0, 1, " 부호 있는 정수 "); // multiplication with sign
    GLCD_string(3, 0, 0, "+00x(+00)= +0000");

    Beep();
    for (i = 10; i <= 90; i += 10)             // multiplication without sign
      for (j = 10; j <= 90; j += 10) {
        GLCD_xy(1, 1);
        GLCD_2d(i);                            // display multiplicand
        GLCD_xy(1, 6);
        GLCD_2d(j);                            // display multiplier
        GLCD_xy(1, 11);
        GLCD_4d(i * j);                        // display multiplication
        Delay_ms(1000);
      }

    Beep();
    for (x = -90; x <= +90; x += 10)           // multiplication with sign
      for (y = -90; y <= +90; y += 10) {
        GLCD_xy(3, 0);
        GLCD_s2d(x);                           // display multiplicand
        GLCD_xy(3, 5);
        GLCD_s2d(y);                           // display multiplier
        GLCD_xy(3, 11);
        GLCD_s4d(x * y);                       // display multiplication
        Delay_ms(1000);
      }
  }
}
