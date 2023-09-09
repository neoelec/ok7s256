#ifndef __DELAY_H__
#define __DELAY_H__

extern void DELAY_1us(void);                   /* 1 us delay for -Os option */
extern void DELAY_us(unsigned int us);         /* us delay for -Os option */
extern void DELAY_ms(unsigned int ms);         /* ms delay for -Os option */

#endif /* __DELAY_H__ */
