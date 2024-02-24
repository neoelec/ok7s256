/* ========================================================================== */
/*              Xkit_test.c : Test Program for OK-7S256 Kit V1.0              */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <board.h>

#include <OK7S256gcc.h>
#include <OK7S256GLCD.h>
#include <OK7S256music.h>

void Test1()
{                                              /* graphic LCD test */
  unsigned int i, x, y;

  GLCD_string(0, 0, 1, "   OK-7S256  V1.0   "); // display text 1
  GLCD_string(1, 0, 0, "     2007/06/01     ");
  GLCD_string(2, 0, 0, "                    ");
  GLCD_string(3, 0, 0, "     Designed by    ");
  GLCD_string(4, 0, 0, "   Duck-Yong Yoon.  ");
  GLCD_string(5, 0, 0, "                    ");
  GLCD_string(6, 0, 0, "128 x 64 Graphic LCD");
  GLCD_string(7, 0, 0, " 6x8 Box, 5x7 ASCII ");
  Delay_ms(3000);

  GLCD_string(0, 0, 0, "===================="); // display text 2
  GLCD_string(1, 0, 0, "  ASCII Characters  ");
  GLCD_string(2, 0, 0, "====================");
  GLCD_string(7, 0, 0, "                    ");

  GLCD_xy(3, 0);
  for (i = 0x20; i < 0x7F; i++)                // from 0x20 to 0x7E
    GLCD_English(0, i);
  Delay_ms(3000);
  Clear_screen();

  LCD_string(0xC0, "   Rectangles   ");        // display graphic 1
  for (i = 0, x = 0, y = 0; i <= 7; i++, x += 4, y += 8) {
    Rectangle(x, y, 63 - x, 127 - y);
    Delay_ms(300);
  }
  Delay_ms(1000);
  Clear_screen();

  for (i = 0, x = 0, y = 0; i <= 7; i++, x += 4, y += 4) {  // display graphic 2
    Rectangle(x, y, 63 - x, 63 - y);
    Rectangle(x, y + 64, 63 - x, 127 - y);
    Delay_ms(300);
  }
  Delay_ms(1000);
  Clear_screen();

  LCD_string(0xC0, "    Circles     ");        // display graphic 3
  Rectangle(0, 0, 63, 127);
  Delay_ms(300);
  for (i = 7; i <= 63; i += 8) {
    Circle(31, 63, i);
    Delay_ms(300);
  }
  Delay_ms(1000);
  Clear_screen();

  for (i = 3; i <= 31; i += 4) {               // display graphic 4
    Circle(31, 31, i);
    Circle(31, 95, i);
    Delay_ms(300);
  }
  Delay_ms(1000);
  Clear_screen();
}

void Test2()
{                                              /* LED and buzzer test */
  unsigned int i;

  for (i = 0; i < 3; i++) {
    LCD_string(0xC0, "    LED1 on     ");      // LED1 on and buzzer sound
    LED_on(LED1);
    Beep();
    Delay_ms(1000);
    LED_off(LED1);
    LCD_string(0xC0, "    LED2 on     ");      // LED2 on and buzzer sound
    LED_on(LED2);
    Beep();
    Delay_ms(1000);
    LED_off(LED2);
  }
}

void Test3()
{                                              /* key input test */
  unsigned int i, key;

  for (i = 0; i < 800; i++) {                  // for 8 seconds
    key = Key_in();                            // input key
    if (key == 1) {                            // if KEY1, LED1 = on
      LED_on(LED1);
      LCD_string(0xC0, "   KEY1 is OK.  ");
    } else if (key == 2) {                     // if KEY2, LED2 = on
      LED_on(LED2);
      LCD_string(0xC0, "   KEY2 is OK.  ");
    } else if (key == 3) {                     // if KEY2/1, LED2/1 = on
      LED_on(LED2 | LED1);
      LCD_string(0xC0, "KEY2/KEY1 is OK.");
    } else {
      LED_off(LED2 | LED1);                    // if no key, LED2/1 = off
      LCD_string(0xC0, " Press KEY2/1 ! ");
    }
    Delay_ms(10);
  }
}

void Test4()
{                                              /* speaker sound test */
  Set_tempo(4);
  LCD_string(0xC0, " Do Re Mi Fa ...");        // play octave 4 forward
  Play_note(MIC, NOTE8);
  Play_note(MID, NOTE8);
  Play_note(MIE, NOTE8);
  Play_note(MIF, NOTE8);
  Play_note(MIG, NOTE8);
  Play_note(MIA, NOTE8);
  Play_note(MIB, NOTE8);
  Play_note(HIC, NOTE4);
  Play_rest(REST4);
  LCD_string(0xC0, " Do Si Ra Sol...");        // play octave 4 reverse
  Play_note(HIC, NOTE8);
  Play_note(MIB, NOTE8);
  Play_note(MIA, NOTE8);
  Play_note(MIG, NOTE8);
  Play_note(MIF, NOTE8);
  Play_note(MIE, NOTE8);
  Play_note(MID, NOTE8);
  Play_note(MIC, NOTE4);
}

void Test5()
{                                              /* PCK1 output test */
  AT91F_PWMC_CfgPMC();                         // enable clock of PWMC
  AT91F_PIO_CfgPeriph(AT91C_BASE_PIOA, 0, PCK1);  // PCK1 output on PA17

  LCD_string(0xC0, "TP3(Slow)=1024Hz");        // PCK1=Slow Clock/32=32.768kHz/32=1024Hz
  AT91F_PMC_EnablePCK(AT91C_BASE_PMC, 1, AT91C_PMC_PRES_CLK_32 | AT91C_PMC_CSS_SLOW_CLK);
  Delay_ms(3000);
  AT91F_PMC_DisablePCK(AT91C_BASE_PMC, AT91C_PMC_CSS_SLOW_CLK);

  LCD_string(0xC0, "TP3(Main)=576kHz");        // PCK1=Main Clock/32=18.432Hz/32=576kHz
  AT91F_PMC_EnablePCK(AT91C_BASE_PMC, 1, AT91C_PMC_PRES_CLK_32 | AT91C_PMC_CSS_MAIN_CLK);
  Delay_ms(3000);
  AT91F_PMC_DisablePCK(AT91C_BASE_PMC, AT91C_PMC_CSS_MAIN_CLK);

  LCD_string(0xC0, "TP3(PLL) = 6MHz ");        // PCK1=PLL Clock/32=192MHz/32=6MHz
  AT91F_PMC_EnablePCK(AT91C_BASE_PMC, 1, AT91C_PMC_PRES_CLK_32 | AT91C_PMC_CSS_PLL_CLK);
  Delay_ms(3000);
  AT91F_PMC_DisablePCK(AT91C_BASE_PMC, 1);
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

void Test6()
{                                              /* A/D converter test */
  unsigned int i, j, sum;

  AT91F_ADC_CfgPMC();                          // enable clock of ADC
  AT91F_ADC_SoftReset(AT91C_BASE_ADC);         // clear all previous settings
  AT91F_ADC_CfgModeReg(AT91C_BASE_ADC,         // 4.8MHz, 10-bit resolution
                       (2 << 24) | (2 << 16) | (4 << 8) | (0 << 5) | (0 << 4) | (0 << 1) | (0 << 0));

  for (i = 0; i < 40; i++) {
    AT91F_ADC_DisableChannel(AT91C_BASE_ADC, AT91C_ADC_CH5);
    AT91F_ADC_EnableChannel(AT91C_BASE_ADC, AT91C_ADC_CH4); // select CH4 for LM35DZ
    sum = 0;
    for (j = 0; j < 32; j++) {
      AT91F_ADC_StartConversion(AT91C_BASE_ADC);  // start conversion
      while (!(AT91F_ADC_GetStatus(AT91C_BASE_ADC) & AT91C_ADC_EOC4)) ; // wait for EOC
      sum += AT91F_ADC_GetConvertedDataCH4(AT91C_BASE_ADC); // add A/D result 32 times
      Delay_ms(1);
    }
    sum >>= 5;                                 // calculate average value
    LCD_command(0xC0);                         // display temperature for xx.x
    LCD_2d1((float)sum * 66. / 1024.);

    AT91F_ADC_DisableChannel(AT91C_BASE_ADC, AT91C_ADC_CH4);
    AT91F_ADC_EnableChannel(AT91C_BASE_ADC, AT91C_ADC_CH5); // select CH5 for VR1
    sum = 0;
    for (j = 0; j < 32; j++) {
      AT91F_ADC_StartConversion(AT91C_BASE_ADC);  // start conversion
      while (!(AT91F_ADC_GetStatus(AT91C_BASE_ADC) & AT91C_ADC_EOC5)) ; // wait for EOC
      sum += AT91F_ADC_GetConvertedDataCH5(AT91C_BASE_ADC); // add A/D result 32 times
      Delay_ms(1);
    }
    sum >>= 5;                                 // calculate average value
    LCD_command(0xC9);                         // display voltage for x.xx
    LCD_1d2((float)sum * 3.3 / 1024.);

    Delay_ms(250);                             // 10sec = 40 * 250ms
  }
}

void Test7()
{                                              /* USART0 RS-232C test */
  unsigned loopback;

  Delay_ms(2000);

  AT91F_US0_CfgPMC();                          // enable clock of USART0
  AT91F_PIO_CfgPeriph(AT91C_BASE_PIOA, AT91C_PA6_TXD0 | AT91C_PA5_RXD0, 0); // enable TXD0, RXD0
  AT91F_US_Configure(AT91C_BASE_US0, BOARD_MCK, 0x08C0, 115200, 0); // 115200 bps, 8 data, no parity, 1 stop
  AT91F_US_ResetTx(AT91C_BASE_US0);            // reset and enable USART0 transmitter
  AT91F_US_ResetRx(AT91C_BASE_US0);            // reset and enable USART0 receiver

  AT91F_US_PutChar(AT91C_BASE_US0, 0x11);      // loopback test 4 times
  Delay_ms(1);
  loopback = AT91F_US_GetChar(AT91C_BASE_US0) << 24;
  AT91F_US_PutChar(AT91C_BASE_US0, 0x22);
  Delay_ms(1);
  loopback += AT91F_US_GetChar(AT91C_BASE_US0) << 16;
  AT91F_US_PutChar(AT91C_BASE_US0, 0x33);
  Delay_ms(1);
  loopback += AT91F_US_GetChar(AT91C_BASE_US0) << 8;
  AT91F_US_PutChar(AT91C_BASE_US0, 0x44);
  Delay_ms(1);
  loopback += AT91F_US_GetChar(AT91C_BASE_US0);

  if (loopback == 0x11223344) {
    LCD_string(0xC0, "   USART0 OK!   ");      // display OK message
    Beep();
  } else {
    LCD_string(0xC0, "USART0 error !!!");      // display error message
    Error();
  }

  Delay_ms(3000);
}

int main(void)
{
  MCU_initialize();                            // initialize AT91SAM7S256 & kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module
  GLCD_clear();                                // initialize graphic LCD module
  cursor_flag = 0;

  LCD_string(0x80, " OK-7S256  V1.0 ");        // logo title 1
  LCD_string(0xC0, "D.Y.Yoon in 2007");

  Buzzer_on();                                 // buzzer on
  LED_on(LED1);                                // LED1 on
  Delay_ms(500);
  LED_off(LED1);                               // LED1 off
  LED_on(LED2);                                // LED2 on
  Delay_ms(500);
  LED_off(LED2);                               // LED2 off
  Buzzer_off();                                // buzzer off

  LCD_string(0x80, " OK-7S256  V1.0 ");        // logo title 2
  LCD_string(0xC0, "AT91SAM7S256 ARM");
  Delay_ms(2000);

  while (1) {
    LCD_string(0x80, "GRAPHIC LCD TEST");      // display test1
    LCD_string(0xC0, "  128 x 64 dot  ");      //   graphic LCD test
    Test1();

    LCD_string(0x80, "LED/BUZZER TEST ");      // display test2
    LCD_string(0xC0, "                ");      //   LED and buzzer test
    Test2();

    LCD_string(0x80, " KEY INPUT TEST ");      // display test3
    LCD_string(0xC0, " Press KEY2/1 ! ");      //   key input test
    Test3();

    LCD_string(0x80, "  SPEAKER TEST  ");      // display test4
    LCD_string(0xC0, "                ");      //   speaker sound test
    Test4();

    LCD_string(0x80, " CPU CLOCK TEST ");      // display test5
    LCD_string(0xC0, "                ");      //   PCK1 output test
    Test5();
    Beep();                                    // beep

    LCD_string(0x80, "    A/D TEST    ");      // display test6
    LCD_string(0xC0, "00.0[");                 //   A/D converter test
    LCD_data(0xDF);
    LCD_string(0xC6, "C] 0.00[V]");
    Test6();

    LCD_string(0x80, "  RS-232C TEST  ");      // display test7
    LCD_string(0xC0, " USART0 test... ");      //   USART0 RS-232C test
    Test7();
  }
}
