/* ========================================================================== */
/*       Xtest14_10.c : RS-232C Communication by USART0 RXRDY Interrupt       */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <board.h>

#include <OK7S256gcc.h>

volatile unsigned int cursor;                  // cursor position of text LCD

void USART0_RX_ISR(void)
{                                              /* USART0 interrupt service routine */
  LCD_data(*AT91C_US0_RHR);                    // display a received character
  cursor++;                                    // 16 character OK ?
  if (cursor == 16) {
    LCD_command(0xC0);                         // if yes, go home
    cursor = 0;
    Beep();
  }
}

void USART0_TX_char(unsigned int data)
{                                              /* transmit a character by USART0 */
  while (!(*AT91C_US0_CSR & 0x0002)) ;         // wait until TXRDY=1

  *AT91C_US0_THR = data;                       // transmit a character
}

void USART0_string(char *string)
{                                              /* transmit a string by USART0 */
  while (*string != '\0') {
    USART0_TX_char(*string);
    string++;
  }
}

int main(void)
{
  MCU_initialize();                            // initialize AT91SAM7S256 & kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD

  LCD_string(0x80, "RS-232C (USART0)");        // display title
  LCD_string(0xC0, "                ");
  Beep();

  LCD_command(0x0F);                           // cursor ON
  LCD_command(0xC0);                           // initial cursor position
  cursor = 0;

  AT91F_US0_CfgPMC();                          // enable clock of USART0
  AT91F_PIO_CfgPeriph(AT91C_BASE_PIOA, AT91C_PA6_TXD0 | AT91C_PA5_RXD0, 0);
  // TXD0, RXD0 by Peripheral A

  *AT91C_US0_MR = 0x100008C0;                  // normal mode, no parity
  // 8 data, 1 stop, LSB first, 16x
  *AT91C_US0_BRGR = 26;                        // MCK/16/26 = 115200 bps
  *AT91C_US0_CR = 0x00000150;                  // TX, RX enable

  AT91F_US_EnableIt(AT91C_BASE_US0, AT91C_US_RXRDY);  // USART0 RXRDY interrupt
  AT91F_AIC_ConfigureIt(AT91C_BASE_AIC, AT91C_ID_US0, 7, 1, USART0_RX_ISR);
  AT91F_AIC_EnableIt(AT91C_BASE_AIC, AT91C_ID_US0);

  while (1) {
    switch (Key_input()) {                     // key input
    case 1:
      LED_on(LED1);
      LED_off(LED2);                           // KEY1 ?
      USART0_string("  KEY1 is OK !  ");
      USART0_TX_char(0x0D);
      USART0_TX_char(0x0A);
      break;
    case 2:
      LED_on(LED2);
      LED_off(LED1);                           // KEY2 ?
      USART0_string("  KEY2 is OK !  ");
      USART0_TX_char(0x0D);
      USART0_TX_char(0x0A);
      break;
    default:
      break;
    }
  }
}
