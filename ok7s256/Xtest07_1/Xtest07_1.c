/* ========================================================================== */
/*           Xtest07_1.c : English/Korean Language Display on GLCD            */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <board.h>

#include <OK7S256gcc.h>
#include <OK7S256Korean.h>

int main(void)
{
  unsigned int i;

  MCU_initialize();                            // initialize AT91SAM7S256 & kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD
  GLCD_clear();                                // initialize GLCD screen

  LCD_string(0x80, "Graphic LCD Test");        // display title on text LCD
  LCD_string(0xC0, " Englisk/Korean ");

  while (1) {
    Beep();
    GLCD_string(0, 0, 0, "ARM7 마스터 키트");  // display screen 1
    GLCD_string(1, 0, 1, " OK-7S256  V1.0 ");
    GLCD_string(2, 0, 0, "   2007/06/01   ");
    GLCD_string(3, 0, 0, "윤덕용 설계,제작");
    Delay_ms(5000);

    Beep();
    GLCD_string(0, 0, 0, "    현대 LCD    "); // display screen 2
    GLCD_string(1, 0, 1, "  HG12605NY-LY  ");
    GLCD_string(2, 0, 0, "                ");
    GLCD_string(3, 0, 2, "128x64 그래픽LCD");
    Delay_ms(5000);

    Beep();
    GLCD_string(0, 0, 0, " 3가지 문자속성 "); // display screen 3
    GLCD_string(1, 0, 0, "문자속성0 : 정상");
    GLCD_string(2, 0, 0, "문자속성1 : ");
    GLCD_string(2, 12, 1, "역상");
    GLCD_string(3, 0, 0, "문자속성2 : ");
    GLCD_string(3, 12, 2, "밑줄");
    Delay_ms(5000);

    Beep();
    GLCD_xy(0, 0);                             // display screen 4
    for (i = 0x00; i <= 0x3F; i++)             // (from 0x00 to 0x3F)
      GLCD_English(0, i);
    Delay_ms(5000);
    GLCD_xy(0, 0);                             // display screen 5
    for (i = 0x40; i <= 0x7F; i++)             // (from 0x40 to 0x7F)
      GLCD_English(1, i);
    Delay_ms(5000);
  }
}
