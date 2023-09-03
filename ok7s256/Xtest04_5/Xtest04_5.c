/* ========================================================================== */
/*          Xtest04_5.c : Real Number Display without and with Sign           */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <math.h>
#include <board.h>

#include <OK7S256gcc.h>

void LCD_1d1(double number)
{                                              /* floating-point number x.x */
  unsigned int i, j;

  j = (int)(number * 10. + 0.5);
  i = j / 10;                                  // 10^0
  LCD_data(i + '0');
  LCD_data('.');
  i = j % 10;                                  // 10^-1
  LCD_data(i + '0');
}

void LCD_s1d1(double number)
{                                              /* floating-point number +x.x */
  if (number >= 0.)                            // sign
    LCD_data('+');
  else
    LCD_data('-');

  LCD_1d1(fabs(number));                       // magnitude
}

void LCD_2d2(double number)
{                                              /* floating-point number xx.xx */
  unsigned int i, j;

  j = (int)(number * 100. + 0.5);
  i = j / 1000;                                // 10^1
  if (i == 0)
    LCD_data(' ');
  else
    LCD_data(i + '0');

  j = j % 1000;                                // 10^0
  i = j / 100;
  LCD_data(i + '0');
  LCD_data('.');

  j = j % 100;                                 // 10^-1
  i = j / 10;
  LCD_data(i + '0');

  i = j % 10;                                  // 10^-2
  LCD_data(i + '0');
}

void LCD_s2d2(double number)
{                                              /* floating-point number +xx.xx */
  if (number >= 0.)                            // sign
    LCD_data('+');
  else
    LCD_data('-');

  LCD_2d2(fabs(number));                       // magnitude
}

int main(void)
{
  double i, j;
  double x, y;

  MCU_initialize();                            // initialize AT91SAM7S256 & kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD

  while (1) {
    LCD_string(0x80, "  FLOAT NUMBER  ");      // multipllication without sign
    LCD_string(0xC0, "0.0 x 0.0 =00.00");
    Beep();

    for (i = 1.1; i <= 9.9; i += 1.1) {
      for (j = 1.1; j <= 9.9; j += 1.1) {
        LCD_command(0xC0);
        LCD_1d1(i);                            // display multiplicand
        LCD_command(0xC6);
        LCD_1d1(j);                            // display multiplier
        LCD_command(0xCB);
        LCD_2d2(i * j);                        // display multiplication
        Delay_ms(1000);
      }
    }

    LCD_string(0x80, " (+0.0)x(+0.0)  ");      // multiplication with sign
    LCD_string(0xC0, "   = +00.00     ");
    Beep();

    for (x = -9.9; x <= 9.9; x += 1.1) {
      for (y = -9.9; y <= 9.9; y += 1.1) {
        LCD_command(0x82);
        LCD_s1d1(x);                           // display multiplicand
        LCD_command(0x89);
        LCD_s1d1(y);                           // display multiplier
        LCD_command(0xC5);
        LCD_s2d2(x * y);                       // display multiplication
        Delay_ms(1000);
      }
    }
  }
}
