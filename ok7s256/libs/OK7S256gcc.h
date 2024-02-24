/***********************************************************************************/
/*    OK7S256gcc.h : Definition & User Function for OK-7S256 V1.0 Training Kit	   */
/***********************************************************************************/

#ifndef __OK7S256GCC_H__
#define __OK7S256GCC_H__

#include "lib_AT91SAM7S256gcc.h"

#define PA0 (1 << 0)                           // define bit number of PIO
#define PA1 (1 << 1)
#define PA2 (1 << 2)
#define PA7 (1 << 7)
#define PA8 (1 << 8)
#define PA15 (1 << 15)
#define PA17 (1 << 17)
#define PA18 (1 << 18)
#define PA19 (1 << 19)
#define PA20 (1 << 20)
#define PA21 (1 << 21)
#define PA22 (1 << 22)
#define PA23 (1 << 23)

#define LED1 PA0                               // LED1,2 output signal
#define LED2 PA1

#define SPEAKER PA0                            // speaker
#define BUZZER PA2                             // buzzer output signal

#define KEY1 PA7                               // KEY1,2 input signal
#define KEY2 PA8

#define CS1 PA15                               // SPI CS1 output signal

#define J3 PA17                                // J3 input signal
#define PCK1 PA17                              // PCK1 output signal

#define LCD_RS PA18                            // LCD output signal
#define LCD_E PA19
#define LCD_ALL (0xFF000000|LCD_E|LCD_RS)

#define GLCD_DI PA20                           // GLCD output signal
#define GLCD_E PA21
#define GLCD_CS1 PA22
#define GLCD_CS2 PA23
#define GLCD_ALL (0xFF000000|GLCD_CS2|GLCD_CS1|GLCD_E|GLCD_DI)

extern void Delay_1us(void);                   /* 1 us delay for -Os option */
extern void Delay_us(unsigned int us);         /* us delay for -Os option */
extern void Delay_ms(unsigned int ms);         /* ms delay for -Os option */
extern void LED_on(unsigned int led);          /* LED on */
extern void LED_off(unsigned int led);         /* LED off */
extern void Buzzer_on(void);                   /* buzzer on */
extern void Buzzer_off(void);                  /* buzzer off */
extern void Beep(void);                        /* beep for 50 ms */
extern void Error(void);                       /* beep 3 times */
extern void MCU_initialize(void);              /* initialize AT91SAM7S256 & OK-7S256 kit */
extern void LCD_command(unsigned int command); /* write a command(instruction) on text LCD */
extern void LCD_data(unsigned int data);       /* display a character on text LCD */
extern void LCD_initialize(void);              /* initialize text LCD module */
extern void LCD_string(unsigned int command, char *string); /* display a string on text LCD */
extern unsigned int Key_in(void);              /* input key KEY2 - KEY1 without debouncing */
extern unsigned int Key_input(void);           /* input key KEY2 - KEY1 with debouncing */

#endif /* __OK7S256GCC_H__ */
