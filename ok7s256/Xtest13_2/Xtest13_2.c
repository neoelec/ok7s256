/* ========================================================================== */
/*                     Xtest13_2.c : Telephone Bell Sound                     */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <board.h>

#include <OK7S256gcc.h>

int main(void)
{
  unsigned int i;

  MCU_initialize();                            // initialize AT91SAM7S256 & kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD

  LCD_string(0x80, "  ** SOUND **   ");        // display title
  LCD_string(0xC0, " Telephone Bell ");

  AT91F_PWMC_CfgPMC();                         // enable clock of PWMC
  AT91F_PIO_CfgPeriph(AT91C_BASE_PIOA, SPEAKER, 0); // PWM0 output on PA0

  while (1) {
    AT91F_PWMC_StartChannel(AT91C_BASE_PWMC, AT91C_PWMC_CHID0); // start sound
    for (i = 0; i < 20; i++) {
      AT91F_PWMC_CfgChannel(AT91C_BASE_PWMC, 0, 0x0204, 9375, 4688);
      // 48MHz/16/9375 = 320Hz
      Delay_ms(25);
      AT91F_PWMC_CfgChannel(AT91C_BASE_PWMC, 0, 0x0204, 6250, 3125);
      // 48MHz/16/6250 = 480Hz
      Delay_ms(25);
    }

    AT91F_PWMC_StopChannel(AT91C_BASE_PWMC, AT91C_PWMC_CHID0);  // stop sound
    Delay_ms(1000);
  }
}
