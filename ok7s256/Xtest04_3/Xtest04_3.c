/* ========================================================================== */
/*                    Xtest04_3.c : Integer Number Display                    */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <board.h>

#include <OK7S256gcc.h>

void LCD_4hex(unsigned int number)
{                                              /* display 4-digit hex number */
  unsigned int i;

  i = (number >> 12) & 0x0000000F;             // 16^3
  if (i <= 9)
    LCD_data(i + '0');
  else
    LCD_data(i - 10 + 'A');

  i = (number >> 8) & 0x0000000F;              // 16^2
  if (i <= 9)
    LCD_data(i + '0');
  else
    LCD_data(i - 10 + 'A');

  i = (number >> 4) & 0x0000000F;              // 16^1
  if (i <= 9)
    LCD_data(i + '0');
  else
    LCD_data(i - 10 + 'A');

  i = number & 0x0000000F;                     // 16^0
  if (i <= 9)
    LCD_data(i + '0');
  else
    LCD_data(i - 10 + 'A');
}

void LCD_5d(unsigned int number)
{                                              /* display 5-digit decimal number */
  unsigned int i, flag;

  flag = 0;
  i = number / 10000;                          // 10^4
  if (i == 0)
    LCD_data(' ');
  else {
    LCD_data(i + '0');
    flag = 1;
  }

  number = number % 10000;                     // 10^3
  i = number / 1000;
  if ((i == 0) && (flag == 0))
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

void LCD_16bin(unsigned int number)
{                                              /* display 16-bit binary number */
  LCD_data(((number >> 15) & 0x00000001) + '0');  // 2^15
  LCD_data(((number >> 14) & 0x00000001) + '0');  // 2^14
  LCD_data(((number >> 13) & 0x00000001) + '0');  // 2^13
  LCD_data(((number >> 12) & 0x00000001) + '0');  // 2^12
  LCD_data(((number >> 11) & 0x00000001) + '0');  // 2^11
  LCD_data(((number >> 10) & 0x00000001) + '0');  // 2^10
  LCD_data(((number >> 9) & 0x00000001) + '0'); // 2^9
  LCD_data(((number >> 8) & 0x00000001) + '0'); // 2^8
  LCD_data(((number >> 7) & 0x00000001) + '0'); // 2^7
  LCD_data(((number >> 6) & 0x00000001) + '0'); // 2^6
  LCD_data(((number >> 5) & 0x00000001) + '0'); // 2^5
  LCD_data(((number >> 4) & 0x00000001) + '0'); // 2^4
  LCD_data(((number >> 3) & 0x00000001) + '0'); // 2^3
  LCD_data(((number >> 2) & 0x00000001) + '0'); // 2^2
  LCD_data(((number >> 1) & 0x00000001) + '0'); // 2^1
  LCD_data((number & 0x00000001) + '0');       // 2^0
}

int main(void)
{
  unsigned int i;

  MCU_initialize();                            // initialize AT91SAM7S256 & kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD

  while (1) {
    LCD_string(0x80, "0x0000 = 00000 =");      // display 16-bit integer number
    LCD_string(0xC0, "0000000000000000");
    Beep();

    for (i = 1; i <= 0xFFFF; i++) {            // integer number from 1 to 65535
      LCD_command(0x82);                       // display hexadecimal number
      LCD_4hex(i);
      LCD_command(0x89);                       // display decimal number
      LCD_5d(i);
      LCD_command(0xC0);                       // display binary number
      LCD_16bin(i);
      Delay_ms(500);
    }
  }
}
