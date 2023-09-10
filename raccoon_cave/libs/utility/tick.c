#include <board.h>
/* - */
#include <aic/aic.h>
#include <pit/pit.h>

#define PIT_PERIOD 1000

volatile unsigned int timestamp;

static void ISR_Pit(void)
{
    unsigned int status;

    status = PIT_GetStatus() & AT91C_PITC_PITS;
    if (status != 0)
        timestamp += (PIT_GetPIVR() >> 20);
}

void TICK_Configure(void)
{
    PIT_Init(PIT_PERIOD, BOARD_MCK / 1000000);

    AIC_DisableIT(AT91C_ID_SYS);
    AIC_ConfigureIT(AT91C_ID_SYS, AT91C_AIC_PRIOR_LOWEST, ISR_Pit);
    AIC_EnableIT(AT91C_ID_SYS);
    PIT_EnableIT();

    PIT_Enable();
}

unsigned int TICK_GetTimestamp(void)
{
    return timestamp;
}
