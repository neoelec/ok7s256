/* ========================================================================== */
/*          Xtest17_4.c : A/D Conversion of AD4(LM35DZ) and AD5(VR1)          */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <board.h>

#include <OK7S256gcc.h>

void LCD_2d1(float number)
{                                              /* floating-point number xx.x */
  unsigned int i, j;

  j = (int)(number + 0.5);
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

void LCD_1d2(float number)
{                                              /* floating-point number x.xx */
  unsigned int i, j;

  j = (int)(number + 0.5);
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

  LCD_string(0x80, "LM35 = 00.0 [");           // display title
  LCD_data(0xDF);
  LCD_string(0x8E, "C]");
  LCD_string(0xC0, " VR1 = 0.00 [V] ");
  Beep();

  AT91F_ADC_CfgPMC();                          // enable peripheral clock for ADC
  AT91F_ADC_SoftReset(AT91C_BASE_ADC);         // clear all previous ADC settings
  *AT91C_ADC_MR = 0x02020400;                  // SHTIM=2 (sample & hold time = 625ns)
  // STARTUP=2 (startup time = 5us)
  // 4.8MHz, 10 bit, software trigger

  while (1) {
    AT91F_ADC_DisableChannel(AT91C_BASE_ADC, AT91C_ADC_CH5);
    AT91F_ADC_EnableChannel(AT91C_BASE_ADC, AT91C_ADC_CH4); // select CH4 for LM35DZ
    sum = 0;
    for (i = 0; i < 10; i++) {
      AT91F_ADC_StartConversion(AT91C_BASE_ADC);  // start conversion
      while (!(AT91F_ADC_GetStatus(AT91C_BASE_ADC) & AT91C_ADC_EOC4)) ; // wait for EOC
      sum += AT91F_ADC_GetConvertedDataCH4(AT91C_BASE_ADC); // add A/D result 10 times
      Delay_ms(1);
    }
    LCD_command(0x87);                         // display temperature(xx.x)
    LCD_2d1((float)sum * 66. / 1024.);         // temperature = sum*66/1024

    AT91F_ADC_DisableChannel(AT91C_BASE_ADC, AT91C_ADC_CH4);
    AT91F_ADC_EnableChannel(AT91C_BASE_ADC, AT91C_ADC_CH5); // select CH5 for VR1
    sum = 0;
    for (i = 0; i < 100; i++) {
      AT91F_ADC_StartConversion(AT91C_BASE_ADC);  // start conversion
      while (!(AT91F_ADC_GetStatus(AT91C_BASE_ADC) & AT91C_ADC_EOC5)) ; // wait for EOC
      sum += AT91F_ADC_GetConvertedDataCH5(AT91C_BASE_ADC); // add A/D result 100 times
      Delay_ms(1);
    }
    LCD_command(0xC7);                         // display voltage(x.xx)
    LCD_1d2((float)sum * 3.3 / 1024.);         // voltage = sum*3.3/1024

    Delay_ms(250);                             // delay 250 ms
  }
}
