#ifndef __BUZZER_H__
#define __BUZZER_H__

extern void BUZZER_Configure(unsigned int durationMs);
extern void BUZZER_On(void);                   /* buzzer on */
extern void BUZZER_Off(void);                  /* buzzer off */
extern void BUZZER_Beep(void);                 /* beep for 50 ms */

#endif /* __BUZZER_H__ */
