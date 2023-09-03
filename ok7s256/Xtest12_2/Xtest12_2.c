/* ========================================================================== */
/*           Xtest12_2.c : Variable Duty Cycle of PWM0, PWM1 Output           */
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

__inline void AT91F_PWMC_CfgMode(AT91PS_PWMC pPWM,  // pointer to a PWM controller
                                 unsigned int mode) // PWM_MR register value
{
  pPWM->PWMC_MR = mode;
}

int main(void)
{
  unsigned int PWM0_duty = 10, PWM1_duty = 20; // initial PWM duty value

  MCU_initialize();                            // initialize AT91SAM7S256 & kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD

  LCD_string(0x80, "PWM0 = 2kHz, 10%");        // display title
  LCD_string(0xC0, "PWM1 = 1kHz, 10%");
  Beep();

  AT91F_PWMC_CfgPMC();                         // enable clock of PWMC
  AT91F_PIO_CfgPeriph(AT91C_BASE_PIOA, AT91C_PA1_PWM1 | AT91C_PA0_PWM0, 0);
  // PWM1,PWM0 output(Peripheral A)

  AT91F_PWMC_CfgMode(AT91C_BASE_PWMC, 0x031E031E);  // CLKA=CLKB = 48MHz/8/30 = 200kHz
  AT91F_PWMC_CfgChannel(AT91C_BASE_PWMC, 0, 0x020B, 100, PWM0_duty);  // CLKA/100 = 2kHz
  AT91F_PWMC_CfgChannel(AT91C_BASE_PWMC, 1, 0x020B, 200, PWM1_duty);  // CLKA/200 = 1kHz
  AT91F_PWMC_StartChannel(AT91C_BASE_PWMC, AT91C_PWMC_CHID1 | AT91C_PWMC_CHID0);
  // start PWM1 and PWM0

  while (1) {
    switch (Key_input()) {
    case 1:
      if (PWM0_duty < 90)
        PWM0_duty += 10;                       // increment PWM0 duty by 10%
      else
        PWM0_duty = 10;
      AT91F_PWMC_UpdateChannel(AT91C_BASE_PWMC, 0, PWM0_duty);
      LCD_command(0x8C);
      LCD_3d(PWM0_duty * 100 / 100);
      break;
    case 2:
      if (PWM1_duty < 180)
        PWM1_duty += 20;                       // increment PWM1 duty by 10%
      else
        PWM1_duty = 20;
      AT91F_PWMC_UpdateChannel(AT91C_BASE_PWMC, 1, PWM1_duty);
      LCD_command(0xCC);
      LCD_3d(PWM1_duty * 100 / 200);
      break;
    }
  }
}
