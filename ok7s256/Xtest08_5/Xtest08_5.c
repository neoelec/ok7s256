/* ========================================================================== */
/*       Xtest08_5.c : Key Input Count with Debouncing by PIO Interrupt       */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <board.h>

#include <OK7S256gcc.h>

void LCD_3d(unsigned int number)
{                                              /* display 3-digit decimal number */
  unsigned int i, flag;

  flag = 0;
  i = number / 100;                            // 10^2
  if (i == 0)
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

unsigned int key1 = 0, key2 = 0;               // key input counter

void PIO_ISR(void)
{                                              /* PIO interrupt service routine */
  unsigned int status;

  Delay_ms(20);                                // delay for debouncing
  status = (AT91F_PIO_GetInput(AT91C_BASE_PIOA) >> 7) & 0x00000003;
  if (status == 3) {                           // if key off, don't count and return
    status = AT91F_PIO_GetInterruptStatus(AT91C_BASE_PIOA);
    return;
  } else                                       // if key on, beep and count
    Beep();

  status = (AT91F_PIO_GetInterruptStatus(AT91C_BASE_PIOA) >> 7) & 0x00000003;
  if (status == 1) {                           // if KEY1, display KEY1 count
    key1++;                                    // increment and display count
    if (key1 > 999)
      key1 = 0;
    LCD_command(0x8A);
    LCD_3d(key1);
  } else if (status == 2) {                    // if KEY2, display KEY2 count
    key2++;
    if (key2 > 999)
      key2 = 0;
    LCD_command(0xCA);
    LCD_3d(key2);
  }
}

int main(void)
{
  MCU_initialize();                            // initialize AT91SAM7S256 & kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD

  LCD_string(0x80, "   KEY1 = 000   ");        // display title on text LCD
  LCD_string(0xC0, "   KEY2 = 000   ");
  Beep();

  AT91F_PIO_InputFilterEnable(AT91C_BASE_PIOA, KEY2 | KEY1);  // initialize PIO interrupt
  AT91F_PIO_InterruptEnable(AT91C_BASE_PIOA, KEY2 | KEY1);
  AT91F_AIC_ConfigureIt(AT91C_BASE_AIC, AT91C_ID_PIOA, 7, 1, PIO_ISR);
  AT91F_AIC_EnableIt(AT91C_BASE_AIC, AT91C_ID_PIOA);

  while (1) ;                                  // wait for interrupts
}
