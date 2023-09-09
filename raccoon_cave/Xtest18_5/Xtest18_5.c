/* ========================================================================== */
/*           Xtest18_5.c : User-defined printf() Function for DBGU            */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */
/*                                       Modified by Raccoon's Cave in 2023.  */

#include <board.h>
/* - */
#include <lcd.h>
#include <rstc/rstc.h>
#include <utility/buzzer.h>
#include <utility/delay.h>
#include <utility/trace.h>

int main(void)
{
    unsigned int i;
    int x;

    // DBGU configuration
    TRACE_CONFIGURE(DBGU_STANDARD, 115200, BOARD_MCK);

    RSTC_ConfigureMode(AT91C_RSTC_URSTEN);
    BUZZER_Configure(1);
    LCD_Configure(16, 2, LCD_5x8DOTS);

    BUZZER_Beep();

    LCD_PutStringAt(0, 0, "    printf()    "); // display title
    LCD_PutStringAt(0, 1, "    for DBGU    ");

    while (1) {
        for (i = 1, x = -10000; i <= 200; i++, x += 100) {  // loop by 200 times
            printf("printf() function test for DBGU : %3u  %d\n\r", i, x);
            DELAY_ms(500);
        }

        BUZZER_Beep();
    }
}
