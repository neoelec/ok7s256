/* ========================================================================== */
/*             Xtest17_5.c : Digital Oscilloscope on GLCD Module              */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2007.  */

#include <board.h>

#include <OK7S256gcc.h>
#include <OK7S256GLCD.h>

volatile unsigned int n;                       // interrupt count (0-110)
volatile unsigned int AD_data, AD_flag;        // A/D data and flag
unsigned int ydot;

void PIT_ISR(void)
{                                              /* PIT interrupt service routine */
  unsigned int i, sum;

  AT91F_PITGetPIVR(AT91C_BASE_PITC);           // clear PITS

  sum = 0;
  for (i = 0; i < 16; i++) {
    AT91F_ADC_StartConversion(AT91C_BASE_ADC); // start conversion
    while (!(AT91F_ADC_GetStatus(AT91C_BASE_ADC) & AT91C_ADC_EOC5)) ; // wait for EOC
    sum += AT91F_ADC_GetConvertedDataCH5(AT91C_BASE_ADC); // add A/D result 16 times
    Delay_ms(1);
  }
  sum >>= 4;                                   // divide sum by 16 for average value
  AD_data = (int)((float)sum * 33. / 1024. + 0.5);  // voltage = 10*(sum*3.3/1024)

  n++;
  if (n == 111)
    n = 0;

  AD_flag = 1;
}

void GLCD_xy_temp(unsigned int x, unsigned int y)
{                                              /* set character position */
  xcharacter = x;
  ydot = y;

  GLCD_command(GLCD_CS2 | GLCD_CS1, 0xB8 + xcharacter); // X address

  if (ydot <= 63)                              // if y <= 63, CS1 Y address
    GLCD_command(GLCD_CS1, 0x40 + ydot);
  else                                         // if y >= 64, CS2 Y address
    GLCD_command(GLCD_CS2, 0x40 + ydot - 64);
}

void GLCD_English_temp(unsigned int attribute, unsigned char character)
            /* display a character */
{
  unsigned int i, cs, x;

  GLCD_xy_temp(xcharacter, ydot);
  if (ydot <= 63)                              // if y <= 63, CS1
    cs = GLCD_CS1;
  else                                         // if y >= 64, CS2
    cs = GLCD_CS2;
  for (i = 0; i <= 4; i++) {
    x = font[character - 0x20][i];
    if ((cursor_flag == 1) && (xcharacter == xcursor) && (ycharacter == ycursor))
      x |= 0x80;
    if (attribute == 0x01)                     // reverse ?
      x = ~x;
    GLCD_data(cs, x);
  }
  x = 0x00;                                    // last byte of font
  if (attribute == 0x01)
    x = ~x;
  GLCD_data(cs, x);

  ydot += 6;                                   // go next character position
}

void GLCD_string_temp(unsigned int x, unsigned int y, unsigned int attribute, char *string)
            /* display a string */
{
  xcharacter = x;
  ydot = y;

  while (*string != '\0') {
    GLCD_English_temp(attribute, *string);     // display a charcater
    string++;
  }
}

void Line_temp(int xx1, int yy1, int xx2, int yy2)
{                                              /* draw a straight line */
  int x, y;

  if (xx1 != xx2) {                            // if xx1 != xx2, x is variable
    if (xx1 < xx2)                             //              y is function
      for (x = xx1; x <= xx2; x++) {
        y = yy1 + (x - xx1) * (yy2 - yy1) / (xx2 - xx1);
        Dot(x, y);
    } else
      for (x = xx1; x >= xx2; x--) {
        y = yy1 + (x - xx1) * (yy2 - yy1) / (xx2 - xx1);
        Dot(x, y);
      }
  } else if (yy1 != yy2) {                     // if yy1 != yy2, y is variable
    if (yy1 < yy2)                             //              x is function
      for (y = yy1; y <= yy2; y++) {
        x = xx1 + (y - yy1) * (xx2 - xx1) / (yy2 - yy1);
        Dot(x, y);
    } else
      for (y = yy1; y >= yy2; y--) {
        x = xx1 + (y - yy1) * (xx2 - xx1) / (yy2 - yy1);
        Dot(x, y);
      }
  } else                                       // if xx1 == xx2 and yy1 == yy2,
    Dot(xx1, yy1);                             //             it is a dot
}

int main(void)
{
  unsigned int i, x, y, xo, yo;
  unsigned int xaxis = 10, yaxis = 53;

  MCU_initialize();                            // initialize AT91SAM7S256 & kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module
  GLCD_clear();                                // initialize GLCD screen

  LCD_string(0x80, "  Oscilloscope  ");        // display title
  LCD_string(0xC0, " for VR1 Voltage");
  Beep();

  AT91F_PITC_CfgPMC();                         // enable peripheral clock for PIT
  AT91F_PITInit(AT91C_BASE_PITC, 1, 48);       // enable and initialize PIT
  AT91F_PITSetPIV(AT91C_BASE_PITC, 300000 - 1); // 48MHz/16/300000 = 10Hz

  AT91F_PITEnableInt(AT91C_BASE_PITC);         // initialize PIT interrupt
  AT91F_AIC_ConfigureIt(AT91C_BASE_AIC, AT91C_ID_SYS, 7, 1, PIT_ISR);
  AT91F_AIC_EnableIt(AT91C_BASE_AIC, AT91C_ID_SYS);

  AT91F_ADC_CfgPMC();                          // enable peripheral clock for ADC
  AT91F_ADC_SoftReset(AT91C_BASE_ADC);         // clear all previous ADC settings
  *AT91C_ADC_MR = 0x02020400;                  // SHTIM=2, STARTUP=2, 4.8MHz, 10 bit
  AT91F_ADC_EnableChannel(AT91C_BASE_ADC, AT91C_ADC_CH5); // select CH5 for VR1

  n = 0;                                       // initial interrupt count
  AD_flag = 0;

  while (1) {
    Clear_screen();                            // initialize GLCD screen

    Line_temp(yaxis, xaxis - 1, yaxis, 125);   // draw X axis
    Line_temp(yaxis - 2, 123, yaxis, 125);
    Line_temp(yaxis + 2, 123, yaxis, 125);
    for (y = xaxis + 10; y <= xaxis + 110; y += 10)
      Line_temp(yaxis - 1, y, yaxis + 1, y);
    for (y = xaxis, i = 0; y <= xaxis + 80; y += 20, i += 2) {
      GLCD_xy_temp(7, y - 2);
      GLCD_English_temp(0, i + '0');
    }
    GLCD_string_temp(7, 108, 0, "sec");

    Line_temp(0, xaxis, yaxis + 1, xaxis);     // draw Y axis
    Line_temp(2, xaxis - 2, 0, xaxis);
    Line_temp(2, xaxis + 2, 0, xaxis);
    for (x = 3; x <= 43; x += 10)
      Line_temp(x, xaxis - 1, x, xaxis + 1);
    GLCD_xy_temp(6, 2);
    GLCD_English_temp(0, '0');
    GLCD_xy_temp(0, 2);
    GLCD_English_temp(0, 'V');

    yo = xaxis;                                // initial point of old data
    xo = yaxis;

    while (n) {
      while (!AD_flag) ;                       // wait until new A/D data
      AD_flag = 0;

      y = xaxis + n;                           // draw line from old point
      x = yaxis - AD_data;                     //           to new point
      Line_temp(xo, yo, x, y);

      yo = y;                                  // old point <-- new point
      xo = x;
    }
  }
}
