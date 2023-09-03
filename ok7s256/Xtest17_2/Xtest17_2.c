/* ========================================================================== */
/*             Xtest17_2.c : A/D Conversion of AD5 Input for VR1              */
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

void LCD_1d2(float number)
{                                              /* floating-point number x.xx */
  unsigned int i, j;

  j = (int)(number * 100. + 0.5);
  i = j / 100;                                 // 10^0
  LCD_data(i + '0');
  LCD_data('.');

  j = j % 100;                                 // 10^-1
  i = j / 10;
  LCD_data(i + '0');

  i = j % 10;                                  // 10^-2
  LCD_data(i + '0');
}

int main(void)
{
  unsigned int i, sum;

  MCU_initialize();                            // initialize AT91SAM7S256 & kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module

  LCD_string(0x80, "    AD5(VR1)    ");        // display title
  LCD_string(0xC0, "0x0000 = 0.00[V]");
  Beep();

  AT91F_ADC_CfgPMC();                          // enable peripheral clock for ADC
  AT91F_ADC_SoftReset(AT91C_BASE_ADC);         // clear all previous ADC settings
  *AT91C_ADC_MR = 0x02020400;                  // SHTIM=2 (sample & hold time = 625ns)
  // STARTUP=2 (startup time = 5us)
  // 4.8MHz, 10 bit, software trigger
  AT91F_ADC_EnableChannel(AT91C_BASE_ADC, AT91C_ADC_CH5); // select CH5 for VR1

  while (1) {
    sum = 0;
    for (i = 0; i < 32; i++) {
      AT91F_ADC_StartConversion(AT91C_BASE_ADC);  // start conversion
      while (!(AT91F_ADC_GetStatus(AT91C_BASE_ADC) & AT91C_ADC_EOC5)) ; // wait for EOC
      sum += AT91F_ADC_GetConvertedDataCH5(AT91C_BASE_ADC); // add A/D result 32 times
      Delay_ms(1);
    }
    sum >>= 5;                                 // divide sum by 32 for average value

    LCD_command(0xC2);                         // display in HEX
    LCD_4hex(sum);
    LCD_command(0xC9);                         // display voltage(x.xx)
    LCD_1d2((float)sum * 3.3 / 1024.);         // voltage = sum*3.3/1024

    Delay_ms(250);                             // delay 250 ms
  }
}
