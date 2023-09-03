/* ========================================================================== */
/*        Xtest03_3.c : Access to Absolute Address of I/O Register(3)         */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <board.h>

#include <OK7S256gcc.h>

#define PIO_SODR (*(volatile unsigned int *) 0xFFFFF430)
#define PIO_CODR (*(volatile unsigned int *) 0xFFFFF434)

int main(void)
{
  MCU_initialize();                            // initialize AT91SAM7S256 & kit

  while (1) {
    Beep();                                    // beep

    PIO_CODR = 0x00000001;                     // PA0=0(LED1 on)
    Delay_ms(1000);
    PIO_SODR = 0x00000001;                     // PA0=1(LED1 off)
    Delay_ms(1000);

    PIO_CODR = 0x00000002;                     // PA1=0(LED2 on)
    Delay_ms(1000);
    PIO_SODR = 0x00000002;                     // PA1=1(LED2 off)
    Delay_ms(1000);

    PIO_CODR = 0x00000003;                     // PA1=PA0=0(LED2 and LED1 on)
    Delay_ms(1000);
    PIO_SODR = 0x00000003;                     // PA1=PA0=1(LED2 and LED1 off)
    Delay_ms(1000);
  }
}
