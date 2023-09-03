/* ========================================================================== */
/*        Xtest18_8.c : User-defined printf() Function for Graphic LCD        */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <stdio.h>
#include <board.h>

#include <OK7S256gcc.h>
#include <OK7S256Korean.h>

/* ===== System Call Reentrant Function ===================================== */

#include <reent.h>
#include <sys/stat.h>

_ssize_t _read_r(struct _reent *r, int file, void *ptr, size_t len)
{
  return 0;
}

_ssize_t _write_r(struct _reent *r, int file, const void *ptr, size_t len)
{
  int i;
  const unsigned char *p;

  p = (const unsigned char *)ptr;

  for (i = 0; i < len; i++)
    if ((*p >= 0x20) && (*p <= 0x7E))
      GLCD_English(0, *p++);

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
  GLCD_clear();                                // initialize GLCD screen
  Beep();

  LCD_string(0x80, "    printf()    ");        // display title on text LCD
  LCD_string(0xC0, "    for GLCD    ");

  GLCD_string(0, 0, 1, " printf() 함수  ");  // display title on graphic LCD
  GLCD_string(1, 0, 0, "                ");
  GLCD_string(2, 0, 0, "  정수 =   000  ");
  GLCD_string(3, 0, 0, "  실수 = 0.000  ");

  while (1) {
    for (i = 1, x = 0.001; i <= 200; i++, x += 0.001) { // loop by 200 times
      GLCD_xy(2, 11);
      printf("%3d\n", i);
      GLCD_xy(3, 9);
      printf("%5.3f\n", x);
      Delay_ms(500);
    }
    Beep();
  }
}
