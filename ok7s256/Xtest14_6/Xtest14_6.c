/* ========================================================================== */
/*         Xtest14_6.c : USART0 Loopback Test by Local Loopback Mode          */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <board.h>

#include <OK7S256gcc.h>

void USART0_TX_char(unsigned int data)
{                                              /* transmit a character by USART0 */
  while (!(*AT91C_US0_CSR & 0x0002)) ;         // wait until TXRDY=1

  *AT91C_US0_THR = data;                       // transmit a character
}

unsigned int USART0_RX_char(void)
{                                              /* receive a character by USART0 */
  unsigned int i;

  i = 0;
  while (!(*AT91C_US0_CSR & 0x0001) && (i < 1000000)) // wait until RXRDY=1
    i++;

  if (i < 1000000)
    return *AT91C_US0_RHR;                     // receive a character
  else
    return ' ';
}

int main(void)
{
  unsigned int i, RxD;

  MCU_initialize();                            // initialize AT91SAM7S256 & kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD

  LCD_string(0x80, "USART0 Loopback1");        // display title

  AT91F_US0_CfgPMC();                          // enable clock of USART0
  AT91F_PIO_CfgPeriph(AT91C_BASE_PIOA, AT91C_PA6_TXD0 | AT91C_PA5_RXD0, 0);
  // TXD0, RXD0 by Peripheral A

  *AT91C_US0_MR = 0x100088C0;                  // Local Loopback mode, no parity
  // 8 data, 1 stop, LSB first, 16x
  *AT91C_US0_BRGR = 26;                        // MCK/16/26 = 115200 bps
  *AT91C_US0_CR = 0x00000150;                  // TX, RX enable

  while (1) {
    for (i = 'A'; i <= 'Z'; i++) {
      LCD_string(0xC0, "TxD=0,RxD=0     ");
      USART0_TX_char(i);                       // transmit a character
      LCD_command(0xC4);
      LCD_data(i);                             // display TxD

      RxD = USART0_RX_char();                  // receive a character
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
