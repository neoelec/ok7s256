/* ========================================================================== */
/*        Xtest05_2.c : Visiting Count on GLCD using Random Number(1)         */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <stdlib.h>
#include <board.h>

#include <OK7S256gcc.h>
#include <OK7S256GLCD.h>

int main(void)
{
  unsigned int i, j, seed, random, count, x, y, visit_flag;
  unsigned int table[8][20];                   // visiting room

  MCU_initialize();                            // initialize AT91SAM7S256 & kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD
  GLCD_clear();                                // initialize GLCD screen

  LCD_string(0x80, "Graphic LCD Test");        // display title on text LCD
  LCD_string(0xC0, " Visiting Count ");
  Beep();

  for (i = 0; i <= 7; i++)                     // clear visiting room
    for (j = 0; j <= 19; j++)
      table[i][j] = 0;
  visit_flag = 0;
  x = 4;                                       // starting position
  y = 10;

  seed = 1000;                                 // make seed of random number
  srand(seed);                                 // initialize random number

  while (visit_flag == 0) {
    random = rand();                           // get random number

    if (random <= 0x1FFFFFFF) {                // 0x00000000 - 0x1FFFFFFF
      if (y != 19) {
        y++;
        table[x][y] += 1;
      }
    } else if (random <= 0x3FFFFFFF) {         // 0x20000000 - 0x3FFFFFFF
      if (y != 0) {
        y--;
        table[x][y] += 1;
      }
    } else if (random <= 0x5FFFFFFF) {         // 0x40000000 - 0x5FFFFFFF
      if (x != 7) {
        x++;
        table[x][y] += 1;
      }
    } else {                                   // 0x60000000 - 0x7FFFFFFF
      if (x != 0) {
        x--;
        table[x][y] += 1;
      }
    }

    for (i = 0; i <= 7; i++)                   // display visiting count
      for (j = 0; j <= 19; j++) {
        count = table[i][j];
        if (count >= 62)
          count = '*';
        else if (count >= 36)
          count = count - 36 + 'a';
        else if (count >= 10)
          count = count - 10 + 'A';
        else
          count = count + '0';
        GLCD_xy(i, j);
        GLCD_English(0, count);
      }
    Delay_ms(100);

    visit_flag = 1;                            // check end
    for (i = 0; i <= 7; i++)
      for (j = 0; j <= 19; j++)
        if (table[i][j] == 0)
          visit_flag = 0;
  }

  Beep();                                      // OK sound
  LCD_string(0xC0, "  Visiting OK!  ");        // OK message
  while (1) ;
}
