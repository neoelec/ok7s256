#ifndef __OK7S256HACK_H__
#define __OK7S256HACK_H__

#ifdef ok7s256

#undef ADC_NUM_1
#undef ADC_NUM_2
#undef ADC_NUM_3
#undef ADC_NUM_4

#define ADC_NUM_1 ADC_CHANNEL_4
#define ADC_NUM_2 ADC_CHANNEL_5
#define ADC_NUM_3 ADC_CHANNEL_6
#define ADC_NUM_4 ADC_CHANNEL_7

#endif /* ok7s256 */

#endif /* __OK7S256HACK_H__ */
