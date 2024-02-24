/* ========================================================================== */
/*         Xtest11_2.c : Timer/Counter Waveform Generation(WAVSEL=11)         */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <board.h>

#include <OK7S256gcc.h>

void LCD_4d(unsigned int number)
{                                              /* display 4-digit decimal number */
  unsigned int i, flag;

  flag = 0;
  i = number / 1000;                           // 10^3
  if (i == 0)
    LCD_data(' ');
  else {
    LCD_data(i + '0');
    flag = 1;
  }

  number = number % 1000;                      // 10^2
  i = number / 100;
  if ((i == 0) && (flag == 0))
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

int main(void)
{
  unsigned int TC0_RA = 500;                   // initial register value
  unsigned int TC0_RB = 1000;
  unsigned int TC0_RC = 1500;

  MCU_initialize();                            // initialize AT91SAM7S256 & kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD

  LCD_string(0x80, "KEY1:TC0_RA=0500");        // display title
  LCD_string(0xC0, "KEY2:TC0_RB=1000");
  Beep();

  AT91F_TC0_CfgPMC();                          // enable clock of TC0
  AT91F_PIO_CfgPeriph(AT91C_BASE_PIOA, 0, AT91C_PA1_TIOB0 | AT91C_PA0_TIOA0);
  // TIOA0,TIOB0 output(Peripheral B)

  *AT91C_TC0_CMR = 0x4343E402;                 // TC0 Channel Control Register
  *AT91C_TC0_CCR = 0x0005;                     // TC0 clock enable and start

  *AT91C_TC0_RA = TC0_RA;                      // set TC0 register
  *AT91C_TC0_RB = TC0_RB;
  *AT91C_TC0_RC = TC0_RC;

  while (1) {
    switch (Key_input()) {
    case 1:
      TC0_RA += 100;                           // increment TC0_RA by 100
      if (TC0_RA == TC0_RC)
        TC0_RA = 100;
      while (*AT91C_TC0_CV != 0) ;             // synchronize
      *AT91C_TC0_RA = TC0_RA;                  // new setting of TC0_RA
      LCD_command(0x8C);                       // display TC0_RA
      LCD_4d(TC0_RA);
      break;
    case 2:
      TC0_RB += 100;                           // increment TC0_RB by 100
      if (TC0_RB == TC0_RC)
        TC0_RB = 100;
      while (*AT91C_TC0_CV != 0) ;             // synchronize
      *AT91C_TC0_RB = TC0_RB;                  // new setting of TC0_RB
      LCD_command(0xCC);                       // display TC0_RB
      LCD_4d(TC0_RB);
      break;
    }
  }
}
