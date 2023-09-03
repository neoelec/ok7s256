/* ========================================================================== */
/*        Xtest12_3.c : Variable Period and Duty Cycle of PWM0 Output         */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <board.h>

#include <OK7S256gcc.h>

void LCD_3d(unsigned int number)
{                                              /* display 3-digit decimal number */
  unsigned int i, flag;

  flag = 0;
  i = number / 100;                            // 10^2
  if (i == 0)
    LCD_data(' ');
  else {
    LCD_data(i + '0');
    flag = 1;
  }

  number = number % 100;                       // 10^1
  i = number / 10;
  if ((i == 0) && (flag == 0))
    LCD_data(' ');
  else {
    LCD_data(i + '0');
    flag = 1;
  }

  i = number % 10;                             // 10^0
  LCD_data(i + '0');
}

void LCD_2d(unsigned int number)
{                                              /* display 2-digit decimal number */
  unsigned int i;

  i = number / 10;                             // 10^1
  if (i == 0)
    LCD_data(' ');
  else
    LCD_data(i + '0');

  i = number % 10;                             // 10^0
  LCD_data(i + '0');
}

__inline void AT91F_PWMC_CfgMode(AT91PS_PWMC pPWM,  // pointer to a PWM controller
                                 unsigned int mode) // PWM_MR register value
{
  pPWM->PWMC_MR = mode;
}

int main(void)
{
  unsigned int PWM0_period = 100, PWM0_duty = 10; // initial PWM period and duty value
  unsigned int step = 10;                      // initial PWM duty step
  unsigned int flag = 0;                       // new setting flag
  double current_duty;                         // current duty cycle

  MCU_initialize();                            // initialize AT91SAM7S256 & kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD

  LCD_string(0x80, "PWM0 Freq & Duty");        // display title
  LCD_string(0xC0, " 100/100kHz,10% ");
  Beep();

  AT91F_PWMC_CfgPMC();                         // enable clock of PWMC
  AT91F_PIO_CfgPeriph(AT91C_BASE_PIOA, AT91C_PA0_PWM0, 0);
  // PWM0 output(Peripheral A)

  AT91F_PWMC_CfgMode(AT91C_BASE_PWMC, 0x041E041E);  // CLKA=CLKB = 48MHz/16/30 = 100kHz
  AT91F_PWMC_CfgChannel(AT91C_BASE_PWMC, 0, 0x020B, 100, PWM0_duty);  // CLKA/100 = 1kHz
  AT91F_PWMC_StartChannel(AT91C_BASE_PWMC, AT91C_PWMC_CHID0); // start PWM0

  while (1) {
    switch (Key_input()) {
    case 1:
      PWM0_duty += step;                       // increment PWM0 duty by 10%
      if (PWM0_duty == PWM0_period)
        PWM0_duty = step;
      flag = 1;
      break;
    case 2:
      current_duty = (double)PWM0_duty / (double)PWM0_period;
      PWM0_period += 100;                      // increment PWM0 period by 100
      if (PWM0_period == 1000)
        PWM0_period = 100;
      PWM0_duty = current_duty * (double)PWM0_period + 0.5;
      step = PWM0_period / 10;                 // calculate new duty step
      flag = 2;
      break;
    default:
      flag = 0;
      break;
    }

    if (flag == 1) {
      flag = 0;
      *AT91C_PWMC_CH0_CMR &= ~AT91C_PWMC_CPD;  // update duty cycle
      AT91F_PWMC_UpdateChannel(AT91C_BASE_PWMC, 0, PWM0_duty);
      LCD_command(0xCC);                       // display PWM0 duty cycle
      LCD_2d(PWM0_duty * 100 / PWM0_period);
    } else if (flag == 2) {
      flag = 0;
      if (PWM0_duty > *AT91C_PWMC_CH0_CPRDR) {
        while (!(*AT91C_PWMC_ISR & AT91C_PWMC_CHID0)) ;
        *AT91C_PWMC_CH0_CMR |= AT91C_PWMC_CPD; // update period
        AT91F_PWMC_UpdateChannel(AT91C_BASE_PWMC, 0, PWM0_period);
        while (!(*AT91C_PWMC_ISR & AT91C_PWMC_CHID0)) ;
        *AT91C_PWMC_CH0_CMR &= ~AT91C_PWMC_CPD; // update duty cycle
        AT91F_PWMC_UpdateChannel(AT91C_BASE_PWMC, 0, PWM0_duty);
      } else {
        while (!(*AT91C_PWMC_ISR & AT91C_PWMC_CHID0)) ;
        *AT91C_PWMC_CH0_CMR &= ~AT91C_PWMC_CPD; // update duty cycle
        AT91F_PWMC_UpdateChannel(AT91C_BASE_PWMC, 0, PWM0_duty);
        while (!(*AT91C_PWMC_ISR & AT91C_PWMC_CHID0)) ;
        *AT91C_PWMC_CH0_CMR |= AT91C_PWMC_CPD; // update period
        AT91F_PWMC_UpdateChannel(AT91C_BASE_PWMC, 0, PWM0_period);
      }
      LCD_command(0xC5);                       // display PWM0 period and duty
      LCD_3d(PWM0_period);
      LCD_command(0xCC);
      LCD_2d(PWM0_duty * 100 / PWM0_period);
    }
  }
}
