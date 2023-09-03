/* ========================================================================== */
/*              Xtest09_2.c : PIT Interrupt Program(0.5Hz Speed)              */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <board.h>

#include <OK7S256gcc.h>

volatile unsigned int PIT_count = 0;           // PIT interrupt count
volatile unsigned int PIT_flag = 0;            // PIT interrupt flag

void PIT_ISR(void)
{                                              /* PIT interrupt service routine */
  AT91F_PITGetPIVR(AT91C_BASE_PITC);           // clear PITS

  PIT_count++;                                 // increment PIT_count

  if (PIT_count < 10)                          // 5Hz/10 = 0.5Hz
    return;

  PIT_count = 0;                               // if PIT_count=10, clear it
  PIT_flag ^= 0x01;                            // toggle PIT_flag

  if (PIT_flag == 1)                           // if PIT_flag=1, LED2 on
    LED_on(LED2);
  else                                         // if PIT_flag=0, LED2 off
    LED_off(LED2);
}

int main(void)
{
  MCU_initialize();                            // initialize AT91SAM7S256 & kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module

  LCD_string(0x80, " PIT Interrupt  ");        // display title
  LCD_string(0xC0, "    (0.5 Hz)    ");
  Beep();

  LED_off(LED2 | LED1);                        // LED2~LED1 off

  AT91F_PITC_CfgPMC();                         // enable peripheral clock for PIT
  AT91F_PITInit(AT91C_BASE_PITC, 1, 48);       // enable and initialize PIT
  AT91F_PITSetPIV(AT91C_BASE_PITC, 600000 - 1); // 48MHz/16/600000 = 5Hz

  AT91F_PITEnableInt(AT91C_BASE_PITC);         // initialize PIT interrupt
  AT91F_AIC_ConfigureIt(AT91C_BASE_AIC, AT91C_ID_SYS, 7, 1, PIT_ISR);
  AT91F_AIC_EnableIt(AT91C_BASE_AIC, AT91C_ID_SYS);

  while (1) ;                                  // wait for interrupt
}
