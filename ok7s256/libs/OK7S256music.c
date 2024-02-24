/***********************************************************************************/
/*	OK7S256music.c : Music Play Function for OK-7S256 V1.0 Training Kit	           */
/***********************************************************************************/

#include <board.h>

#include "OK7S256gcc.h"
#include "OK7S256music.h"

unsigned int tempo;                            // tempo = from 1(fast) to 7(slow)
unsigned int cut_flag = 1;                     // cut sound between notes

void Set_tempo(unsigned int number)
{                                              /* set tempo and PWMC */
  if ((number == 0) || (number > 7))           // set tempo
    tempo = 4;
  else
    tempo = number;

  AT91F_PWMC_CfgPMC();                         // enable clock of PWMC
  AT91F_PIO_CfgPeriph(AT91C_BASE_PIOA, SPEAKER, 0); // PWM0 output on PA0
}

void Play_note(unsigned int divider, unsigned int note)
{                                              /* play note */
  AT91F_PWMC_CfgChannel(AT91C_BASE_PWMC, 0, 0x0204, divider, divider >> 1);
  // Hz=MCK/16/divider(duty ration 50%)
  AT91F_PWMC_StartChannel(AT91C_BASE_PWMC, AT91C_PWMC_CHID0); // start sound
  Delay_ms(note * tempo * 7);                  // note play time
  AT91F_PWMC_StopChannel(AT91C_BASE_PWMC, AT91C_PWMC_CHID0);  // stop sound

  if (cut_flag != 0)                           // if not 0, cut sound between notes
    Delay_ms(5);
}

void Play_rest(unsigned int rest)
{                                              /* play rest */
  Delay_ms(rest * tempo * 7);                  // rest play time
}
