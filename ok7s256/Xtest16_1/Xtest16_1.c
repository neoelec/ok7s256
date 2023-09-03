/* ========================================================================== */
/*         Xtest16_1.c : Digital Clock by DS1307 RTC(24-Hour Format)          */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <board.h>

#include <OK7S256gcc.h>

unsigned int second, minute, hour, ampm;       // time variable

void LCD_2BCD(unsigned int number)
{                                              /* display 2-digit BCD number */
  LCD_data((number >> 4) + '0');               // 10^1
  LCD_data((number & 0x0F) + '0');             // 10^0
}

void TWI_transmit(unsigned int address, unsigned int data)
{                                              /* transmit by TWI */
  *AT91C_TWI_MMR = 0x00680100;                 // master write, device address 1 byte
  *AT91C_TWI_IADR = address;                   // device address
  *AT91C_TWI_CR = AT91C_TWI_MSEN | AT91C_TWI_STOP | AT91C_TWI_START;  // control register
  *AT91C_TWI_THR = data;                       // start transmission

  while (!(*AT91C_TWI_SR & AT91C_TWI_TXCOMP)) ; // complete?(TXCOMP=1)
}

unsigned int TWI_receive(unsigned int address)
{                                              /* receive by TWI */
  *AT91C_TWI_MMR = 0x00681100;                 // master read, device address 1 byte
  *AT91C_TWI_IADR = address;                   // device address
  *AT91C_TWI_CR = AT91C_TWI_MSEN | AT91C_TWI_STOP | AT91C_TWI_START;  // control register

  while (!(*AT91C_TWI_SR & AT91C_TWI_TXCOMP)) ; // complete?(TXCOMP=1)
  return *AT91C_TWI_RHR;                       // read received data and return
}

int main(void)
{
  MCU_initialize();                            // initialize AT91SAM7S256 & kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module

  hour = 0x23;                                 // initial time 23:55:00
  minute = 0x55;
  second = 0x00;

  LCD_string(0x80, " Digital Clock  ");        // display title
  LCD_string(0xC0, "   12:00:00     ");
  Beep();

  AT91F_TWI_CfgPIO();                          // enable TWD, TWCK pin
  AT91F_PIO_Opendrain(AT91C_BASE_PIOA, AT91C_PA4_TWCK | AT91C_PA3_TWD); // open drain
  AT91F_TWI_CfgPMC();                          // enable peripheral clock for TWI

  AT91F_TWI_Configure(AT91C_BASE_TWI);         // TWI master mode
  *AT91C_TWI_CWGR = 0x00023B3B;                // about 100kHz

  TWI_transmit(0x00, second);                  // innitialize DS1307 RTC
  TWI_transmit(0x01, minute);
  TWI_transmit(0x02, hour);
  TWI_transmit(0x03, 0x06);
  TWI_transmit(0x04, 0x01);
  TWI_transmit(0x05, 0x06);
  TWI_transmit(0x06, 0x07);
  TWI_transmit(0x07, 0x00);                    // (control register = 0x00)

  while (1) {
    hour = TWI_receive(0x02);                  // read hour
    minute = TWI_receive(0x01);                // read minute
    second = TWI_receive(0x00);                // read second

    LCD_command(0xC3);
    LCD_2BCD(hour);                            // display hour
    LCD_command(0xC6);
    LCD_2BCD(minute);                          // display minute
    LCD_command(0xC9);
    LCD_2BCD(second);                          // display second
  }
}
