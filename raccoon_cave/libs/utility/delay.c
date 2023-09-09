#include <board.h>

void DELAY_1us(void)
{                                              /* 1 us delay for -Os option */
    volatile unsigned int count;

    for (count = 0; count < 1; count++) ;
}

void DELAY_us(unsigned int us)
{                                              /* us delay for -Os option */
    volatile unsigned int count, countmax = (BOARD_MCK / 24000000) * us;

    for (count = 0; count < countmax; count++) ;
}

void DELAY_ms(unsigned int ms)
{                                              /* ms delay for -Os option */
    volatile unsigned int count, countmax = (BOARD_MCK / 25000) * ms;

    for (count = 0; count < countmax; count++) ;
}
