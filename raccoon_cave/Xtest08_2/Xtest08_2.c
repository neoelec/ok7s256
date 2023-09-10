/* ========================================================================== */
/*               Xtest08_2.c : Key Input Count with Debouncing                */
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

static void LCD_3d(unsigned int number)
{                                              /* display 3-digit decimal number */
    unsigned int i, flag;

    flag = 0;
    i = number / 100;                          // 10^2
    if (i == 0)
        LCD_PutChar(' ');
    else {
        LCD_PutChar(i + '0');
        flag = 1;
    }

    number = number % 100;                     // 10^1
    i = number / 10;
    if ((i == 0) && (flag == 0))
        LCD_PutChar(' ');
    else {
        LCD_PutChar(i + '0');
        flag = 1;
    }

    i = number % 10;                           // 10^0
    LCD_PutChar(i + '0');
}

int main(void)
{
    unsigned int key1 = 0, key2 = 0;

    RSTC_ConfigureMode(AT91C_RSTC_URSTEN);
    BUZZER_Configure(1);
    KEY_Configure(KEY_ACTIVE_LOW);
    LCD_Configure(16, 2, LCD_5x8DOTS);

    LCD_PutStringAt(0, 0, "   KEY1 = 000   "); // display title on text LCD
    LCD_PutStringAt(0, 1, "   KEY2 = 000   ");
    BUZZER_Beep();

    while (1) {
        switch (KEY_Input()) {                 // key input without debouncing
        case 0x01:
            key1++;                            // if key1, display KEY1 count
            if (key1 > 999)
                key1 = 0;
            LCD_SetCursor(10, 0);
            LCD_3d(key1);
            BUZZER_Beep();
            break;
        case 0x02:
            key2++;                            // if key2, display KEY2 count
            if (key2 > 999)
                key2 = 0;
            LCD_SetCursor(10, 1);
            LCD_3d(key2);
            BUZZER_Beep();
            break;
        default:
            break;
        }
    }
}
