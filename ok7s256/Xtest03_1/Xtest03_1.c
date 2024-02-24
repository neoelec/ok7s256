/* ========================================================================== */
/*        Xtest03_1.c : Access to Absolute Address of I/O Register(1)         */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <board.h>

#include <OK7S256gcc.h>

int main(void)
{
  MCU_initialize();                            // initialize AT91SAM7S256 & kit

  while (1) {
    Beep();                                    // beep

    AT91F_PIO_ClearOutput(AT91C_BASE_PIOA, PA0);  // PA0=0(LED1 on)
    Delay_ms(1000);
    AT91F_PIO_SetOutput(AT91C_BASE_PIOA, PA0); // PA0=1(LED1 off)
    Delay_ms(1000);

    AT91F_PIO_ClearOutput(AT91C_BASE_PIOA, PA1);  // PA1=0(LED2 on)
    Delay_ms(1000);
    AT91F_PIO_SetOutput(AT91C_BASE_PIOA, PA1); // PA1=1(LED2 off)
    Delay_ms(1000);

    AT91F_PIO_ClearOutput(AT91C_BASE_PIOA, PA1 | PA0);  // PA1=PA0=0(LED2 and LED1 on)
    Delay_ms(1000);
    AT91F_PIO_SetOutput(AT91C_BASE_PIOA, PA1 | PA0);  // PA1=PA0=1(LED2 and LED1 off)
    Delay_ms(1000);
  }
}
