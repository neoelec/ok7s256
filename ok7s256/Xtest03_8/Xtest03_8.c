/* ========================================================================== */
/*         Xtest03_8.c : Check SLCK, MAINCK, PLLCK Clock Frequency(2)         */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <board.h>

#include <OK7S256gcc.h>

int main(void)
{
  MCU_initialize();                            // initialize AT91SAM7S256 & kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module

  LCD_string(0x80, "Check PCK1 (TP3)");        // display title

  AT91F_PIO_CfgPeriph(AT91C_BASE_PIOA, 0, PCK1);  // PCK1 output(Peripheral B) on PA17

  while (1) {
    Beep();                                    // check SLCK
    LCD_string(0xC0, "SLCK = 32.768kHz");
    AT91F_PMC_EnablePCK(AT91C_BASE_PMC, 1, AT91C_PMC_PRES_CLK | AT91C_PMC_CSS_SLOW_CLK);
    Delay_ms(5000);

    Beep();                                    // check MAINCK
    LCD_string(0xC0, "MAINCK=18.432MHz");
    AT91F_PMC_EnablePCK(AT91C_BASE_PMC, 1, AT91C_PMC_PRES_CLK | AT91C_PMC_CSS_MAIN_CLK);
    Delay_ms(5000);

    Beep();                                    // check PLLCK
    LCD_string(0xC0, "PLLCK/16 = 24MHz");
    AT91F_PMC_EnablePCK(AT91C_BASE_PMC, 1, AT91C_PMC_PRES_CLK_16 | AT91C_PMC_CSS_PLL_CLK);
    Delay_ms(5000);
  }
}
