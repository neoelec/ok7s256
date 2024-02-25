#include <FreeRTOS.h>
#include <task.h>

#include <board.h>
#include <utility/led.h>

static void prvLEDConfigure( void )
{
	LED_Configure( 0 );
	LED_Configure( 1 );
}

static void prvLEDFlashTask0( void *pvParameters )
{
portTickType xLastWakeTime;
const portTickType xFrequency = 500;

	xLastWakeTime = xTaskGetTickCount();
	while ( 1 )
	{
		vTaskDelayUntil( &xLastWakeTime, xFrequency );
		LED_Toggle( 0 );
	}
}

static void prvLEDFlashTask1( void *pvParameters )
{
portTickType xLastWakeTime;
const portTickType xFrequency = 1000;

	xLastWakeTime = xTaskGetTickCount();
	while ( 1 )
	{
		vTaskDelayUntil( &xLastWakeTime, xFrequency );
		LED_Toggle( 1 );
	}
}

int main(void)
{
	prvLEDConfigure();

	xTaskCreate( prvLEDFlashTask0, "LED0", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL );
	xTaskCreate( prvLEDFlashTask1, "LED1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL );
	vTaskStartScheduler();

	return 0;
}
