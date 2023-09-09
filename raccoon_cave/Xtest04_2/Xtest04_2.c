/* ========================================================================== */
/*                Xtest04_2.c : User-Defined Character Display                */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */
/*                                       Modified by Raccoon's Cave in 2023.  */

#include <board.h>
/* - */
#include <lcd.h>
#include <rstc/rstc.h>
#include <utility/buzzer.h>
#include <utility/delay.h>

#define NRELEM(a) (sizeof(a) / sizeof(a[0]))

static const uint8_t custChar[][8] = {
    { 0x10, 0x18, 0x1C, 0x1E, 0x1C, 0x18, 0x10, 0x00, },    // character 0x00
    { 0x0F, 0x09, 0x09, 0x09, 0x09, 0x09, 0x0F, 0x00, },    // character 0x01
    { 0x08, 0x08, 0x08, 0x0E, 0x08, 0x08, 0x08, 0x00, },    // character 0x02
    { 0x01, 0x02, 0x04, 0x08, 0x00, 0x00, 0x0F, 0x00, },    // character 0x03
    { 0x10, 0x08, 0x04, 0x02, 0x00, 0x00, 0x1E, 0x00, },    // character 0x04
    { 0x0F, 0x08, 0x08, 0x0F, 0x08, 0x08, 0x0F, 0x00, },    // character 0x05
    { 0x04, 0x04, 0x04, 0x1C, 0x04, 0x04, 0x04, 0x00, },    // character 0x06
    { 0x01, 0x03, 0x07, 0x0F, 0x07, 0x03, 0x01, 0x00, },    // character 0x07
};

static void Set_font(void)
{                                              /* set user character font */
    uint8_t i;

    for (i = 0; i < NRELEM(custChar); i++)
        LCD_CreateChar(i, custChar[i]);
}

int main(void)
{
    RSTC_ConfigureMode(AT91C_RSTC_URSTEN);
    BUZZER_Configure(1);
    LCD_Configure(16, 2, LCD_5x8DOTS);

    Set_font();                                // set user character font

    while (1) {
        BUZZER_Beep();
        LCD_Command(0x80);                     // display logo
        LCD_PutChar(0x00);
        LCD_PutStringAt(1, 0, " OK-7S256 KIT ");
        LCD_PutChar(0x07);
        LCD_PutStringAt(0, 1, " AT91SAM ");    // display message 1
        LCD_PutChar(0x01);
        LCD_PutChar(0x02);
        LCD_PutChar(0x03);
        LCD_PutChar(0x04);
        LCD_PutChar(0x05);
        LCD_PutChar(0x06);
        LCD_PutChar(' ');
        DELAY_ms(2000);
        LCD_PutStringAt(0, 1, "   2007/06/01   ");  // display message 2
        DELAY_ms(2000);
        LCD_PutStringAt(0, 1, " DUCK-YONG YOON ");  // display message 3
        DELAY_ms(2000);
    }
}
