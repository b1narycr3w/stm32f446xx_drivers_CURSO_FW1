#include <stm32f446xx.h>
#include "stm32f446xx_gpio.h"
#include "stm32f446xx_tim.h"
#include "stm32f446xx_nvic.h"


GPIO_handle_t LED;
TIM_handle_t htim_led;

void delay(uint32_t cnt)
{
	while(cnt)
		cnt--;
}


void GPIO_setup(void)
{
	LED.pGPIOx = GPIOA;
	LED.GPIO_config.GPIO_Mode = GPIO_Mode_OUT;
	LED.GPIO_config.GPIO_OType = GPIO_OType_PP;
	LED.GPIO_config.GPIO_Pin = GPIO_PIN_5;
	LED.GPIO_config.GPIO_PuPd = GPIO_PuPd_NONE;
	LED.GPIO_config.GPIO_Speed = GPIO_Speed_LOW;

	GPIO_Init(&LED);
}

void TIM_setup(void)
{
	htim_led.pTIMx = TIM6;
	htim_led.TIM_TimeBase.TIM_Period = 63999;
	htim_led.TIM_TimeBase.TIM_Prescaler = 24;

	TIM_TimeBaseInit(&htim_led);
}

int main(void)
{
	GPIO_setup();
	TIM_setup();

	TIM_ITConfig(htim_led.pTIMx, TIM_IT_UI, ENABLE);
	TIM_Cmd(htim_led.pTIMx, ENABLE);

	NVIC_IRQ_Enable(IRQ_TIM6_DAC);

	while(1){

	}
}

void TIM6_DAC_IRQHandler(void)
{
	TIM_IRQHandler(&htim_led);
}

void TIM_EventCallback(TIM_handle_t *pTIMHandle, TIM_Event_t event)
{
	if(event == TIM_EVENT_UI){
		GPIO_TogglePin(LED.pGPIOx, GPIO_PIN_5);
	}
}

