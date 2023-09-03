/* ========================================================================== */
/*                      Xtest13_1.c : Play Music Melody                       */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <board.h>

#include <OK7S256gcc.h>
#include <OK7S256music.h>

int main(void)
{
  MCU_initialize();                            // initialize AT91SAM7S256 & kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD

  LCD_string(0x80, "** MUSIC PLAY **");        // display title

  while (1) {
    LCD_string(0xC0, "PongdangPongdang");      // display music title
    Set_tempo(4);                              // set tempo

    Play_note(MIC, NOTE8);                     // line 1
    Play_note(MID, NOTE8);
    Play_note(MIE, NOTE8);
    Play_note(MIE, NOTE8);
    Play_note(MIC, NOTE8);
    Play_note(MIE, NOTE8);
    Play_note(MIG, NOTE16);
    Play_note(MIA, NOTE16);
    Play_note(MIG, NOTE8);
    Play_note(MIC, NOTE8);
    Play_note(MID, NOTE8);
    Play_note(MIE, NOTE8);
    Play_note(MIE, NOTE8);
    Play_note(MIC, NOTE8);
    Play_note(MIE, NOTE8);
    Play_note(MIG, NOTE16);
    Play_note(MIA, NOTE16);
    Play_note(MIG, NOTE8);
    Play_note(MIA, NOTE4);                     // line 2
    Play_note(MIG, NOTE8);
    Play_note(MIE, NOTE8);
    Play_note(MIA, NOTE4);
    Play_note(MIG, NOTE8);
    Play_note(MIE, NOTE8);
    Play_note(MID, NOTE8);
    Play_note(MID, NOTE8);
    Play_note(MIC, NOTE8);
    Play_note(MID, NOTE8);
    Play_note(MIE, NOTE8);
    Play_note(MIG, NOTE8);
    Play_note(MIG, NOTE4);
    Play_note(MIA, NOTE8D);                    // line 3
    Play_note(MIA, NOTE16);
    Play_note(MIG, NOTE8);
    Play_note(MIA, NOTE8);
    Play_note(HIC, NOTE8);
    Play_note(HIC, NOTE8);
    Play_note(HIC, NOTE8);
    Play_rest(REST8);
    Play_note(MIG, NOTE8D);
    Play_note(MIG, NOTE16);
    Play_note(MIE, NOTE8);
    Play_note(MID, NOTE8);
    Play_note(MIC, NOTE4D);
    Play_rest(REST8);
    Play_note(MID, NOTE8D);                    // line 4
    Play_note(MIE, NOTE16);
    Play_note(MIC, NOTE8);
    Play_note(MIE, NOTE8);
    Play_note(MIG, NOTE8);
    Play_note(MIG, NOTE8);
    Play_note(MIG, NOTE4);
    Play_note(MID, NOTE8);
    Play_note(MIE, NOTE16);
    Play_note(MIF, NOTE16);
    Play_note(MIE, NOTE8);
    Play_note(MID, NOTE8);
    Play_note(MIC, NOTE4D);
    Play_rest(REST8);
    Delay_ms(1000);

    LCD_string(0xC0, "     Age 18     ");      // display music title
    Set_tempo(3);                              // set tempo

    Play_note(MIG, NOTE4D);                    // line 1
    Play_note(MIG, NOTE16);
    Play_note(MIA, NOTE16);
    Play_note(MIG, NOTE8);
    Play_note(MIE, NOTE8);
    Play_note(MIC, NOTE4);
    Play_note(HIC, NOTE8);
    Play_note(HIC, NOTE16);
    Play_note(HID, NOTE16);
    Play_note(HIC, NOTE8);
    Play_note(MIB, NOTE8);
    Play_note(MIA, NOTE2);
    Play_note(MIG, NOTE4D);                    // line 2
    Play_note(MIG, NOTE16);
    Play_note(MIA, NOTE16);
    Play_note(MIG, NOTE8);
    Play_note(MIE, NOTE8);
    Play_note(MIC, NOTE8);
    Play_note(MIE, NOTE8);
    Play_note(MID, NOTE8);
    Play_note(MID, NOTE8);
    Play_note(MID, NOTE8);
    Play_note(MID, NOTE8);
    Play_note(MID, NOTE2);
    Play_note(MIG, NOTE4D);                    // line 3
    Play_note(MIG, NOTE16);
    Play_note(MIA, NOTE16);
    Play_note(MIG, NOTE8);
    Play_note(MIE, NOTE8);
    Play_note(MIC, NOTE4);
    Play_note(HIC, NOTE8);
    Play_note(HIC, NOTE16);
    Play_note(HID, NOTE16);
    Play_note(HIC, NOTE8);
    Play_note(MIB, NOTE8);
    Play_note(MIA, NOTE2);
    Play_note(MIG, NOTE8);                     // line 4
    Play_note(HIE, NOTE4);
    Play_note(HIC, NOTE8);
    Play_note(HID, NOTE8D);
    Play_note(HIC, NOTE16);
    Play_note(MIG, NOTE8);
    Play_note(MIA, NOTE8);
    Play_note(HIC, NOTE8);
    Play_note(HIC, NOTE8);
    Play_note(HIC, NOTE8);
    Play_note(HIC, NOTE8);
    Play_note(HIC, NOTE2);
    Play_note(MIG, NOTE4D);                    // line 5
    Play_note(HIE, NOTE8);
    Play_note(HIC, NOTE4);
    Play_note(MIG, NOTE8);
    Play_note(MIE, NOTE8);
    Play_note(MIC, NOTE2D);
    Play_rest(REST8);
    Play_note(MIG, NOTE4D);                    // line 6
    Play_note(HIG, NOTE8);
    Play_note(HIE, NOTE4);
    Play_note(HID, NOTE8);
    Play_note(HIC, NOTE8);
    Play_note(MIA, NOTE8);
    Play_note(HIC, NOTE2D);
    Play_note(MIG, NOTE4D);                    // line 7
    Play_note(MIG, NOTE16);
    Play_note(MIA, NOTE16);
    Play_note(MIG, NOTE8);
    Play_note(MIE, NOTE8);
    Play_note(MIC, NOTE4);
    Play_note(HIC, NOTE8);
    Play_note(HIC, NOTE16);
    Play_note(HID, NOTE16);
    Play_note(HIC, NOTE8);
    Play_note(MIB, NOTE8);
    Play_note(MIA, NOTE2);
    Play_note(MIG, NOTE8);                     // line 8
    Play_note(HIE, NOTE4);
    Play_note(HIC, NOTE8);
    Play_note(HID, NOTE8D);
    Play_note(HIC, NOTE16);
    Play_note(MIG, NOTE8);
    Play_note(MIA, NOTE8);
    Play_note(HIC, NOTE8);
    Play_note(HIC, NOTE8);
    Play_note(HIC, NOTE8);
    Play_note(HIC, NOTE8);
    Play_note(HIC, NOTE2);
    Delay_ms(1000);

    LCD_string(0xC0, "Triangle Rotary ");      // display music title
    Set_tempo(5);                              // set tempo

    Play_note(MIC, NOTE4);                     // prelude
    Play_note(MIC, NOTE16);
    Play_note(MID, NOTE16);
    Play_note(MIE, NOTE16);
    Play_note(MIG, NOTE16);
    Play_note(HIE, NOTE4D);
    Play_note(HID, NOTE8);
    Play_note(HIC, NOTE4);
    Play_note(MIA, NOTE16);
    Play_note(MIG, NOTE16);
    Play_note(MIE, NOTE16);
    Play_note(MIA, NOTE16);
    Play_note(MIG, NOTE2);
    Play_note(HIC, NOTE8);
    Play_note(MIA, NOTE16);
    Play_note(HIC, NOTE16);
    Play_note(MIA, NOTE8);
    Play_note(MIG, NOTE8);
    Play_note(MIE, NOTE4);
    Play_note(MIG, NOTE16);
    Play_note(MIE, NOTE16);
    Play_note(MID, NOTE16);
    Play_note(MIE, NOTE16);
    Play_note(MIC, NOTE2D);
    Play_rest(REST8);                          // line 1
    Play_note(MIC, NOTE8);
    Play_note(MIC, NOTE8);
    Play_note(MID, NOTE8);
    Play_note(MIE, NOTE4);
    Play_note(MIG, NOTE8);
    Play_note(MIA, NOTE8);
    Play_note(MIG, NOTE1);
    Play_note(MIE, NOTE8);
    Play_note(MIG, NOTE8);
    Play_note(MIA, NOTE8);
    Play_note(HIC, NOTE8);
    Play_note(HIE, NOTE4);
    Play_note(HID, NOTE8);
    Play_note(HIC, NOTE8);
    Play_note(HID, NOTE2D);
    Play_rest(REST8);
    Play_note(HIE, NOTE4D);                    // line 2
    Play_note(HID, NOTE8);
    Play_note(HIC, NOTE4);
    Play_note(MIA, NOTE16);
    Play_note(HIC, NOTE16);
    Play_note(MIA, NOTE16);
    Play_note(MIG, NOTE16);
    Play_rest(REST8);
    Play_note(MIE, NOTE16);
    Play_note(MIG, NOTE16);
    Play_note(MIA, NOTE16);
    Play_note(HIC, NOTE16);
    Play_note(MIA, NOTE8);
    Play_note(MIG, NOTE2);
    Play_rest(REST8);
    Play_note(LOA, NOTE8);
    Play_note(LOA, NOTE8);
    Play_note(MIC, NOTE8);
    Play_note(MID, NOTE4);
    Play_note(MIE, NOTE16);
    Play_note(MID, NOTE16);
    Play_note(MIC, NOTE16);
    Play_note(LOA, NOTE16);
    Play_note(MIC, NOTE2D);
    Play_rest(REST8);
    Play_note(MID, NOTE4D);                    // line 3
    Play_note(MIE, NOTE8);
    Play_note(MID, NOTE4);
    Play_note(MIC, NOTE8);
    Play_note(MID, NOTE8);
    Play_rest(REST8);
    Play_note(MIE, NOTE8);
    Play_note(MIG, NOTE8);
    Play_note(MIA, NOTE8);
    Play_note(HIC, NOTE2);
    Play_rest(REST8);
    Play_note(MIG, NOTE8);
    Play_note(HIC, NOTE8);
    Play_note(HID, NOTE8);
    Play_note(HIE, NOTE4);
    Play_note(HID, NOTE16T);
    Play_note(HIE, NOTE16T);
    Play_note(HID, NOTE16T);
    Play_note(HIC, NOTE16);
    Play_note(HID, NOTE16);
    Play_note(HIE, NOTE2D);
    Play_rest(REST8);
    Play_note(HIF, NOTE4D);                    // line 4
    Play_note(HIE, NOTE8);
    Play_note(HID, NOTE4);
    Play_note(HIC, NOTE4);
    Play_rest(REST8);
    Play_note(MIA, NOTE8);
    Play_note(MIG, NOTE8);
    Play_note(HID, NOTE8);
    Play_note(HIC, NOTE4);
    Play_note(MIA, NOTE8);
    Play_note(MIG, NOTE8);
    Play_rest(REST8);
    Play_note(MIE, NOTE16);
    Play_note(MIE, NOTE16);
    Play_note(MID, NOTE8);
    Play_note(MIA, NOTE8);
    Play_note(MIG, NOTE4);
    Play_note(MIE, NOTE16T);
    Play_note(MIF, NOTE16T);
    Play_note(MIE, NOTE16T);
    Play_note(MID, NOTE8);
    Play_note(MIC, NOTE2D);
    Delay_ms(1000);

    LCD_string(0xC0, "  Chil-Gab San  ");      // display music title
    Set_tempo(4);                              // set tempo

    Play_note(HIG, NOTE16);                    // prelude line 1
    Play_note(HIAX, NOTE16);
    Play_note(HIG, NOTE2);
    Play_note(HIG, NOTE16);
    Play_note(HIF, NOTE16);
    Play_note(HID, NOTE16);
    Play_note(HIF, NOTE16);
    Play_note(HIG, NOTE16);
    Play_note(HIAX, NOTE16);
    Play_note(HIG, NOTE2D);
    Play_note(HID, NOTE16);
    Play_note(HIF, NOTE16);
    Play_note(HID, NOTE2);
    Play_note(HID, NOTE16);
    Play_note(HID, NOTE16);
    Play_note(HIC, NOTE16);
    Play_note(HID, NOTE16);
    Play_note(HIG, NOTE16);
    Play_note(HIF, NOTE16);
    Play_note(HID, NOTE2D);
    Play_rest(REST32);
    Play_note(MID, NOTE4D);                    // prelude line 2
    Play_note(MID, NOTE8);
    Play_note(MIF, NOTE8);
    Play_note(MID, NOTE16);
    Play_note(MIF, NOTE16);
    Play_note(MIG, NOTE2);
    Play_note(MIAX, NOTE4);
    Play_note(MIG, NOTE2);
    Play_note(HIG, NOTE16);
    Play_note(HIF, NOTE16);
    Play_note(HID, NOTE16);
    Play_note(HIF, NOTE16);
    Play_note(HIG, NOTE16);
    Play_note(HIAX, NOTE16);
    Play_note(HIG, NOTE2);
    Play_rest(REST8);
    Play_note(HID, NOTE4);                     // line 1
    Play_note(HID, NOTE2);
    Play_note(HID, NOTE16);
    Play_note(HIF, NOTE16);
    Play_note(HID, NOTE16);
    Play_note(HIC, NOTE16);
    Play_note(HID, NOTE2);
    Play_note(HIC, NOTE8);
    Play_note(MIAX, NOTE8);
    Play_note(HIC, NOTE8);
    Play_note(HID, NOTE8);
    Play_note(MIAX, NOTE8T);
    Play_note(MIA, NOTE8T);
    Play_note(MIG, NOTE8T);
    Play_note(MID, NOTE2);
    Play_rest(REST8);
    Play_note(MID, NOTE8);                     // line 2
    Play_note(MIF, NOTE8);
    Play_note(MIG, NOTE8);
    Play_note(MIAX, NOTE8);
    Play_note(HIC, NOTE8);
    Play_note(HID, NOTE8);
    Play_note(HIC, NOTE2);
    Play_note(HIC, NOTE8T);
    Play_note(MIAX, NOTE8T);
    Play_note(HIC, NOTE8T);
    Play_note(HID, NOTE1);
    Play_rest(REST4);
    Play_note(HID, NOTE4);                     // line 3
    Play_note(HID, NOTE4);
    Play_note(HIF, NOTE4);
    Play_note(HIG, NOTE2);
    Play_note(HIF, NOTE4);
    Play_note(HID, NOTE4);
    Play_note(HIF, NOTE4);
    Play_note(HID, NOTE8);
    Play_note(HIC, NOTE8);
    Play_note(HID, NOTE2);
    Play_rest(REST8);
    Play_note(HIC, NOTE8);                     // line 4
    Play_note(MIAX, NOTE8);
    Play_note(HIC, NOTE8);
    Play_note(HID, NOTE8);
    Play_note(MIAX, NOTE8T);
    Play_note(MIA, NOTE8T);
    Play_note(MIG, NOTE8T);
    Play_note(MID, NOTE2);
    Play_note(MIAX, NOTE8);
    Play_note(MIA, NOTE8);
    Play_note(MIG, NOTE1);
    Play_rest(REST4);
    Play_note(MIA, NOTE4D);                    // line 5
    Play_note(MIAX, NOTE8);
    Play_note(HIC, NOTE8);
    Play_note(MIAX, NOTE8);
    Play_note(MIA, NOTE4D);
    Play_note(HID, NOTE8);
    Play_note(HID, NOTE4);
    Play_note(MIG, NOTE4);
    Play_note(MIG, NOTE4);
    Play_note(MIG, NOTE8);
    Play_note(MIF, NOTE8);
    Play_note(MIG, NOTE2);
    Play_rest(REST4);
    Play_note(MIG, NOTE4);                     // line 6
    Play_note(MIAX, NOTE4);
    Play_note(HIC, NOTE4);
    Play_note(HID, NOTE4D);
    Play_note(HIF, NOTE8);
    Play_note(HIG, NOTE8);
    Play_note(HIF, NOTE8);
    Play_note(HID, NOTE1);
    Play_rest(REST4);
    Play_note(HIG, NOTE4D);                    // line 7
    Play_note(HIF, NOTE8);
    Play_note(HIG, NOTE8);
    Play_note(HIF, NOTE8);
    Play_note(HID, NOTE2D);
    Play_note(HIC, NOTE8);
    Play_note(MIAX, NOTE8);
    Play_note(HIC, NOTE8);
    Play_note(HID, NOTE8);
    Play_note(MIAX, NOTE8T);
    Play_note(MIA, NOTE8T);
    Play_note(MIG, NOTE8T);
    Play_note(MID, NOTE2);
    Play_rest(REST8);
    Play_note(MID, NOTE8);                     // line 8
    Play_note(MIF, NOTE8);
    Play_note(MIG, NOTE8);
    Play_note(MIAX, NOTE8);
    Play_note(HIC, NOTE8);
    Play_note(HID, NOTE8);
    Play_note(HIC, NOTE2);
    Play_note(MIAX, NOTE8T);
    Play_note(HIC, NOTE8T);
    Play_note(MIAX, NOTE8T);
    Play_note(MIG, NOTE1);
    Play_rest(REST1);
    Delay_ms(1000);

    LCD_string(0xC0, "   Empty Sky    ");      // display music title
    Set_tempo(4);                              // set tempo

    Play_note(MIA, NOTE8);                     // line 1
    Play_note(MIB, NOTE8);
    Play_note(MIFX, NOTE4D);
    Play_note(MIE, NOTE16);
    Play_note(MID, NOTE16);
    Play_note(MIFX, NOTE2D);
    Play_note(MIE, NOTE8);
    Play_note(MIFX, NOTE8);
    Play_note(MIE, NOTE8);
    Play_note(MID, NOTE8);
    Play_note(LOB, NOTE8);
    Play_note(MID, NOTE8);
    Play_note(LOA, NOTE2D);
    Play_note(MID, NOTE8);                     // line 2
    Play_note(LOA, NOTE8);
    Play_note(MID, NOTE8);
    Play_note(MIE, NOTE8);
    Play_note(MIFX, NOTE8);
    Play_note(MIA, NOTE8);
    Play_note(MIB, NOTE2);
    Play_note(MIFX, NOTE8);
    Play_note(MIA, NOTE1);
    Play_rest(REST4);
    Play_note(MID, NOTE8);                     // line 3
    Play_note(MID, NOTE8);
    Play_note(HID, NOTE4D);
    Play_note(HID, NOTE8);
    Play_note(HID, NOTE2D);
    Play_note(MIB, NOTE8);
    Play_note(HID, NOTE8);
    Play_note(MIB, NOTE4D);
    Play_note(MIA, NOTE8);
    Play_note(MIFX, NOTE2D);
    Play_note(MIE, NOTE8);                     // line 4
    Play_note(MIE, NOTE8);
    Play_note(MIE, NOTE4D);
    Play_note(MIB, NOTE8);
    Play_note(MIA, NOTE8);
    Play_note(MIFX, NOTE8);
    Play_note(MIFX, NOTE4D);
    Play_note(MIE, NOTE8);
    Play_note(MID, NOTE1);
    Play_rest(REST4);
    Play_note(HID, NOTE8);                     // line 5
    Play_note(HIE, NOTE8);
    Play_note(HIE, NOTE4D);
    Play_note(HIE, NOTE8);
    Play_note(HID, NOTE8);
    Play_note(HIE, NOTE8);
    Play_note(HIFX, NOTE2);
    Play_note(HIE, NOTE8);
    Play_note(HID, NOTE8);
    Play_note(MIB, NOTE8);
    Play_note(HID, NOTE8);
    Play_note(HIE, NOTE8);
    Play_note(HIFX, NOTE8);
    Play_note(HIE, NOTE2D);
    Play_note(HIFX, NOTE8);                    // line 6
    Play_note(HIFX, NOTE8);
    Play_note(HIFX, NOTE4D);
    Play_note(HIE, NOTE8);
    Play_note(HID, NOTE8);
    Play_note(HIE, NOTE16);
    Play_note(HID, NOTE16);
    Play_note(MIB, NOTE8);
    Play_note(MIA, NOTE8);
    Play_note(MIFX, NOTE4);
    Play_note(MIB, NOTE8);
    Play_note(HIE, NOTE8);
    Play_note(HID, NOTE4);
    Play_note(MIB, NOTE8);
    Play_note(HID, NOTE8);
    Play_note(MIA, NOTE2D);
    Play_note(LOA, NOTE8);                     // line 7
    Play_note(LOB, NOTE8);
    Play_note(MID, NOTE4D);
    Play_note(MIE, NOTE8);
    Play_note(MIFX, NOTE8);
    Play_note(MIA, NOTE8);
    Play_note(MIA, NOTE2);
    Play_note(MID, NOTE8);
    Play_note(MID, NOTE8);
    Play_note(HID, NOTE4D);
    Play_note(HID, NOTE8);
    Play_note(MIB, NOTE8);
    Play_note(MIA, NOTE8);
    Play_note(MIFX, NOTE2);
    Play_note(MIA, NOTE8);                     // line 8
    Play_note(HIFX, NOTE8);
    Play_note(HIFX, NOTE4);
    Play_note(HIFX, NOTE4);
    Play_note(HIE, NOTE4D);
    Play_note(HIFX, NOTE8);
    Play_note(MIA, NOTE8);
    Play_note(MIB, NOTE8);
    Play_note(HID, NOTE1);
    Play_rest(REST1);
    Delay_ms(1000);
  }
}
