/* ========================================================================== */
/*        Xtest14_5.c : RS-232C Communication by DBGU RXRDY Interrupt         */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <board.h>

#include <OK7S256gcc.h>

volatile unsigned int cursor;                  // cursor position of text LCD

void DBGU_RX_ISR(void)
{                                              /* DBGU interrupt service routine */
  LCD_data(*AT91C_DBGU_RHR);                   // display a received character
  cursor++;                                    // 16 character OK ?
  if (cursor == 16) {
    LCD_command(0xC0);                         // if yes, go home
    cursor = 0;
    Beep();
  }
}

void DBGU_TX_char(unsigned int data)
{                                              /* transmit a character by DBGU */
  while (!(*AT91C_DBGU_CSR & 0x0002)) ;        // wait until TXRDY=1

  *AT91C_DBGU_THR = data;                      // transmit a character
}

void DBGU_string(char *string)
{                                              /* transmit a string by DBGU */
  while (*string != '\0') {
    DBGU_TX_char(*string);
    string++;
  }
}

int main(void)
{
  MCU_initialize();                            // initialize AT91SAM7S256 & kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD

  LCD_string(0x80, " RS-232C (DBGU) ");        // display title
  LCD_string(0xC0, "                ");
  Beep();

  LCD_command(0x0F);                           // cursor ON
  LCD_command(0xC0);                           // initial cursor position
  cursor = 0;

  AT91F_DBGU_CfgPMC();                         // enable clock of DBGU
  AT91F_DBGU_CfgPIO();                         // DTXD, DRXD by Peripheral A

  *AT91C_DBGU_MR = 0x00000800;                 // normal mode, no parity
  *AT91C_DBGU_BRGR = 26;                       // MCK/16/26 = 115200 bps
  *AT91C_DBGU_CR = 0x00000150;                 // TX, RX enable

  AT91F_DBGU_InterruptEnable(AT91C_BASE_DBGU, AT91C_US_RXRDY);  // DBGU RXRDY interrupt
  AT91F_AIC_ConfigureIt(AT91C_BASE_AIC, AT91C_ID_SYS, 7, 1, DBGU_RX_ISR);
  AT91F_AIC_EnableIt(AT91C_BASE_AIC, AT91C_ID_SYS);

  while (1) {
    switch (Key_input()) {                     // key input
    case 1:
      LED_on(LED1);
      LED_off(LED2);                           // KEY1 ?
      DBGU_string("  KEY1 is OK !  ");
      DBGU_TX_char(0x0D);
      DBGU_TX_char(0x0A);
      break;
    case 2:
      LED_on(LED2);
      LED_off(LED1);                           // KEY2 ?
      DBGU_string("  KEY2 is OK !  ");
      DBGU_TX_char(0x0D);
      DBGU_TX_char(0x0A);
      break;
    default:
      break;
    }
  }
}
