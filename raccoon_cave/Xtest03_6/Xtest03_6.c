/* ========================================================================== */
/*             Xtest03_6.c : Test Time-Delay Function by Hardware             */
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
#include <utility/tick.h>

static void HW_DELAY_ms(unsigned int ms)
{
    unsigned int timestamp, current;

    if (ms == 0)
        return;

    timestamp = TICK_GetTimestamp();
    do {
        current = TICK_GetTimestamp();
    } while ((current - timestamp) < ms);
}

static void __LED_Configure(void)
{
    LED_Configure(0);
    LED_Configure(1);
}

int main(void)
{
    unsigned int i;

    RSTC_ConfigureMode(AT91C_RSTC_URSTEN);
    TICK_Configure();
    BUZZER_Configure(1);
    LCD_Configure(16, 2, LCD_5x8DOTS);
    __LED_Configure();

    LCD_PutStringAt(0, 0, " H/W Time Delay "); // display title

    while (1) {
        LCD_PutStringAt(0, 1, " 10ms delay test");  // output pulse by 10ms delay
        BUZZER_Beep();
        for (i = 0; i < 500; i++) {
            LED_Set(1);                        // LED2 on
            HW_DELAY_ms(10);
            LED_Clear(1);                      // LED2 off
            HW_DELAY_ms(10);
        }

        LCD_PutStringAt(0, 1, "100ms delay test");  // output pulse by 100ms delay
        BUZZER_Beep();
        for (i = 0; i < 50; i++) {
            LED_Set(1);                        // LED2 on
            HW_DELAY_ms(100);
            LED_Clear(1);                      // LED2 off
            HW_DELAY_ms(100);
        }

        LCD_PutStringAt(0, 1, "500ms delay test");  // output pulse by 500ms delay
        BUZZER_Beep();
        for (i = 0; i < 10; i++) {
            LED_Set(1);                        // LED2 on
            HW_DELAY_ms(500);
            LED_Clear(1);                      // LED2 off
            HW_DELAY_ms(500);
        }
    }
}
