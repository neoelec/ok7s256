/* ========================================================================== */
/*  Xtest11_3.c : Multiple Interrupt Program(RTT & PIT in System Controller)  */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <board.h>

#include <OK7S256gcc.h>

volatile unsigned int RTT_flag = 0;            // RTT interrupt flag
volatile unsigned int PIT_flag = 0;            // PIT interrupt flag

void SYS_ISR(void)
{                                              /* RTT & PIT interrupt service routine */
  if (AT91F_RTTGetStatus(AT91C_BASE_RTTC) & 0x0002) { // RTT interrupt ?
    RTT_flag ^= 0x01;                          // toggle RTT_flag(2Hz/2 = 1Hz)
    if (RTT_flag == 1)                         // if RTT_flag=1, LED1 on
      LED_on(LED1);
    else                                       // if RTT_flag=0, LED1 off
      LED_off(LED1);
  } else if (AT91F_PITGetStatus(AT91C_BASE_PITC) & 0x0001) {  // PIT interrupt ?
    AT91F_PITGetPIVR(AT91C_BASE_PITC);         // clear PITS
    PIT_flag ^= 0x01;                          // toggle PIT_flag(4Hz/2 = 2Hz)
    if (PIT_flag == 1)                         // if PIT_flag=1, LED2 on
      LED_on(LED2);
    else                                       // if PIT_flag=0, LED2 off
      LED_off(LED2);
  }
}

int main(void)
{
  MCU_initialize();                            // initialize AT91SAM7S256 & kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module

  LCD_string(0x80, "RTT(LED1) = 2 Hz");        // display title
  LCD_string(0xC0, "PIT(LED2) = 4 Hz");
  Beep();

  LED_off(LED2 | LED1);                        // LED2~LED1 off

  AT91F_RTTC_CfgPMC();                         // initialize RTT
  AT91F_RTTRestart(AT91C_BASE_RTTC);           // clear and restart RTT
  AT91F_RTTSetPrescaler(AT91C_BASE_RTTC, 16384);  // 32.768kHz/16384 = 2Hz
  AT91F_RTTSetRttIncINT(AT91C_BASE_RTTC);      // initialize RTT interrupt

  AT91F_PITC_CfgPMC();                         // initialize PIT
  AT91F_PITInit(AT91C_BASE_PITC, 1, 48);       // enable and initialize PIT
  AT91F_PITSetPIV(AT91C_BASE_PITC, 750000 - 1); // 48MHz/16/750000 = 4Hz
  AT91F_PITEnableInt(AT91C_BASE_PITC);         // initialize PIT interrupt

  AT91F_AIC_ConfigureIt(AT91C_BASE_AIC, AT91C_ID_SYS, 7, 1, SYS_ISR); // set interrupts
  AT91F_AIC_EnableIt(AT91C_BASE_AIC, AT91C_ID_SYS);

  while (1) ;                                  // wait for interrupts
}
