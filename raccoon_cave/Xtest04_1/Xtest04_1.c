/* ========================================================================== */
/*                    Xtest04_1.c : Basic Text LCD Display                    */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */
/*                                       Modified by Raccoon's Cave in 2023.  */

#include <board.h>
/* - */
#include <lcd.h>
#include <rstc/rstc.h>
#include <utility/buzzer.h>
#include <utility/delay.h>

int main(void)
{
    unsigned int i;

    RSTC_ConfigureMode(AT91C_RSTC_URSTEN);
    BUZZER_Configure(1);
    LCD_Configure(16, 2, LCD_5x8DOTS);

    while (1) {
        BUZZER_Beep();
        LCD_PutStringAt(0, 0, " OK-7S256  V1.0 ");  // logo title 1
        LCD_PutStringAt(0, 1, "AT91SAM7S256 ARM");
        DELAY_ms(2000);
        LCD_PutStringAt(0, 1, "   2007/06/01   ");  // logo title 2
        DELAY_ms(2000);
        LCD_PutStringAt(0, 1, "  Ohm Books Co. ");  // logo title 3
        DELAY_ms(2000);

        BUZZER_Beep();
        LCD_PutStringAt(0, 0, "0123456789ABCDEF0123456789ABCDEF");  // display long line
        LCD_PutStringAt(0, 1, "Go shift left and right 16 times");
        DELAY_ms(1000);

        for (i = 0; i < 16; i++) {             // shift left
            LCD_ScrollDisplayLeft();
            DELAY_ms(300);
        }
        DELAY_ms(1000);

        for (i = 0; i < 16; i++) {             // shift right
            LCD_ScrollDisplayRight();
            DELAY_ms(300);
        }
        DELAY_ms(1000);
    }
}
