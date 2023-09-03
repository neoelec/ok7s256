/* ========================================================================== */
/*         Xtest04_4.c : Integer Number Display without and with Sign         */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <stdlib.h>
#include <board.h>

#include <OK7S256gcc.h>

void LCD_2d(unsigned int number)
{                                              /* display 2-digit decimal number */
  unsigned char i;

  i = number / 10;                             // 10^1
  if (i == 0)
    LCD_data(' ');
  else
    LCD_data(i + '0');

  i = number % 10;                             // 10^0
  LCD_data(i + '0');
}

void LCD_s2d(signed int number)
{                                              /* display signed 2-digit decimal number */
  if (number >= 0)                             // sign
    LCD_data('+');
  else
    LCD_data('-');

  LCD_2d(abs(number));                         // magnitude
}

void LCD_4d(unsigned int number)
{                                              /* display 4-digit decimal number */
  unsigned int i, flag;

  flag = 0;
  i = number / 1000;                           // 10^3
  if (i == 0)
    LCD_data(' ');
  else {
    LCD_data(i + '0');
    flag = 1;
  }

  number = number % 1000;                      // 10^2
  i = number / 100;
  if ((i == 0) && (flag == 0))
    LCD_data(' ');
  else {
    LCD_data(i + '0');
    flag = 1;
  }

  number = number % 100;                       // 10^1
  i = number / 10;
  if ((i == 0) && (flag == 0))
    LCD_data(' ');
  else {
    LCD_data(i + '0');
    flag = 1;
  }

  i = number % 10;                             // 10^0
  LCD_data(i + '0');
}

void LCD_s4d(signed int number)
{                                              /* display signed 4-digit decimal number */
  if (number >= 0)                             // sign
    LCD_data('+');
  else
    LCD_data('-');

  LCD_4d(abs(number));                         // magnitude
}

int main(void)
{
  unsigned int i, j;
  signed int x, y;

  MCU_initialize();                            // initialize AT91SAM7S256 & kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD

  while (1) {
    LCD_string(0x80, " UNSIGNED MULTI ");      // multiplication without sign
    LCD_string(0xC0, " 00 x 00 = 0000 ");
    Beep();

    for (i = 10; i <= 90; i += 10)
      for (j = 10; j <= 90; j += 10) {
        LCD_command(0xC1);
        LCD_2d(i);                             // display multiplicand
        LCD_command(0xC6);
        LCD_2d(j);                             // display multiplier
        LCD_command(0xCB);
        LCD_4d(i * j);                         // display multiplication
        Delay_ms(1000);
      }

    LCD_string(0x80, "  SIGNED MULTI  ");      // multiplication with sign
    LCD_string(0xC0, "+00x(+00)= +0000");
    Beep();

    for (x = -90; x <= +90; x += 10)
      for (y = -90; y <= +90; y += 10) {
        LCD_command(0xC0);
        LCD_s2d(x);                            // display multiplicand
        LCD_command(0xC5);
        LCD_s2d(y);                            // display multiplier
        LCD_command(0xCB);
        LCD_s4d(x * y);                        // display multiplication
        Delay_ms(1000);
      }
  }
}
