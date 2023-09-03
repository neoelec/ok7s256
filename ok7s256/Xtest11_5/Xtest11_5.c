/* ========================================================================== */
/*              Xtest11_5.c : Multiple Interrupt Program by Flag              */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <board.h>

#include <OK7S256gcc.h>

volatile unsigned int RTT_flag = 0;            // RTT interrupt flag
volatile unsigned int TC0_flag = 0;            // TC0 interrupt flag

void RTT_ISR(void)
{                                              /* RTT interrupt service routine */
  if (*AT91C_RTTC_RTSR & 0x0002)               // RTT RTTINC interrupt ?
    RTT_flag = 1;                              // if yes, set RTT_flag
}

void TC0_ISR(void)
{                                              /* TC0 interrupt service routine */
  if (*AT91C_TC0_SR & 0x0010)                  // TC0 CPCS interrupt ?
    TC0_flag = 1;                              // if yes, set TC0_flag
}

int main(void)
{
  unsigned int LED1_status, LED2_status;       // LED1, LED2 toggle status

  MCU_initialize();                            // initialize AT91SAM7S256 & kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module

  LCD_string(0x80, "RTT(LED1) = 2 Hz");        // display title
  LCD_string(0xC0, "TC0(LED2) = 6 Hz");
  Beep();

  LED_off(LED2 | LED1);                        // LED2~LED1 off

  AT91F_RTTC_CfgPMC();                         // initialize RTT
  AT91F_RTTRestart(AT91C_BASE_RTTC);           // clear and restart RTT
  AT91F_RTTSetPrescaler(AT91C_BASE_RTTC, 16384);  // 32.768kHz/16384 = 2Hz

  AT91F_RTTSetRttIncINT(AT91C_BASE_RTTC);      // initialize RTT interrupt
  AT91F_AIC_ConfigureIt(AT91C_BASE_AIC, AT91C_ID_SYS, 7, 1, RTT_ISR);
  AT91F_AIC_EnableIt(AT91C_BASE_AIC, AT91C_ID_SYS);

  AT91F_TC0_CfgPMC();                          // initialize TC0
  *AT91C_TC0_CMR = 0x8989C402;                 // TC0 Channel Control Register
  *AT91C_TC0_CCR = 0x0005;                     // TC0 clock enable and start
  *AT91C_TC0_RA = 10000;                       // set TC0 register
  *AT91C_TC0_RB = 20000;
  *AT91C_TC0_RC = 62500;                       // (48MHz/128/62500 = 6Hz)

  AT91F_TC_InterruptEnable(AT91C_BASE_TC0, AT91C_TC_CPCS);  // initialize TC0 interrupt
  AT91F_AIC_ConfigureIt(AT91C_BASE_AIC, AT91C_ID_TC0, 7, 1, TC0_ISR);
  AT91F_AIC_EnableIt(AT91C_BASE_AIC, AT91C_ID_TC0);

  LED1_status = 0;
  LED2_status = 0;

  while (1) {
    if (RTT_flag == 1) {                       // RTT interrupt ?
      RTT_flag = 0;                            // if yes, clear flag

      LED1_status ^= 0x01;                     // toggle LED1_status(2Hz/2 = 1Hz)
      if (LED1_status == 1)                    // if LED1_status=1, LED1 on
        LED_on(LED1);
      else                                     // if LED1_status=0, LED1 off
        LED_off(LED1);
    }

    if (TC0_flag == 1) {                       // TC0 interrupt ?
      TC0_flag = 0;                            // if yes, clear flag

      LED2_status ^= 0x01;                     // toggle LED2_status(6Hz/2 = 3Hz)
      if (LED2_status == 1)                    // if LED2_status=1, LED2 on
        LED_on(LED2);
      else                                     // if LED2_status=0, LED2 off
        LED_off(LED2);
    }
  }
}
