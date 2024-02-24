/* ========================================================================== */
/*                  Xtest12_1.c : Constant PWM0, PWM1 Output                  */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <board.h>

#include <OK7S256gcc.h>

__inline void AT91F_PWMC_CfgMode(AT91PS_PWMC pPWM,  // pointer to a PWM controller
                                 unsigned int mode) // PWM_MR register value
{
  pPWM->PWMC_MR = mode;
}

int main(void)
{
  MCU_initialize();                            // initialize AT91SAM7S256 & kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD

  LCD_string(0x80, "PWM0 = 2kHz, 25%");        // display title
  LCD_string(0xC0, "PWM1 = 1kHz, 50%");
  Beep();

  AT91F_PWMC_CfgPMC();                         // enable clock of PWMC
  AT91F_PIO_CfgPeriph(AT91C_BASE_PIOA, AT91C_PA1_PWM1 | AT91C_PA0_PWM0, 0);
  // PWM1,PWM0 output(Peripheral A)

  AT91F_PWMC_CfgMode(AT91C_BASE_PWMC, 0x031E031E);  // CLKA=CLKB = 48MHz/8/30 = 200kHz
  AT91F_PWMC_CfgChannel(AT91C_BASE_PWMC, 0, 0x020B, 100, 25); // CLKA/100 = 2kHz
  AT91F_PWMC_CfgChannel(AT91C_BASE_PWMC, 1, 0x020B, 200, 100);  // CLKA/200 = 1kHz
  AT91F_PWMC_StartChannel(AT91C_BASE_PWMC, AT91C_PWMC_CHID1 | AT91C_PWMC_CHID0);
  // start PWM1 and PWM0

  while (1) ;                                  // infinite loop
}
