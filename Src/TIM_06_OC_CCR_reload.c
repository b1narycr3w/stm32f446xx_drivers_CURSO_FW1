#include <stm32f446xx.h>
#include "stm32f446xx_gpio.h"
#include "stm32f446xx_tim.h"
#include "stm32f446xx_rcc.h"
#include "stm32f446xx_nvic.h"

TIM_handle_t htim2;
uint32_t CCR1_Pulse, CCR2_Pulse, CCR3_Pulse, CCR4_Pulse;

void GPIO_setup(void)
{
	GPIO_handle_t TIM2_PIN = {0};

	TIM2_PIN.pGPIOx = GPIOA;
	TIM2_PIN.GPIO_config.GPIO_Pin = GPIO_PIN_0;
	TIM2_PIN.GPIO_config.GPIO_Mode = GPIO_Mode_AF;
	TIM2_PIN.GPIO_config.GPIO_AltFun = GPIO_ALTFUN_1;
	TIM2_PIN.GPIO_config.GPIO_Speed = GPIO_Speed_LOW;

	GPIO_Init(&TIM2_PIN);

	TIM2_PIN.GPIO_config.GPIO_Pin = GPIO_PIN_1;
	GPIO_Init(&TIM2_PIN);

	TIM2_PIN.pGPIOx = GPIOB;
	TIM2_PIN.GPIO_config.GPIO_Pin = GPIO_PIN_10;
	GPIO_Init(&TIM2_PIN);

	TIM2_PIN.GPIO_config.GPIO_Pin = GPIO_PIN_2;
	GPIO_Init(&TIM2_PIN);


}

void TIM_setup(void)
{
	uint32_t CKcnt;

	htim2.pTIMx = TIM2;
	htim2.TIM_TimeBase.TIM_Prescaler = 1;
	htim2.TIM_TimeBase.TIM_Period = 0xffffffff;
	htim2.TIM_TimeBase.TIM_CounterMode = TIM_CouterMode_UP;

	TIM_TimeBaseInit(&htim2);

	CKcnt = RCC_GetAPB1_TimerCLK()/(htim2.TIM_TimeBase.TIM_Prescaler + 1);
	CCR1_Pulse = CKcnt/(2 * 500);
	CCR2_Pulse = CKcnt/(2 * 1000);
	CCR3_Pulse = CKcnt/(2 * 2000);
	CCR4_Pulse = CKcnt/(2 * 4000);

	htim2.TIM_OutputCompare.TIM_Channel = TIM_CH1;
	htim2.TIM_OutputCompare.TIM_OCMode = TIM_OCMode_Toggle;
	htim2.TIM_OutputCompare.TIM_OCPolarity = TIM_OCPolarity_Active_HIGH;
	htim2.TIM_OutputCompare.TIM_Pulse = CCR1_Pulse;
	TIM_OCInit(&htim2);

	htim2.TIM_OutputCompare.TIM_Channel = TIM_CH2;
	htim2.TIM_OutputCompare.TIM_Pulse = CCR2_Pulse;
	TIM_OCInit(&htim2);

	htim2.TIM_OutputCompare.TIM_Channel = TIM_CH3;
	htim2.TIM_OutputCompare.TIM_Pulse = CCR3_Pulse;
	TIM_OCInit(&htim2);

	htim2.TIM_OutputCompare.TIM_Channel = TIM_CH4;
	htim2.TIM_OutputCompare.TIM_Pulse = CCR4_Pulse;
	TIM_OCInit(&htim2);

}

int main(void)
{
	GPIO_setup();
	TIM_setup();

	TIM_ITConfig(htim2.pTIMx, TIM_IT_CC1I, ENABLE);
	TIM_ITConfig(htim2.pTIMx, TIM_IT_CC2I, ENABLE);
	TIM_ITConfig(htim2.pTIMx, TIM_IT_CC3I, ENABLE);
	TIM_ITConfig(htim2.pTIMx, TIM_IT_CC4I, ENABLE);

	TIM_Cmd(htim2.pTIMx, ENABLE);

	NVIC_IRQ_Enable(IRQ_TIM2);
	while(1){

	}
}

void TIM2_IRQHandler(void)
{
	TIM_IRQHandler(&htim2);
}

void TIM_EventCallback(TIM_handle_t *pTIMHandle, TIM_Event_t event)
{
	uint32_t TIMx_CCRx_value;

	if(event == TIM_EVENT_CC1I){
		TIMx_CCRx_value = TIM_GetCapture(pTIMHandle->pTIMx, TIM_CH1);
		TIM_SetCompare(pTIMHandle->pTIMx, TIM_CH1, TIMx_CCRx_value + CCR1_Pulse);
	}

	if(event == TIM_EVENT_CC2I){
		TIMx_CCRx_value = TIM_GetCapture(pTIMHandle->pTIMx, TIM_CH2);
		TIM_SetCompare(pTIMHandle->pTIMx, TIM_CH2, TIMx_CCRx_value + CCR2_Pulse);
	}

	if(event == TIM_EVENT_CC3I){
		TIMx_CCRx_value = TIM_GetCapture(pTIMHandle->pTIMx, TIM_CH3);
		TIM_SetCompare(pTIMHandle->pTIMx, TIM_CH3, TIMx_CCRx_value + CCR3_Pulse);
	}

	if(event == TIM_EVENT_CC4I){
		TIMx_CCRx_value = TIM_GetCapture(pTIMHandle->pTIMx, TIM_CH4);
		TIM_SetCompare(pTIMHandle->pTIMx, TIM_CH4, TIMx_CCRx_value + CCR4_Pulse);
	}
}

void assert_failed(uint8_t *file, uint32_t line){
	while(1);
}
