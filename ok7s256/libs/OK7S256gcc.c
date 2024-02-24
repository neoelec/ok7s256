/***********************************************************************************/
/*    OK7S256gcc.c : Definition & User Function for OK-7S256 V1.0 Training Kit	   */
/***********************************************************************************/

#include <board.h>

#include "lib_AT91SAM7S256.h"
#include "OK7S256gcc.h"

void Delay_1us(void)
{                                              /* 1 us delay for -Os option */
  volatile unsigned int count;

  for (count = 0; count < 1; count++) ;
}

void Delay_us(unsigned int us)
{                                              /* us delay for -Os option */
  volatile unsigned int count, countmax = (BOARD_MCK / 24000000) * us;

  for (count = 0; count < countmax; count++) ;
}

void Delay_ms(unsigned int ms)
{                                              /* ms delay for -Os option */
  volatile unsigned int count, countmax = (BOARD_MCK / 25000) * ms;

  for (count = 0; count < countmax; count++) ;
}

void LED_on(unsigned int led)
{                                              /* LED on */
  AT91F_PIO_CfgOutput(AT91C_BASE_PIOA, LED2 | LED1);  // PA1-PA0 = output
  AT91F_PIO_ClearOutput(AT91C_BASE_PIOA, led);
}

void LED_off(unsigned int led)
{                                              /* LED off */
  AT91F_PIO_CfgOutput(AT91C_BASE_PIOA, LED2 | LED1);  // PA1-PA0 = output
  AT91F_PIO_SetOutput(AT91C_BASE_PIOA, led);
}

void Buzzer_on(void)
{                                              /* buzzer on */
  AT91F_PIO_ClearOutput(AT91C_BASE_PIOA, BUZZER);
}

void Buzzer_off(void)
{                                              /* buzzer off */
  AT91F_PIO_SetOutput(AT91C_BASE_PIOA, BUZZER);
}

void Beep(void)
{                                              /* beep for 50 ms */
  Buzzer_on();
  Delay_ms(50);
  Buzzer_off();
}

void Error(void)
{                                              /* beep 3 times */
  Beep();
  Delay_ms(50);
  Beep();
  Delay_ms(50);
  Beep();
}

void MCU_initialize(void)
{                                              /* initialize AT91SAM7S256 & OK-7S256 kit */
  AT91F_RSTSetMode(AT91C_BASE_RSTC, AT91C_RSTC_URSTEN); // enable User Reset by NRST pin input

  AT91F_PIOA_CfgPMC();                         // enable clock of PIO

  AT91F_PIO_CfgOutput(AT91C_BASE_PIOA, LED2 | LED1);  // PA1-PA0 = output
  LED_off(LED2 | LED1);                        // LED2-LED1 off

  AT91F_PIO_CfgOutput(AT91C_BASE_PIOA, BUZZER); // PA2 = output
  Buzzer_off();                                // buzzer off

  AT91F_PIO_CfgInput(AT91C_BASE_PIOA, J3 | KEY2 | KEY1);  // PA17,PA8,PA7 = input with pullup
  AT91F_PIO_Pullup(AT91C_BASE_PIOA, J3 | KEY2 | KEY1);

  AT91F_PIO_CfgOutput(AT91C_BASE_PIOA, LCD_ALL);  // open drain output for LCD
  AT91F_PIO_ClearOutput(AT91C_BASE_PIOA, LCD_ALL);
  AT91F_PIO_Opendrain(AT91C_BASE_PIOA, LCD_ALL);

  AT91F_PIO_CfgOutput(AT91C_BASE_PIOA, GLCD_ALL); // open drain output for GLCD
  AT91F_PIO_ClearOutput(AT91C_BASE_PIOA, GLCD_ALL);
  AT91F_PIO_Opendrain(AT91C_BASE_PIOA, GLCD_ALL);
}

void LCD_command(unsigned int command)
{                                              /* write a command(instruction) on text LCD */
  AT91F_PIO_ClearOutput(AT91C_BASE_PIOA, LCD_RS); // RS = 0
  AT91F_PIO_SetOutput(AT91C_BASE_PIOA, command << 24);  // output command
  AT91F_PIO_ClearOutput(AT91C_BASE_PIOA, (~command) << 24);

  AT91F_PIO_SetOutput(AT91C_BASE_PIOA, LCD_E); // E = 1
  Delay_1us();
  AT91F_PIO_ClearOutput(AT91C_BASE_PIOA, LCD_E);  // E = 0

  if (command & 0xFC)                          // wait for operation
    Delay_us(50);
  else
    Delay_ms(2);
}

void LCD_data(unsigned int data)
{                                              /* display a character on text LCD */
  AT91F_PIO_SetOutput(AT91C_BASE_PIOA, LCD_RS); // RS = 1
  AT91F_PIO_SetOutput(AT91C_BASE_PIOA, data << 24); // output data
  AT91F_PIO_ClearOutput(AT91C_BASE_PIOA, (~data) << 24);

  AT91F_PIO_SetOutput(AT91C_BASE_PIOA, LCD_E); // E = 1
  Delay_1us();
  AT91F_PIO_ClearOutput(AT91C_BASE_PIOA, LCD_E);  // E = 0

  Delay_us(50);                                // wait for operation
}

void LCD_initialize(void)
{                                              /* initialize text LCD module */
  AT91F_PIO_CfgOutput(AT91C_BASE_PIOA, LCD_ALL);  // open drain output
  AT91F_PIO_ClearOutput(AT91C_BASE_PIOA, LCD_ALL);
  AT91F_PIO_Opendrain(AT91C_BASE_PIOA, LCD_ALL);
  Delay_ms(2);

  LCD_command(0x38);                           // function set(8 bit, 2 line, 5x7 dot)
  LCD_command(0x0C);                           // display control(display on, cursor off)
  LCD_command(0x06);                           // entry mode set(increment, not shift)
  LCD_command(0x01);                           // clear display
}

void LCD_string(unsigned int command, char *string)
{                                              /* display a string on text LCD */
  LCD_command(command);                        // cursor position

  while (*string != '\0') {                    // display string
    LCD_data(*string);
    string++;
  }
}

static unsigned char key_flag = 0;

unsigned int Key_in(void)
{                                              /* input key KEY2 - KEY1 without debouncing */
  unsigned int keycode;                        //   (no input = 0, KEY1 = 1, KEY2 = 2)

  AT91F_PIO_CfgInput(AT91C_BASE_PIOA, KEY2 | KEY1); // PA8,PA7 = input with pullup
  AT91F_PIO_Pullup(AT91C_BASE_PIOA, KEY2 | KEY1);

  keycode = (~(AT91F_PIO_GetInput(AT91C_BASE_PIOA) >> 7)) & 0x00000003;

  return keycode;
}

unsigned int Key_input(void)
{                                              /* input key KEY2 - KEY1 with debouncing */
  unsigned int key;                            //   (no input = 0, KEY1 = 1, KEY2 = 2)

  key = Key_in();                              // any key pressed ?
  if (key == 0) {                              // if no key, check key off
    if (key_flag == 0)
      return key;
    else {
      Delay_ms(20);
      key_flag = 0;
      return key;
    }
  } else {                                     // if key input, check continuous key
    if (key_flag != 0)                         // if continuous key, treat as no key input
      return 0;
    else {                                     // if new key, beep and delay for debounce
      Beep();
      key_flag = 1;
      return key;
    }
  }
}
