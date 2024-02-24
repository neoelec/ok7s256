/* ========================================================================== */
/*      Xtest15_3.c : AT93C56 Read/Write(ORG=1, 128x16 bit, 16-bit SPI)       */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <board.h>

#include <OK7S256gcc.h>

void LCD_2hex(unsigned int number)
{                                              /* display 2-digit hex number */
  unsigned char i;

  i = (number >> 4) & 0x0F;                    // 16^1
  if (i <= 9)
    LCD_data(i + '0');
  else
    LCD_data(i - 10 + 'A');

  i = number & 0x0F;                           // 16^0
  if (i <= 9)
    LCD_data(i + '0');
  else
    LCD_data(i - 10 + 'A');
}

void LCD_4hex(unsigned int number)
{                                              /* display 4-digit hex number */
  unsigned char i;

  i = (number >> 12) & 0x0F;                   // 16^3
  if (i <= 9)
    LCD_data(i + '0');
  else
    LCD_data(i - 10 + 'A');

  i = (number >> 8) & 0x0F;                    // 16^2
  if (i <= 9)
    LCD_data(i + '0');
  else
    LCD_data(i - 10 + 'A');

  i = (number >> 4) & 0x0F;                    // 16^1
  if (i <= 9)
    LCD_data(i + '0');
  else
    LCD_data(i - 10 + 'A');

  i = number & 0x0F;                           // 16^0
  if (i <= 9)
    LCD_data(i + '0');
  else
    LCD_data(i - 10 + 'A');
}

void AT93C56_EWEN(void)
{                                              /* write enable */
  AT91F_PIO_SetOutput(AT91C_BASE_PIOA, CS1);   // CS = 1

  AT91F_SPI_PutChar(AT91C_BASE_SPI, 0x04C0, 1); // 0000 0100 1100 0000
  while (!(*AT91C_SPI_SR & 0x0200)) ;          // transmit complete ?

  AT91F_PIO_ClearOutput(AT91C_BASE_PIOA, CS1); // CS = 0
}

void AT93C56_EWDS(void)
{                                              /* write disable */
  AT91F_PIO_SetOutput(AT91C_BASE_PIOA, CS1);   // CS = 1

  AT91F_SPI_PutChar(AT91C_BASE_SPI, 0x0400, 1); // 0000 0100 0000 0000
  while (!(*AT91C_SPI_SR & 0x0200)) ;          // transmit complete ?

  AT91F_PIO_ClearOutput(AT91C_BASE_PIOA, CS1); // CS = 0
}

void AT93C56_WRITE(unsigned int address, unsigned int byte2)
{                                              /* write 16 bit */
  AT91F_PIO_SetOutput(AT91C_BASE_PIOA, CS1);   // CS = 1

  AT91F_SPI_PutChar(AT91C_BASE_SPI, 0x0500 + address, 1); // 0000 0101 + A7~A0
  while (!(*AT91C_SPI_SR & 0x0200)) ;          // transmit complete ?
  AT91F_SPI_PutChar(AT91C_BASE_SPI, byte2, 1); // D15~D0
  while (!(*AT91C_SPI_SR & 0x0200)) ;          // transmit complete ?

  AT91F_PIO_ClearOutput(AT91C_BASE_PIOA, CS1); // CS = 0
  Delay_ms(10);                                // delay 10 ms for twp time
}

unsigned int AT93C56_READ(unsigned int address)
{                                              /* read a byte */
  AT91F_PIO_SetOutput(AT91C_BASE_PIOA, CS1);   // CS = 1

  AT91F_SPI_PutChar(AT91C_BASE_SPI, 0x0600 + address, 1); // 0000 0110 + A7~A0
  while (!(*AT91C_SPI_SR & 0x0200)) ;          // transmit complete ?
  AT91F_SPI_PutChar(AT91C_BASE_SPI, 0x0000, 1); // dummy data
  while (!(*AT91C_SPI_SR & 0x0200)) ;          // transmit complete ?

  AT91F_PIO_ClearOutput(AT91C_BASE_PIOA, CS1); // CS = 0
  return AT91F_SPI_GetChar(AT91C_BASE_SPI);    // read SPI_RDR and return
}

int main(void)
{
  unsigned int address, byte2;

  MCU_initialize();                            // initialize AT91SAM7S256 & kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD

  LCD_string(0x80, " AT93C56 0x00 = ");        // display title
  LCD_string(0xC0, "  0x0000/0x0000 ");
  Beep();

  AT91F_PIO_CfgOutput(AT91C_BASE_PIOA, CS1);   // PA15 output signal
  AT91F_PIO_ClearOutput(AT91C_BASE_PIOA, CS1); // CS1=0

  AT91F_PIO_CfgOutput(AT91C_BASE_PIOA, PA17);  // PA17=1 for ORG=1
  AT91F_PIO_SetOutput(AT91C_BASE_PIOA, PA17);

  AT91F_PIO_CfgPeriph(AT91C_BASE_PIOA, AT91C_PA12_MISO | AT91C_PA13_MOSI | AT91C_PA14_SPCK, 0);
  // MISO,MOSI,SPCK output(Peripheral A)

  AT91F_SPI_CfgPMC();                          // enable clock of SPI
  *AT91C_SPI_CR = 0x01000001;                  // enable SPI
  *AT91C_SPI_MR = 0x00010001;                  // master mode
  AT91F_SPI_CfgCs(AT91C_BASE_SPI, 1, 0x02003082); // CS1,1M bps,16 bit,NCPHA=1,CPOL=0

  AT93C56_EWEN();                              // AT93C56 write enable

  for (address = 0x00; address <= 0x7F; address++) {
    LCD_command(0x8B);                         // display address
    LCD_2hex(address);

    LCD_command(0xC4);                         // display write data
    LCD_4hex(0x5555);
    AT93C56_WRITE(address, 0x5555);            // write 0x5555
    byte2 = AT93C56_READ(address);
    LCD_command(0xCB);                         // display read data
    LCD_4hex(byte2);
    Delay_ms(500);
    if (byte2 != 0x5555) {                     // if error, beep
      Beep();
      Delay_ms(2000);
    }

    LCD_command(0xC4);                         // display write data
    LCD_4hex(0xAAAA);
    AT93C56_WRITE(address, 0xAAAA);            // write 0xAAAA
    byte2 = AT93C56_READ(address);
    LCD_command(0xCB);                         // display read data
    LCD_4hex(byte2);
    Delay_ms(500);
    if (byte2 != 0xAAAA) {                     // if error, beep
      Beep();
      Delay_ms(2000);
    }
  }

  AT93C56_EWDS();                              // AT93C56 write disable
  Beep();

  while (1) ;                                  // infinite loop
}
