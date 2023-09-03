/* ========================================================================== */
/*             Xtest14_2.c : DBGU Loopback Test by RS-232C Cable              */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <board.h>

#include <OK7S256gcc.h>

void DBGU_TX_char(unsigned int data)
{                                              /* transmit a character by DBGU */
  while (!(*AT91C_DBGU_CSR & 0x0002)) ;        // wait until TXRDY=1

  *AT91C_DBGU_THR = data;                      // transmit a character
}

unsigned int DBGU_RX_char(void)
{                                              /* receive a character by DBGU */
  unsigned int i;

  i = 0;
  while (!(*AT91C_DBGU_CSR & 0x0001) && (i < 1000000))  // wait until RXRDY=1
    i++;

  if (i < 1000000)
    return *AT91C_DBGU_RHR;                    // receive a character
  else
    return ' ';
}

int main(void)
{
  unsigned int i, RxD;

  MCU_initialize();                            // initialize AT91SAM7S256 & kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD

  LCD_string(0x80, "DBGU Loopback(2)");        // display title

  AT91F_DBGU_CfgPMC();                         // enable clock of DBGU
  AT91F_DBGU_CfgPIO();                         // DTXD, DRXD by Peripheral A

  *AT91C_DBGU_MR = 0x00000800;                 // normal mode, no parity
  *AT91C_DBGU_BRGR = 26;                       // MCK/16/26 = 115200 bps
  *AT91C_DBGU_CR = 0x00000150;                 // TX, RX enable

  while (1) {
    for (i = 'A'; i <= 'Z'; i++) {
      LCD_string(0xC0, "TxD=0,RxD=0     ");
      DBGU_TX_char(i);                         // transmit a character
      LCD_command(0xC4);
      LCD_data(i);                             // display TxD

      RxD = DBGU_RX_char();                    // receive a character
      LCD_command(0xCA);
      LCD_data(RxD);                           // display RxD

      if (RxD == i) {                          // if equal, OK
        LCD_string(0xCB, ", OK!");
        Beep();
      } else {                                 // if not equal, error
        LCD_string(0xCB, ",Err!");
        Error();
      }

      Delay_ms(2000);
    }
  }
}
