/* ========================================================================== */
/*             Xtest03_5.c : Test Time-Delay Function by Software             */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */
/*                                       Modified by Raccoon's Cave in 2023.  */

#include <board.h>
/* - */
#include <lcd.h>
#include <rstc/rstc.h>
#include <utility/buzzer.h>
#include <utility/delay.h>
#include <utility/led.h>

static void __LED_Configure(void)
{
    LED_Configure(0);
    LED_Configure(1);
}

int main(void)
{
    unsigned int i;

    RSTC_ConfigureMode(AT91C_RSTC_URSTEN);
    BUZZER_Configure(1);
    LCD_Configure(16, 2, LCD_5x8DOTS);
    __LED_Configure();

    LCD_PutStringAt(0, 0, " S/W Time Delay "); // display title

    while (1) {
        LCD_PutStringAt(0, 1, " 1us delay test ");  // output pulse by 1us delay
        BUZZER_Beep();
        for (i = 0; i < 5000000; i++) {
            LED_Set(1);                        // LED2 on
            DELAY_1us();
            LED_Clear(1);                      // LED2 off
            DELAY_1us();
        }

        LCD_PutStringAt(0, 1, " 10us delay test");  // output pulse by 10us delay
        BUZZER_Beep();
        for (i = 0; i < 500000; i++) {
            LED_Set(1);                        // LED2 on
            DELAY_us(10);
            LED_Clear(1);                      // LED2 off
            DELAY_us(10);
        }

        LCD_PutStringAt(0, 1, "100us delay test");  // output pulse by 100us delay
        BUZZER_Beep();
        for (i = 0; i < 50000; i++) {
            LED_Set(1);                        // LED2 on
            DELAY_us(100);
            LED_Clear(1);                      // LED2 off
            DELAY_us(100);
        }

        LCD_PutStringAt(0, 1, "500us delay test");  // output pulse by 500us delay
        BUZZER_Beep();
        for (i = 0; i < 10000; i++) {
            LED_Set(1);                        // LED2 on
            DELAY_us(500);
            LED_Clear(1);                      // LED2 off
            DELAY_us(500);
        }

        LCD_PutStringAt(0, 1, " 10ms delay test");  // output pulse by 10ms delay
        BUZZER_Beep();
        for (i = 0; i < 500; i++) {
            LED_Set(1);                        // LED2 on
            DELAY_ms(10);
            LED_Clear(1);                      // LED2 off
            DELAY_ms(10);
        }

        LCD_PutStringAt(0, 1, "100ms delay test");  // output pulse by 100ms delay
        BUZZER_Beep();
        for (i = 0; i < 50; i++) {
            LED_Set(1);                        // LED2 on
            DELAY_ms(100);
            LED_Clear(1);                      // LED2 off
            DELAY_ms(100);
        }

        LCD_PutStringAt(0, 1, "500ms delay test");  // output pulse by 500ms delay
        BUZZER_Beep();
        for (i = 0; i < 10; i++) {
            LED_Set(1);                        // LED2 on
            DELAY_ms(500);
            LED_Clear(1);                      // LED2 off
            DELAY_ms(500);
        }
    }
}
