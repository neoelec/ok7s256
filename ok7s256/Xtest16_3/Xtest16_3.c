/* ========================================================================== */
/*    Xtest16_3.c : Digital Clock with Calendar on Text LCD by DS1307 RTC     */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <board.h>

#include <OK7S256gcc.h>

unsigned int year, month, date, weekday;       // time variable
unsigned int second, minute, hour, ampm, cursor;

void LCD_2BCD(unsigned int number)
{                                              /* display 2-digit BCD number */
  LCD_data((number >> 4) + '0');               // 10^1
  LCD_data((number & 0x0F) + '0');             // 10^0
}

unsigned int BCD_increment(unsigned int number)
{                                              /* BCD increment */
  unsigned int i;

  i = (number >> 4) * 10 + (number & 0x0F);    // convert BCD to binary
  i++;                                         // incrment
  i = ((i / 10) << 4) + (i % 10);              // convert binary to BCD
  return i;
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

void RTC_display(void)
{                                              /* display clock from RTC */
  LCD_command(0x0C);                           // cursor OFF

  year = TWI_receive(0x06);                    // display year
  LCD_command(0x83);
  LCD_2BCD(year);

  month = TWI_receive(0x05);                   // display month
  LCD_command(0x86);
  LCD_2BCD(month);

  date = TWI_receive(0x04);                    // display date
  LCD_command(0x89);
  LCD_2BCD(date);

  weekday = TWI_receive(0x03);                 // display weekday
  if (weekday == 1)
    LCD_string(0x8C, "SUN");
  else if (weekday == 2)
    LCD_string(0x8C, "MON");
  else if (weekday == 3)
    LCD_string(0x8C, "TUE");
  else if (weekday == 4)
    LCD_string(0x8C, "WED");
  else if (weekday == 5)
    LCD_string(0x8C, "THU");
  else if (weekday == 6)
    LCD_string(0x8C, "FRI");
  else
    LCD_string(0x8C, "SAT");

  hour = TWI_receive(0x02) & 0x3F;             // display hour
  if (hour > 0x20) {
    hour &= 0x1F;
    ampm = 'P';
  } else
    ampm = 'A';
  LCD_command(0xC2);
  LCD_2BCD(hour);
  LCD_command(0xCB);
  LCD_data(ampm);                              // display AM/PM

  minute = TWI_receive(0x01);                  // display minute
  LCD_command(0xC5);
  LCD_2BCD(minute);

  second = TWI_receive(0x00);                  // display second
  LCD_command(0xC8);
  LCD_2BCD(second);

  LCD_command(cursor);                         // go cursor position
  LCD_command(0x0F);                           // cursor ON
  Delay_ms(10);                                // time delay for cursor

  if ((minute == 0x00) && (second == 0x00)) {  // beep for each o'clock
    Beep();
    Delay_ms(1000);
  }
}

void Cursor_left(void)
{                                              /* go cursor left */
  if (cursor == 0xCF)
    cursor = 0xCC;
  else if (cursor == 0xCC)
    cursor = 0xC9;
  else if (cursor == 0xC9)
    cursor = 0xC6;
  else if (cursor == 0xC6)
    cursor = 0xC3;
  else if (cursor == 0xC3)
    cursor = 0x8E;
  else if (cursor == 0x8E)
    cursor = 0x8A;
  else if (cursor == 0x8A)
    cursor = 0x87;
  else if (cursor == 0x87)
    cursor = 0x84;
  else if (cursor == 0x84)
    cursor = 0xCF;
}

void Increment(void)
{                                              /* increment time */
  switch (cursor) {
  case 0x84:
    year = TWI_receive(0x06);                  // in case of year
    if (year == 0x99)
      year = 0x00;
    else
      year = BCD_increment(year);
    TWI_transmit(0x06, year);
    break;
  case 0x87:
    month = TWI_receive(0x05);                 // in case of month
    if (month == 0x12)
      month = 0x01;
    else
      month = BCD_increment(month);
    TWI_transmit(0x05, month);
    break;
  case 0x8A:
    date = TWI_receive(0x04);                  // in case of date
    if (date == 0x31)
      date = 0x01;
    else
      date = BCD_increment(date);
    TWI_transmit(0x04, date);
    break;
  case 0x8E:
    weekday = TWI_receive(0x03);               // in case of weekday
    if (weekday == 0x07)
      weekday = 0x01;
    else
      weekday++;
    TWI_transmit(0x03, weekday);
    break;
  case 0xC3:
    hour = TWI_receive(0x02) & 0x3F;           // in case of hour
    if (hour == 0x12)
      hour = 0x01;
    else if (hour == 0x32)
      hour = 0x21;
    else
      hour = BCD_increment(hour);
    TWI_transmit(0x02, hour | 0x40);
    break;
  case 0xC6:
    minute = TWI_receive(0x01);                // in case of minute
    if (minute == 0x59)
      minute = 0x00;
    else
      minute = BCD_increment(minute);
    TWI_transmit(0x01, minute);
    break;
  case 0xC9:
    second = TWI_receive(0x00);                // in case of second
    if (second == 0x59)
      second = 0x00;
    else
      second = BCD_increment(second);
    TWI_transmit(0x00, second);
    break;
  case 0xCC:
    hour = TWI_receive(0x02);                  // in case of AM/PM
    if ((hour & 0x20) == 0x20)
      hour &= 0xDF;
    else
      hour |= 0x20;
    TWI_transmit(0x02, hour);
    break;
  default:
    break;
  }
}

int main(void)
{
  MCU_initialize();                            // initialize AT91SAM7S256 & kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module

  LCD_string(0x80, " 2007/06/01 FRI ");        // display title
  LCD_string(0xC0, "  12:00:00 AM   ");
  Beep();

  LCD_command(0x0F);                           // cursor ON
  cursor = 0xCF;                               // initial cursor position

  AT91F_TWI_CfgPIO();                          // enable TWD, TWCK pin
  AT91F_PIO_Opendrain(AT91C_BASE_PIOA, AT91C_PA4_TWCK | AT91C_PA3_TWD); // open drain
  AT91F_TWI_CfgPMC();                          // enable peripheral clock for TWI

  AT91F_TWI_Configure(AT91C_BASE_TWI);         // TWI master mode
  *AT91C_TWI_CWGR = 0x00023B3B;                // about 100kHz

  RTC_check();                                 // check the status of DS1307 RTC

  while (1) {
    RTC_display();                             // display clock

    switch (Key_input()) {                     // key input
    case 0x01:
      Increment();                             // if KEY1, increment time
      break;
    case 0x02:
      Cursor_left();                           // if KEY2, go cursor left
      break;
    default:
      break;
    }
  }
}
