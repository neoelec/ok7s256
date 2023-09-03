/* ========================================================================== */
/*        Xtest03_2.c : Access to Absolute Address of I/O Register(2)         */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <board.h>

#include <OK7S256gcc.h>

int main(void)
{
  MCU_initialize();                            // initialize AT91SAM7S256 & kit

  while (1) {
    Beep();                                    // beep

    *AT91C_PIOA_CODR = 0x00000001;             // PA0=0(LED1 on)
    Delay_ms(1000);
    *AT91C_PIOA_SODR = 0x00000001;             // PA0=1(LED1 off)
    Delay_ms(1000);

    *AT91C_PIOA_CODR = 0x00000002;             // PA1=0(LED2 on)
    Delay_ms(1000);
    *AT91C_PIOA_SODR = 0x00000002;             // PA1=1(LED2 off)
    Delay_ms(1000);

    *AT91C_PIOA_CODR = 0x00000003;             // PA1=PA0=0(LED2 and LED1 on)
    Delay_ms(1000);
    *AT91C_PIOA_SODR = 0x00000003;             // PA1=PA0=1(LED2 and LED1 off)
    Delay_ms(1000);
  }
}
