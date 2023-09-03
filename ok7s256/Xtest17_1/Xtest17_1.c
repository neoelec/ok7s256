/* ========================================================================== */
/*            Xtest17_1.c : A/D Conversion of AD4 Input for LM35DZ            */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <board.h>

#include <OK7S256gcc.h>

void LCD_4hex(unsigned int number)
{                                              /* display 4-digit hex number */
  unsigned int i;

  i = number >> 12;                            // 16^3
  if (i <= 9)
    LCD_data(i + '0');
  else
    LCD_data(i - 10 + 'A');

  i = (number >> 8) & 0x000F;                  // 16^2
  if (i <= 9)
    LCD_data(i + '0');
  else
    LCD_data(i - 10 + 'A');

  i = (number >> 4) & 0x000F;                  // 16^1
  if (i <= 9)
    LCD_data(i + '0');
  else
    LCD_data(i - 10 + 'A');

  i = number & 0x000F;                         // 16^0
  if (i <= 9)
    LCD_data(i + '0');
  else
    LCD_data(i - 10 + 'A');
}

void LCD_2d1(float number)
{                                              /* floating-point number xx.x */
  unsigned int i, j;

  j = (int)(number * 10. + 0.5);
  i = j / 100;                                 // 10^1
  if (i == 0)
    LCD_data(' ');
  else
    LCD_data(i + '0');

  j = j % 100;                                 // 10^0
  i = j / 10;
  LCD_data(i + '0');
  LCD_data('.');

  i = j % 10;                                  // 10^-1
  LCD_data(i + '0');
}

int main(void)
{
  unsigned int i, sum;

  MCU_initialize();                            // initialize AT91SAM7S256 & kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module

  LCD_string(0x80, "   AD4(LM35DZ)  ");        // display title
  LCD_string(0xC0, "0x0000 = 00.0 ");
  LCD_data(0xDF);
  LCD_data('C');
  Beep();

  AT91F_ADC_CfgPMC();                          // enable peripheral clock for ADC
  AT91F_ADC_SoftReset(AT91C_BASE_ADC);         // clear all previous ADC settings
  *AT91C_ADC_MR = 0x02020400;                  // SHTIM=2 (sample & hold time = 625ns)
  // STARTUP=2 (startup time = 5us)
  // 4.8MHz, 10 bit, software trigger
  AT91F_ADC_EnableChannel(AT91C_BASE_ADC, AT91C_ADC_CH4); // select CH4 for LM35DZ

  while (1) {
    sum = 0;
    for (i = 0; i < 32; i++) {
      AT91F_ADC_StartConversion(AT91C_BASE_ADC);  // start conversion
      while (!(AT91F_ADC_GetStatus(AT91C_BASE_ADC) & AT91C_ADC_EOC4)) ; // wait for EOC
      sum += AT91F_ADC_GetConvertedDataCH4(AT91C_BASE_ADC); // add A/D result 32 times
      Delay_ms(1);
    }
    sum >>= 5;                                 // divide sum by 32 for average value

    LCD_command(0xC2);                         // display in HEX
    LCD_4hex(sum);
    LCD_command(0xC9);                         // display temperature(xx.x)
    LCD_2d1((float)sum * 66. / 1024.);         // temperature = sum*66/1024

    Delay_ms(250);                             // delay 250 ms
  }
}
