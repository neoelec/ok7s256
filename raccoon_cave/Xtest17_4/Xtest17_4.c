/* ========================================================================== */
/*          Xtest17_4.c : A/D Conversion of AD4(LM35DZ) and AD5(VR1)          */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */
/*                                       Modified by Raccoon's Cave in 2023.  */

#include <board.h>
/* - */
#include <adc/adc.h>
#include <lcd.h>
#include <rstc/rstc.h>
#include <utility/buzzer.h>
#include <utility/delay.h>

static void LCD_2d1(float number)
{                                              /* floating-point number xx.x */
    unsigned int i, j;

    j = (int)(number + 0.5);
    i = j / 100;                               // 10^1
    if (i == 0)
        LCD_PutChar(' ');
    else
        LCD_PutChar(i + '0');

    j = j % 100;                               // 10^0
    i = j / 10;
    LCD_PutChar(i + '0');
    LCD_PutChar('.');

    i = j % 10;                                // 10^-1
    LCD_PutChar(i + '0');
}

static void LCD_1d2(float number)
{                                              /* floating-point number x.xx */
    unsigned int i, j;

    j = (int)(number + 0.5);
    i = j / 100;                               // 10^0
    LCD_PutChar(i + '0');
    LCD_PutChar('.');

    j = j % 100;                               // 10^-1
    i = j / 10;
    LCD_PutChar(i + '0');

    i = j % 10;                                // 10^-2
    LCD_PutChar(i + '0');
}

#define BOARD_ADC_FREQ 5000000

#define ADC_CHANNEL_LM35DZ ADC_CHANNEL_4
#define ADC_CHANNEL_VR1 ADC_CHANNEL_5

static void __ADC_Configure(void)
{
    ADC_Initialize(AT91C_BASE_ADC, AT91C_ID_ADC, AT91C_ADC_TRGEN_DIS, 0, AT91C_ADC_SLEEP_NORMAL_MODE, AT91C_ADC_LOWRES_10_BIT, BOARD_MCK, BOARD_ADC_FREQ, 10, 1200);
}

static unsigned int __ADC_GetValue(unsigned int channel)
{
    unsigned int sum, status;
    unsigned int i;

    ADC_EnableChannel(AT91C_BASE_ADC, channel);

    sum = 0;
    for (i = 0; i < 10; i++) {
        ADC_StartConversion(AT91C_BASE_ADC);   // start conversion
        do {
            status = ADC_GetStatus(AT91C_BASE_ADC);
        } while (!ADC_IsChannelInterruptStatusSet(status, channel));    // wait for EOC
        sum += ADC_GetConvertedData(AT91C_BASE_ADC, channel);   // add A/D result 10 times
        DELAY_ms(1);
    }

    ADC_DisableChannel(AT91C_BASE_ADC, channel);

    return sum;
}

int main(void)
{
    unsigned int sum;

    RSTC_ConfigureMode(AT91C_RSTC_URSTEN);
    BUZZER_Configure(1);
    LCD_Configure(16, 2, LCD_5x8DOTS);
    __ADC_Configure();

    LCD_PutStringAt(0, 0, "LM35 = 00.0 [");    // display title
    LCD_PutChar(0xDF);
    LCD_PutStringAt(14, 0, "C]");
    LCD_PutStringAt(0, 1, " VR1 = 0.00 [V] ");
    BUZZER_Beep();

    while (1) {
        sum = __ADC_GetValue(ADC_CHANNEL_LM35DZ);
        LCD_SetCursor(7, 0);                   // display temperature(xx.x)
        LCD_2d1((float)sum * 66. / 1024.);     // temperature = sum*6.6/1024

        sum = __ADC_GetValue(ADC_CHANNEL_VR1);
        LCD_SetCursor(7, 1);                   // display voltage(x.xx)
        LCD_1d2((float)sum * 33. / 1024.);     // voltage = sum*3.3/1024

        DELAY_ms(250);                         // delay 250 ms
    }
}
