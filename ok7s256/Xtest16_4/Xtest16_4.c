/* ========================================================================== */
/*   Xtest16_4.c : Digital Clock with Calendar on Graphic LCD by DS1307 RTC   */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <board.h>

#include <OK7S256gcc.h>
#include <OK7S256Korean.h>

unsigned int year, month, date, weekday;       // time variable
unsigned int second, minute, hour, ampm;

void GLCD_2BCD(unsigned int number)
{                                              /* display 2-digit BCD number */
  GLCD_English(0, (number >> 4) + '0');        // 10^1
  GLCD_English(0, (number & 0x0F) + '0');      // 10^0
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
  year = TWI_receive(0x06);                    // display year
  GLCD_xy(1, 3);
  GLCD_2BCD(year);

  month = TWI_receive(0x05);                   // display month
  GLCD_xy(1, 6);
  GLCD_2BCD(month);

  date = TWI_receive(0x04);                    // display date
  GLCD_xy(1, 9);
  GLCD_2BCD(date);

  weekday = TWI_receive(0x03);                 // display weekday
  if (weekday == 1)
    GLCD_string(1, 12, 0, "일");
  else if (weekday == 2)
    GLCD_string(1, 12, 0, "월");
  else if (weekday == 3)
    GLCD_string(1, 12, 0, "화");
  else if (weekday == 4)
    GLCD_string(1, 12, 0, "수");
  else if (weekday == 5)
    GLCD_string(1, 12, 0, "목");
  else if (weekday == 6)
    GLCD_string(1, 12, 0, "금");
  else
    GLCD_string(1, 12, 0, "토");

  hour = TWI_receive(0x02) & 0x3F;             // display hour
  if (hour > 0x20) {
    hour &= 0x1F;
    ampm = 'P';
  } else
    ampm = 'A';
  GLCD_xy(2, 2);
  GLCD_2BCD(hour);
  GLCD_xy(2, 11);
  GLCD_English(0, ampm);                       // display AM/PM
  GLCD_xy(2, 12);
  GLCD_English(0, 'M');

  minute = TWI_receive(0x01);                  // display minute
  GLCD_xy(2, 5);
  GLCD_2BCD(minute);

  second = TWI_receive(0x00);                  // display second
  GLCD_xy(2, 8);
  GLCD_2BCD(second);

  GLCD_xy(2, 15);
  GLCD_English(0, ' ');                        // display home position
  Delay_ms(10);                                // time delay for cursor

  if ((minute == 0x00) && (second == 0x00)) {  // beep for each o'clock
    Beep();
    Delay_ms(1000);
  }
}

void Cursor_left(void)
{                                              /* go cursor left */
  if ((xcursor == 2) && (ycursor == 15))
    ycursor = 12;
  else if ((xcursor == 2) && (ycursor == 12))
    ycursor = 9;
  else if ((xcursor == 2) && (ycursor == 9))
    ycursor = 6;
  else if ((xcursor == 2) && (ycursor == 6))
    ycursor = 3;
  else if ((xcursor == 2) && (ycursor == 3)) {
    xcursor = 1;
    ycursor = 12;
  } else if ((xcursor == 1) && (ycursor == 12))
    ycursor = 10;
  else if ((xcursor == 1) && (ycursor == 10))
    ycursor = 7;
  else if ((xcursor == 1) && (ycursor == 7))
    ycursor = 4;
  else if ((xcursor == 1) && (ycursor == 4)) {
    xcursor = 2;
    ycursor = 15;
  }
}

void Increment(void)
{                                              /* increment time */
  if (xcursor == 1)
    switch (ycursor) {
    case 4:
      year = TWI_receive(0x06);                // in case of year
      if (year == 0x99)
        year = 0x00;
      else
        year = BCD_increment(year);
      TWI_transmit(0x06, year);
      break;
    case 7:
      month = TWI_receive(0x05);               // in case of month
      if (month == 0x12)
        month = 0x01;
      else
        month = BCD_increment(month);
      TWI_transmit(0x05, month);
      break;
    case 10:
      date = TWI_receive(0x04);                // in case of date
      if (date == 0x31)
        date = 0x01;
      else
        date = BCD_increment(date);
      TWI_transmit(0x04, date);
      break;
    case 12:
      weekday = TWI_receive(0x03);             // in case of weekday
      if (weekday == 0x07)
        weekday = 0x01;
      else
        weekday++;
      TWI_transmit(0x03, weekday);
      break;
    default:
      break;
  } else if (xcursor == 2)
    switch (ycursor) {
    case 3:
      hour = TWI_receive(0x02) & 0x3F;         // in case of hour
      if (hour == 0x12)
        hour = 0x01;
      else if (hour == 0x32)
        hour = 0x21;
      else
        hour = BCD_increment(hour);
      TWI_transmit(0x02, hour | 0x40);
      break;
    case 6:
      minute = TWI_receive(0x01);              // in case of minute
      if (minute == 0x59)
        minute = 0x00;
      else
        minute = BCD_increment(minute);
      TWI_transmit(0x01, minute);
      break;
    case 9:
      second = TWI_receive(0x00);              // in case of second
      if (second == 0x59)
        second = 0x00;
      else
        second = BCD_increment(second);
      TWI_transmit(0x00, second);
      break;
    case 12:
      hour = TWI_receive(0x02);                // in case of AM/PM
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
  GLCD_clear();                                // initialize GLCD screen

  xcursor = 2;                                 // initial cursor position
  ycursor = 15;
  cursor_flag = 1;                             // cursor ON

  LCD_string(0x80, " Digital Clock  ");        // display title on text LCD
  LCD_string(0xC0, "    on GLCD     ");

  GLCD_string(0, 0, 0, "****************");    // display title on graphic LCD
  GLCD_string(1, 0, 0, " 2007/06/01(월) ");
  GLCD_string(2, 0, 0, "  12:00:00 AM   ");
  GLCD_string(3, 0, 0, "****************");
  Beep();

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
