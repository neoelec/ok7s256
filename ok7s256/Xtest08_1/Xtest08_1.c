/* ========================================================================== */
/*              Xtest08_1.c : Key Input Count without Debouncing              */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <board.h>

#include <OK7S256gcc.h>

void LCD_3d(unsigned int number)
{                                              /* display 3-digit decimal number */
  unsigned int i, flag;

  flag = 0;
  i = number / 100;                            // 10^2
  if (i == 0)
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

int main(void)
{
  unsigned int key1 = 0, key2 = 0;

  MCU_initialize();                            // initialize AT91SAM7S256 & kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD

  LCD_string(0x80, "   KEY1 = 000   ");        // display title on text LCD
  LCD_string(0xC0, "   KEY2 = 000   ");
  Beep();

  while (1) {
    switch (Key_in()) {                        // key input without debouncing
    case 0x01:
      key1++;                                  // if key1, display KEY1 count
      if (key1 > 999)
        key1 = 0;
      LCD_command(0x8A);
      LCD_3d(key1);
      break;
    case 0x02:
      key2++;                                  // if key2, display KEY2 count
      if (key2 > 999)
        key2 = 0;
      LCD_command(0xCA);
      LCD_3d(key2);
      break;
    default:
      break;
    }
  }
}
