/* ========================================================================== */
/*           Xtest18_5.c : User-defined printf() Function for DBGU            */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <stdio.h>
#include <board.h>

#include <OK7S256gcc.h>

unsigned int DBGU_RX_char(void)
{                                              /* receive a character by DBGU */
  while (!(*AT91C_DBGU_CSR & 0x0001)) ;        // wait until RXRDY=1

  return *AT91C_DBGU_RHR;                      // receive a character
}

void DBGU_TX_char(unsigned int data)
{                                              /* transmit a character by DBGU */
  while (!(*AT91C_DBGU_CSR & 0x0002)) ;        // wait until TXRDY=1

  *AT91C_DBGU_THR = data;                      // transmit a character
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
    c = DBGU_RX_char();
    *p++ = c;
    DBGU_TX_char(c);

    if (c == 0x0D && i <= (len - 2)) {
      *p = 0x0A;
      DBGU_TX_char(0x0A);
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
      DBGU_TX_char('\r');
    DBGU_TX_char(*p++);
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
  LCD_string(0xC0, "    for DBGU    ");

  AT91F_DBGU_CfgPMC();                         // enable clock of DBGU
  AT91F_DBGU_CfgPIO();                         // DTXD, DRXD by Peripheral A

  *AT91C_DBGU_MR = 0x00000800;                 // normal mode, no parity
  *AT91C_DBGU_BRGR = 26;                       // MCK/16/26 = 115200 bps
  *AT91C_DBGU_CR = 0x00000150;                 // TX, RX enable

  while (1) {
    for (i = 1, x = 0.001; i <= 200; i++, x += 0.001) { // loop by 200 times
      printf("printf() function test for DBGU : %3d  %5.3f\n", i, x);
      Delay_ms(500);
    }
    Beep();
  }
}
