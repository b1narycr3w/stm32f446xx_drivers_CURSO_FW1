#include <stm32f446xx.h>
#include "stm32f446xx_gpio.h"
#include "stm32f446xx_tim.h"
#include "stm32f446xx_nvic.h"
#include "stm32f446xx_rcc.h"


TIM_handle_t htim2;
uint32_t capture1;
uint32_t capture2;
uint32_t capture_diff;

typedef enum{
	waiting_for_cap1_st,
	waiting_for_cap2_st,
	processing_st
}freq_measurement_st_t;

freq_measurement_st_t freq_measurement_st = waiting_for_cap1_st;

void GPIO_setup(void)
{
	GPIO_handle_t MCO1_PIN;
	GPIO_handle_t TIM2CH2_PIN;
	GPIO_handle_t PC10_debug;

	MCO1_PIN.pGPIOx = GPIOA;
	MCO1_PIN.GPIO_config.GPIO_Pin = GPIO_PIN_8;
	MCO1_PIN.GPIO_config.GPIO_Mode = GPIO_Mode_AF;
	MCO1_PIN.GPIO_config.GPIO_AltFun = GPIO_ALTFUN_0;
	MCO1_PIN.GPIO_config.GPIO_OType = GPIO_OType_PP;
	MCO1_PIN.GPIO_config.GPIO_Speed = GPIO_Speed_FAST;

	GPIO_Init(&MCO1_PIN);

	TIM2CH2_PIN.pGPIOx = GPIOA;
	TIM2CH2_PIN.GPIO_config.GPIO_Pin = GPIO_PIN_1;
	TIM2CH2_PIN.GPIO_config.GPIO_Mode = GPIO_Mode_AF;
	TIM2CH2_PIN.GPIO_config.GPIO_AltFun = GPIO_ALTFUN_1;
	TIM2CH2_PIN.GPIO_config.GPIO_Speed = GPIO_Speed_FAST;

	GPIO_Init(&TIM2CH2_PIN);

	PC10_debug.pGPIOx = GPIOC;
	PC10_debug.GPIO_config.GPIO_Pin = GPIO_PIN_10;
	PC10_debug.GPIO_config.GPIO_Mode = GPIO_Mode_OUT;
	PC10_debug.GPIO_config.GPIO_Speed = GPIO_Speed_FAST;

	GPIO_Init(&PC10_debug);
}

void TIM_setup(void)
{
	htim2.pTIMx = TIM2;
	htim2.TIM_TimeBase.TIM_Prescaler = 1;
	htim2.TIM_TimeBase.TIM_Period = 0xffffffff;
	htim2.TIM_TimeBase.TIM_CounterMode = TIM_CouterMode_UP;

	TIM_TimeBaseInit(&htim2);

	htim2.TIM_InputCapture.TIM_Channel = TIM_CH2;
	htim2.TIM_InputCapture.TIM_ICFilter = TIM_ICFilter_NONE;
	htim2.TIM_InputCapture.TIM_ICPolarity = TIM_ICPolarity_RE;
	htim2.TIM_InputCapture.TIM_ICPrescaler = TIM_ICPrescaler_NONE;
	htim2.TIM_InputCapture.TIM_ICSelection = TIM_ICSelection_Direct;

	TIM_ICInit(&htim2);
}

void SYSCLK_PLL_setup(void)
{
	uint32_t PLLM, PLLN, PLLP, PLLQ, PLLR;
	// 168MHz
	PLLM = 8;
	PLLN = 336;
	PLLP = 2;
	PLLQ = 7;
	PLLR = 5;

	// Configurar prescaler APB1 y APB2
	RCC_APB1CLKConfig(RCC_APB_Prescaler_4); // 42MHz
	RCC_APB2CLKConfig(RCC_APB_Prescaler_2); // 84MHz

	// Habilitar HSE
	RCC_HSEConfig(RCC_HSE_ON);

	// Esperar a que HSE este OK
	RCC_WaitForCLKRDY(RCC_Clock_HSE);

	// Configurar el PLL
	RCC_PLLConfig(RCC_PLL_Source_HSE, PLLM, PLLN, PLLP, PLLQ, PLLR);

	// Habilitar PLL
	RCC_PLLCmd(ENABLE);

	// Esperar a que PLL este OK
	RCC_WaitForCLKRDY(RCC_Clock_PLL);

	// Flash latency
	*((volatile uint32_t *)0x40023C00) = 0x05;

	// Seleccionar PLL_P como fuente de reloj del sistema
	RCC_SYSCLKConfig(RCC_SYSCLK_Source_PLL_P);

}

int main(void)
{
	uint32_t freq;
	uint32_t CNT_CLK_freq;

	SYSCLK_PLL_setup();

	// Configurar LSE
	RCC_LSEConfig(RCC_LSE_ON);
	RCC_WaitForCLKRDY(RCC_Clock_LSE);

	// Configurar MCO1
	RCC_MCO1Config(RCC_MCO1_Source_LSE, RCC_MCO1_Prescaler_None);

	GPIO_setup();
	TIM_setup();

	TIM_ITConfig(htim2.pTIMx, TIM_IT_CC2I, ENABLE);
	TIM_Cmd(htim2.pTIMx, ENABLE);

	NVIC_IRQ_Enable(IRQ_TIM2);

	CNT_CLK_freq = RCC_GetAPB1_TimerCLK()/(htim2.TIM_TimeBase.TIM_Prescaler + 1);
	while(1){
		if(freq_measurement_st == processing_st){
			freq = CNT_CLK_freq / capture_diff;
			freq_measurement_st = waiting_for_cap1_st;
		}
	}
}

void TIM2_IRQHandler(void)
{
	GPIO_WritePin(GPIOC, 10, SET);
	TIM_IRQHandler(&htim2);
	GPIO_WritePin(GPIOC, 10, RESET);
}

void TIM_EventCallback(TIM_handle_t *pTIMHandle, TIM_Event_t event)
{
	if(event == TIM_EVENT_CC2I){
		switch(freq_measurement_st){
		case waiting_for_cap1_st:
			capture1 = TIM_GetCapture(htim2.pTIMx, TIM_CH2);
			freq_measurement_st = waiting_for_cap2_st;
			break;
		case waiting_for_cap2_st:
			capture2 = TIM_GetCapture(htim2.pTIMx, TIM_CH2);
			if(capture2 > capture1)
				capture_diff = capture2 - capture1;
			else
				capture_diff = 0xffffffff - capture1 + capture2 + 1;
			freq_measurement_st = processing_st;
			break;
		case processing_st:
			break;
		default:
			freq_measurement_st = waiting_for_cap1_st;
			break;
		}
	}
}

void assert_failed(uint8_t *file, uint32_t line){
	while(1);
}
