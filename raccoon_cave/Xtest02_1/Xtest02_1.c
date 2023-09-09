/* ========================================================================== */
/*                        Xtest02_1.c : LED Display(1)                        */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */
/*                                       Modified by Raccoon's Cave in 2023.  */

#include <board.h>
/* - */
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
    RSTC_ConfigureMode(AT91C_RSTC_URSTEN);
    BUZZER_Configure(1);
    __LED_Configure();

    while (1) {
        BUZZER_Beep();                         // beep

        LED_Set(0);                            // LED1 on
        DELAY_ms(1000);
        LED_Clear(0);                          // LED1 off
        DELAY_ms(1000);

        LED_Set(1);                            // LED2 on
        DELAY_ms(1000);
        LED_Clear(1);                          // LED2 off
        DELAY_ms(1000);

        LED_Set(0);                            // LED2 and LED1 on
        LED_Set(1);
        DELAY_ms(1000);
        LED_Clear(0);                          // LED2 and LED1 off
        LED_Clear(1);
        DELAY_ms(1000);
    }
}
