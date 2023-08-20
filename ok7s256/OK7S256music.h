/***********************************************************************************/
/*	OK7S256music.h : Music Play Function for OK-7S256 V1.0 Training Kit	   */
/***********************************************************************************/
#define	VLOA	27273				// define divider for octave 2
#define	VLOAX	25742
#define	VLOB	24297
#define	LOC	22934				// define divider for octave 3
#define	LOCX	21646
#define	LOD	20432
#define	LODX	19285
#define	LOE	18202
#define	LOF	17181
#define	LOFX	16216
#define	LOG	15306
#define	LOGX	14447
#define	LOA	13636
#define	LOAX	12871
#define	LOB	12149
#define	MIC	11467				// define divider for octave 4
#define	MICX	10823
#define	MID	10216
#define	MIDX	9642
#define	MIE	9101
#define	MIF	8590
#define	MIFX	8108
#define	MIG	7653
#define	MIGX	7224
#define	MIA	6818
#define	MIAX	6436
#define	MIB	6074
#define	HIC	5733				// define divider for octave 5
#define	HICX	5412
#define	HID	5108
#define	HIDX	4821
#define	HIE	4551
#define	HIF	4295
#define	HIFX	4054
#define	HIG	3827
#define	HIGX	3612
#define	HIA	3409
#define	HIAX	3218
#define	HIB	3037
#define	VHIC	2867				// define divider for octave 6
#define	VHICX	2706
#define	VHID	2554
#define	VHIDX	2411
#define	VHIE	2275

#define	NOTE32	1*3				// define note length
#define	NOTE16	2*3
#define	NOTE16D	3*3
#define	NOTE16T	2*2
#define	NOTE8	4*3
#define	NOTE8D	6*3
#define	NOTE8T	4*2
#define	NOTE4	8*3
#define	NOTE4D	12*3
#define	NOTE4T	8*2
#define	NOTE2	16*3
#define	NOTE2D	24*3
#define	NOTE1	32*3

#define	REST32	1*3				// define rest length
#define	REST16	2*3
#define	REST16D	3*3
#define	REST8	4*3
#define	REST8D	6*3
#define	REST4	8*3
#define	REST4D	12*3
#define	REST2	16*3
#define	REST2D	24*3
#define	REST1	32*3

unsigned int tempo;				// tempo = from 1(fast) to 7(slow)
unsigned int cut_flag = 1;			// cut sound between notes

void Set_tempo(unsigned int number)		/* set tempo and PWMC */
{
  if((number == 0) || (number > 7))		// set tempo
    tempo = 4;
  else
    tempo = number;

  AT91F_PWMC_CfgPMC();				// enable clock of PWMC
  AT91F_PIO_CfgPeriph(AT91C_BASE_PIOA, SPEAKER, 0); // PWM0 output on PA0
}

void Play_note(unsigned int divider, unsigned int note) /* play note */
{
  AT91F_PWMC_CfgChannel(AT91C_BASE_PWMC, 0, 0x0204, divider, divider >> 1);
						// Hz=MCK/16/divider(duty ration 50%)
  AT91F_PWMC_StartChannel(AT91C_BASE_PWMC, AT91C_PWMC_CHID0); // start sound
  Delay_ms(note*tempo*7);			// note play time
  AT91F_PWMC_StopChannel(AT91C_BASE_PWMC, AT91C_PWMC_CHID0);  // stop sound

  if(cut_flag != 0)				// if not 0, cut sound between notes
    Delay_ms(5);
}

void Play_rest(unsigned int rest)		/* play rest */
{
  Delay_ms(rest*tempo*7);			// rest play time
}
