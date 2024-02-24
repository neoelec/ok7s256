/* ========================================================================== */
/*                Xtest04_2.c : User-Defined Character Display                */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <board.h>

#include <OK7S256gcc.h>

void Set_font(void)
{                                              /* set user character font */
  unsigned int i;
  unsigned int font[] = {
    0x10, 0x18, 0x1C, 0x1E, 0x1C, 0x18, 0x10, 0x00, // character 0x00
    0x0F, 0x09, 0x09, 0x09, 0x09, 0x09, 0x0F, 0x00, // character 0x01
    0x08, 0x08, 0x08, 0x0E, 0x08, 0x08, 0x08, 0x00, // character 0x02
    0x01, 0x02, 0x04, 0x08, 0x00, 0x00, 0x0F, 0x00, // character 0x03
    0x10, 0x08, 0x04, 0x02, 0x00, 0x00, 0x1E, 0x00, // character 0x04
    0x0F, 0x08, 0x08, 0x0F, 0x08, 0x08, 0x0F, 0x00, // character 0x05
    0x04, 0x04, 0x04, 0x1C, 0x04, 0x04, 0x04, 0x00, // character 0x06
    0x01, 0x03, 0x07, 0x0F, 0x07, 0x03, 0x01, 0x00
  };                                           // character 0x07

  LCD_command(0x40);                           // set CG RAM address
  for (i = 0; i < 64; i++)                     // download font data
    LCD_data(font[i]);
}

int main(void)
{
  MCU_initialize();                            // initialize AT91SAM7S256 & kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD

  Set_font();                                  // set user character font

  while (1) {
    Beep();
    LCD_command(0x80);                         // display logo
    LCD_data(0x00);
    LCD_string(0x81, " OK-7S256 KIT ");
    LCD_data(0x07);
    LCD_string(0xC0, " AT91SAM ");             // display message 1
    LCD_data(0x01);
    LCD_data(0x02);
    LCD_data(0x03);
    LCD_data(0x04);
    LCD_data(0x05);
    LCD_data(0x06);
    LCD_data(' ');
    Delay_ms(2000);
    LCD_string(0xC0, "   2007/06/01   ");      // display message 2
    Delay_ms(2000);
    LCD_string(0xC0, " DUCK-YONG YOON ");      // display message 3
    Delay_ms(2000);
  }
}
