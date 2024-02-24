/* ========================================================================== */
/*             Xtest03_5.c : Test Time-Delay Function by Software             */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <board.h>

#include <OK7S256gcc.h>

int main(void)
{
  unsigned int i;

  MCU_initialize();                            // initialize AT91SAM7S256 & kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module

  LCD_string(0x80, " S/W Time Delay ");        // display title

  LED_off(LED2 | LED1);                        // LED2~LED1 off

  while (1) {
    LCD_string(0xC0, " 1us delay test ");      // output pulse by 1us delay
    Beep();
    for (i = 0; i < 5000000; i++) {
      LED_on(LED2);                            // LED2 on
      Delay_1us();
      LED_off(LED2);                           // LED2 off
      Delay_1us();
    }

    LCD_string(0xC0, " 10us delay test");      // output pulse by 10us delay
    Beep();
    for (i = 0; i < 500000; i++) {
      LED_on(LED2);                            // LED2 on
      Delay_us(10);
      LED_off(LED2);                           // LED2 off
      Delay_us(10);
    }

    LCD_string(0xC0, "100us delay test");      // output pulse by 100us delay
    Beep();
    for (i = 0; i < 50000; i++) {
      LED_on(LED2);                            // LED2 on
      Delay_us(100);
      LED_off(LED2);                           // LED2 off
      Delay_us(100);
    }

    LCD_string(0xC0, "500us delay test");      // output pulse by 500us delay
    Beep();
    for (i = 0; i < 10000; i++) {
      LED_on(LED2);                            // LED2 on
      Delay_us(500);
      LED_off(LED2);                           // LED2 off
      Delay_us(500);
    }

    LCD_string(0xC0, " 10ms delay test");      // output pulse by 10ms delay
    Beep();
    for (i = 0; i < 500; i++) {
      LED_on(LED2);                            // LED2 on
      Delay_ms(10);
      LED_off(LED2);                           // LED2 off
      Delay_ms(10);
    }

    LCD_string(0xC0, "100ms delay test");      // output pulse by 100ms delay
    Beep();
    for (i = 0; i < 50; i++) {
      LED_on(LED2);                            // LED2 on
      Delay_ms(100);
      LED_off(LED2);                           // LED2 off
      Delay_ms(100);
    }

    LCD_string(0xC0, "500ms delay test");      // output pulse by 500ms delay
    Beep();
    for (i = 0; i < 10; i++) {
      LED_on(LED2);                            // LED2 on
      Delay_ms(500);
      LED_off(LED2);                           // LED2 off
      Delay_ms(500);
    }
  }
}
