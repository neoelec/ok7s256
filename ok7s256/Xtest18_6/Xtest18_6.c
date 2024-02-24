/* ========================================================================== */
/*          Xtest18_6.c : User-defined printf() Function for USART0           */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <stdio.h>
#include <board.h>

#include <OK7S256gcc.h>

unsigned int USART0_RX_char(void)
{                                              /* receive a character by USART0 */
  while (!(*AT91C_US0_CSR & 0x0001)) ;         // wait until RXRDY=1

  return *AT91C_US0_RHR;                       // receive a character
}

void USART0_TX_char(unsigned int data)
{                                              /* transmit a character by USART0 */
  while (!(*AT91C_US0_CSR & 0x0002)) ;         // wait until TXRDY=1

  *AT91C_US0_THR = data;                       // transmit a character
}

/* ===== System Call Reentrant Function ===================================== */

#include <reent.h>
#include <sys/stat.h>

_ssize_t _read_r(struct _reent *r, int file, void *ptr, size_t len)
{
  char c;
  int i;
  unsigned char *p;

  p = (unsigned char *)ptr;

  for (i = 0; i < len; i++) {
    c = USART0_RX_char();
    *p++ = c;
    USART0_TX_char(c);

    if (c == 0x0D && i <= (len - 2)) {
      *p = 0x0A;
      USART0_TX_char(0x0A);
      return i + 2;
    }
  }

  return i;
}

_ssize_t _write_r(struct _reent *r, int file, const void *ptr, size_t len)
{
  int i;
  const unsigned char *p;

  p = (const unsigned char *)ptr;

  for (i = 0; i < len; i++) {
    if (*p == '\n')
      USART0_TX_char('\r');
    USART0_TX_char(*p++);
  }

  return len;
}

int _close_r(struct _reent *r, int file)
{
  return 0;
}

_off_t _lseek_r(struct _reent *r, int file, _off_t ptr, int dir)
{
  return (_off_t) 0;
}

int _fstat_r(struct _reent *r, int file, struct stat *st)
{
  st->st_mode = S_IFCHR;
  return 0;
}

int isatty(int file)
{
  return 1;
}

extern char end[];

static char *heap_ptr;

void *_sbrk_r(struct _reent *_s_r, ptrdiff_t nbytes)
{
  char *base;

  if (!heap_ptr)
    heap_ptr = end;
  base = heap_ptr;
  heap_ptr += nbytes;

  return base;
}

/* ========================================================================== */

int main(void)
{
  unsigned int i;
  double x;

  MCU_initialize();                            // initialize AT91SAM7S256 & kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD
  Beep();

  LCD_string(0x80, "    printf()    ");        // display title
  LCD_string(0xC0, "   for USART0   ");

  AT91F_US0_CfgPMC();                          // enable clock of USART0
  AT91F_PIO_CfgPeriph(AT91C_BASE_PIOA, AT91C_PA6_TXD0 | AT91C_PA5_RXD0, 0);
  // TXD0, RXD0 by Peripheral A

  *AT91C_US0_MR = 0x100008C0;                  // normal mode, no parity
  // 8 data, 1 stop, LSB first, 16x
  *AT91C_US0_BRGR = 26;                        // MCK/16/26 = 115200 bps
  *AT91C_US0_CR = 0x00000150;                  // TX, RX enable

  while (1) {
    for (i = 1, x = 0.001; i <= 200; i++, x += 0.001) { // loop by 200 times
      printf("printf() function test for USART0 : %3d  %5.3f\n", i, x);
      Delay_ms(500);
    }
    Beep();
  }
}
