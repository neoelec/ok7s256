/* ========================================================================== */
/*        Xtest05_4.c : Visiting Count on GLCD using Random Number(3)         */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <stdlib.h>
#include <board.h>

#include <OK7S256gcc.h>
#include <OK7S256GLCD.h>

void TWI_initialize(void)
{                                              /* initialize TWI */
  AT91F_TWI_CfgPIO();                          // enable TWD, TWCK pin
  AT91F_PIO_Opendrain(AT91C_BASE_PIOA, AT91C_PA4_TWCK | AT91C_PA3_TWD); // open drain
  AT91F_TWI_CfgPMC();                          // enable peripheral clock for TWI

  AT91F_TWI_Configure(AT91C_BASE_TWI);         // TWI master mode
  *AT91C_TWI_CWGR = 0x00023B3B;                // about 100kHz
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

void RTC_check(void)
{                                              /* check if DS1307 RTC is OK */
  unsigned int RTC_flag;

  RTC_flag = 0;                                // initial flag

  if (TWI_receive(0x00) == 0x00)               // if second = 0x00, not OK
    RTC_flag = 1;
  else if (TWI_receive(0x00) > 0x59)           // if second > 0x59, not OK
    RTC_flag = 1;
  else if (TWI_receive(0x01) == 0x00)          // if minute = 0x00, not OK
    RTC_flag = 1;
  else if (TWI_receive(0x01) > 0x59)           // if minute > 0x59, not OK
    RTC_flag = 1;
  else if ((TWI_receive(0x02) & 0x9F) == 0x00) // if hour = 0x00, not OK
    RTC_flag = 1;
  else if ((TWI_receive(0x02) & 0x40) == 0x00)
    RTC_flag = 1;
  else if ((TWI_receive(0x02) & 0x9F) > 0x12)  // if hour > 0x12, not OK
    RTC_flag = 1;
  else if (TWI_receive(0x03) == 0x00)          // if week = 0x00, not OK
    RTC_flag = 1;
  else if (TWI_receive(0x03) > 0x07)           // if week > 0x07, not OK
    RTC_flag = 1;
  else if (TWI_receive(0x04) == 0x00)          // if date = 0x00, not OK
    RTC_flag = 1;
  else if (TWI_receive(0x04) > 0x31)           // if date > 0x31, not OK
    RTC_flag = 1;
  else if (TWI_receive(0x05) == 0x00)          // if month = 0x00, not OK
    RTC_flag = 1;
  else if (TWI_receive(0x05) > 0x12)           // if month > 0x12, not OK
    RTC_flag = 1;
  else if (TWI_receive(0x06) > 0x99)           // if year > 0x99, not OK
    RTC_flag = 1;

  if (RTC_flag != 0) {
    TWI_transmit(0x00, 0x00);                  // innitialize DS1307 RTC
    TWI_transmit(0x01, 0x00);                  // (2007/06/01 FRI 12:00:00 AM)
    TWI_transmit(0x02, 0x12 | 0x40);
    TWI_transmit(0x03, 0x06);
    TWI_transmit(0x04, 0x01);
    TWI_transmit(0x05, 0x06);
    TWI_transmit(0x06, 0x07);
    TWI_transmit(0x07, 0x00);                  // (control register = 0x00)
  }
}

int main(void)
{
  unsigned int i, j, seed, random, x, y, visit_flag;

  MCU_initialize();                            // initialize AT91SAM7S256 & kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD
  GLCD_clear();                                // initialize GLCD screen

  LCD_string(0x80, "Graphic LCD Test");        // display title on text LCD
  LCD_string(0xC0, " Visiting Count ");
  Beep();

  Clear_screen();                              // clear visiting room
  visit_flag = 0;
  x = 32;                                      // starting position
  y = 64;

  TWI_initialize();                            // initialize TWI
  RTC_check();                                 // check the status of DS1307 RTC

  seed = TWI_receive(0x02) << 16;              // make seed of random number
  seed += (TWI_receive(0x01) << 8);            // (seed = hour / minute / second)
  seed += TWI_receive(0x00);
  srand(seed);                                 // initialize random number

  while (visit_flag == 0) {
    random = rand();                           // get random number

    if (random <= 0x1FFFFFFF) {                // 0x00000000 - 0x1FFFFFFF
      if (y == 127)
        y = 0;
      else
        y++;
      Dot(x, y);
    } else if (random <= 0x3FFFFFFF) {         // 0x20000000 - 0x3FFFFFFF
      if (y == 0)
        y = 127;
      else
        y--;
      Dot(x, y);
    } else if (random <= 0x5FFFFFFF) {         // 0x40000000 - 0x5FFFFFFF
      if (x == 63)
        x = 0;
      else
        x++;
      Dot(x, y);
    } else {                                   // 0x60000000 - 0x7FFFFFFF
      if (x == 0)
        x = 63;
      else
        x--;
      Dot(x, y);
    }

    Delay_ms(1);

    visit_flag = 1;                            // check end
    for (i = 0; i <= 7; i++)
      for (j = 0; j <= 127; j++)
        if (screen[i][j] != 0xFF)
          visit_flag = 0;
  }

  Beep();                                      // OK sound
  LCD_string(0xC0, "  Visiting OK!  ");        // OK message
  while (1) ;
}
