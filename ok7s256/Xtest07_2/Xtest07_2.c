/* ========================================================================== */
/*                Xtest07_2.c : Integer Number Display on GLCD                */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <board.h>

#include <OK7S256gcc.h>
#include <OK7S256Korean.h>

void GLCD_2hex(unsigned int number)
{                                              /* display 2-digit hex number */
  unsigned int i;

  i = (number >> 4) & 0x0000000F;              // 16^1
  if (i <= 9)
    GLCD_English(0, i + '0');
  else
    GLCD_English(0, i - 10 + 'A');

  i = number & 0x0000000F;                     // 16^0
  if (i <= 9)
    GLCD_English(0, i + '0');
  else
    GLCD_English(0, i - 10 + 'A');
}

void GLCD_3d(unsigned int number)
{                                              /* display 3-digit decimal number */
  unsigned int i, flag;

  flag = 0;
  i = number / 100;                            // 10^2
  if (i == 0)
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

void GLCD_8bin(unsigned int number)
{                                              /* display 8-bit binary number */
  GLCD_English(0, ((number >> 7) & 0x00000001) + '0');  // 2^7
  GLCD_English(0, ((number >> 6) & 0x00000001) + '0');  // 2^6
  GLCD_English(0, ((number >> 5) & 0x00000001) + '0');  // 2^5
  GLCD_English(0, ((number >> 4) & 0x00000001) + '0');  // 2^4
  GLCD_English(0, ((number >> 3) & 0x00000001) + '0');  // 2^3
  GLCD_English(0, ((number >> 2) & 0x00000001) + '0');  // 2^2
  GLCD_English(0, ((number >> 1) & 0x00000001) + '0');  // 2^1
  GLCD_English(0, (number & 0x00000001) + '0'); // 2^0
}

int main(void)
{
  unsigned int i;

  MCU_initialize();                            // initialize AT91SAM7S256 & kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD
  GLCD_clear();                                // initialize GLCD screen

  LCD_string(0x80, "Graphic LCD Test");        // display title on text LCD
  LCD_string(0xC0, " Integer Number ");

  while (1) {
    Beep();
    GLCD_string(0, 0, 0, " ** 정수표시 ** "); // display 8 bit integer
    GLCD_string(1, 0, 0, "16진수= 0x00    ");
    GLCD_string(2, 0, 0, "10진수= 000     ");
    GLCD_string(3, 0, 0, " 2진수= 00000000");

    for (i = 1; i <= 255; i++) {
      GLCD_xy(1, 10);                          // (display hex)
      GLCD_2hex(i);
      GLCD_xy(2, 8);                           // (display decimal)
      GLCD_3d(i);
      GLCD_xy(3, 8);                           // (display binary)
      GLCD_8bin(i);
      Delay_ms(500);
    }
  }
}
