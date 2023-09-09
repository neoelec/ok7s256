#include <board.h>
/* - */
#include <pio/pio.h>

#include "buzzer.h"
#include "delay.h"

static const Pin __pinBuzzer = PIN_BUZZER;
static const Pin *pinBuzzer = &__pinBuzzer;

static unsigned int duration;

void BUZZER_Configure(unsigned int durationMs)
{
    PIO_Configure(pinBuzzer, 1);
    duration = durationMs;
}

void BUZZER_On(void)
{                                              /* buzzer on */
    PIO_Clear(pinBuzzer);
}

void BUZZER_Off(void)
{                                              /* buzzer off */
    PIO_Set(pinBuzzer);
}

void BUZZER_Beep(void)
{                                              /* beep for 50 ms */
    BUZZER_On();
    DELAY_ms(duration);
    BUZZER_Off();
}
