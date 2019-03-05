/*
 * lin_timer.c
 *
 *  Created on: Mar 4, 2019
 *      Author: Cursos
 */
#include "lin_timer.h"

#include "fsl_pit.h"

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "event_groups.h"

#define EVENT_PIT0 (1<<0)
#define EVENT_PIT1 (1<<1)

#define GET_ARGS(args,type) *((type*)args)

typedef struct
{
//	pit_config_t pit_config;
//	uint32_t interruptPin;
	EventGroupHandle_t events;
	SemaphoreHandle_t mutex;
	SemaphoreHandle_t bin_sem;
	TaskHandle_t blink_task_handle;
}lin_pit_hanlde_t;

static lin_pit_hanlde_t pit_hanlde[NUMBER_OF_PIT] = {0};

static inline void lin_pit_init(lin_pit_t base, float period);
static inline void nvic_enable_irq_nvic_set_priority(lin_pit_t base);

void PIT0_IRQHandler(void)
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	PIT_ClearStatusFlags(PIT, kPIT_Chnl_0, kPIT_TimerFlag);

	xEventGroupSetBitsFromISR(pit_hanlde[lin_pit0].events, EVENT_PIT0, &xHigherPriorityTaskWoken);
	portYIELD_FROM_ISR( xHigherPriorityTaskWoken );

}

static inline void lin_pit_init(lin_pit_t base, float period)
{
	pit_hanlde[lin_pit0].events = xEventGroupCreate();
    pit_config_t pit_config;
    PIT_GetDefaultConfig(&pit_config);
    PIT_Init(PIT, &pit_config);
    PIT_SetTimerPeriod(PIT, kPIT_Chnl_0, CLOCK_GetBusClkFreq()*(period));//1.5
    PIT_GetStatusFlags(PIT, kPIT_Chnl_0);
    PIT_StartTimer(PIT, kPIT_Chnl_0);
    PIT_EnableInterrupts(PIT, kPIT_Chnl_0, kPIT_TimerInterruptEnable);
//    NVIC_EnableIRQ(PIT0_IRQn);
    nvic_enable_irq_nvic_set_priority(base);

}

static inline void nvic_enable_irq_nvic_set_priority(lin_pit_t base)
{
	switch(base)
	{
	case lin_pit0:
		NVIC_EnableIRQ(PIT0_IRQn);
		NVIC_SetPriority(PIT1_IRQn, 5);
		break;
	case lin_pit1:
		NVIC_EnableIRQ(PIT0_IRQn);
		NVIC_SetPriority(PIT1_IRQn, 5);
		break;

	}
}

void lin_pit_wait_pin(void)
{

		xEventGroupWaitBits(pit_hanlde[lin_pit0].events, EVENT_PIT0, pdTRUE, pdFALSE, portMAX_DELAY);

}


