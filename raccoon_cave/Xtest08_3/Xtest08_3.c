/* ========================================================================== */
/*             Xtest08_3.c : PIO Interrupt Program by KEY1 & KEY2             */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */
/*                                       Modified by Raccoon's Cave in 2023.  */

#include <board.h>
/* - */
#include <lcd.h>
#include <rstc/rstc.h>
#include <utility/buzzer.h>
#include <utility/delay.h>
#include <utility/key.h>
#include <utility/led.h>
#include <utility/tick.h>

static KeyNotifier kn;
static unsigned int keycode;

static void KN_Handle(KeyNotifier * kn, unsigned int number)
{
    keycode |= (1 << number);
}

static void __KEY_Configurea(void)
{
    KEY_ConfigureIt(KEY_ACTIVE_LOW);

    kn.func = KN_Handle;
    KEY_RegisterNotifier(&kn);
}

static void __LED_Configure(void)
{
    LED_Configure(0);
    LED_Configure(1);
}

int main(void)
{
    RSTC_ConfigureMode(AT91C_RSTC_URSTEN);
    TICK_Configure();
    BUZZER_Configure(1);
    __KEY_Configurea();
    LCD_Configure(16, 2, LCD_5x8DOTS);
    __LED_Configure();

    LCD_PutStringAt(0, 0, " PIO Interrupt  "); // display title on text LCD
    LCD_PutStringAt(0, 1, "                ");
    BUZZER_Beep();

    while (1) {
        if (keycode & 0x1) {
            LCD_PutStringAt(0, 1, "    by KEY1     ");
            BUZZER_Beep();
            LED_Clear(1);
            LED_Set(0);
            keycode &= ~0x1;
        }

        if (keycode & 0x2) {
            LCD_PutStringAt(0, 1, "    by KEY2     ");
            BUZZER_Beep();
            LED_Clear(0);
            LED_Set(1);
            keycode &= ~0x2;
        }
    }
}
