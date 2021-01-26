#include <stm32f446xx.h>
#include "stm32f446xx_gpio.h"
#include "stm32f446xx_tim.h"
#include "stm32f446xx_nvic.h"

TIM_handle_t htim2;
uint32_t CCR1_Pulse[3];

uint8_t button_pressed_f;

void delay(uint32_t cnt)
{
	while(cnt)
		cnt--;
}

void GPIO_setup(void)
{
	GPIO_handle_t TIM2_PIN = {0};

	TIM2_PIN.pGPIOx = GPIOA;
	TIM2_PIN.GPIO_config.GPIO_Pin = GPIO_PIN_0;
	TIM2_PIN.GPIO_config.GPIO_Mode = GPIO_Mode_AF;
	TIM2_PIN.GPIO_config.GPIO_AltFun = GPIO_ALTFUN_1;
	TIM2_PIN.GPIO_config.GPIO_Speed = GPIO_Speed_LOW;

	GPIO_Init(&TIM2_PIN);

	GPIO_handle_t Button;
	Button.pGPIOx = GPIOC;
	Button.GPIO_config.GPIO_Mode = GPIO_Mode_IT_FE;
	Button.GPIO_config.GPIO_Pin = GPIO_PIN_13;
	Button.GPIO_config.GPIO_PuPd = GPIO_PuPd_NONE;
	Button.GPIO_config.GPIO_Speed = GPIO_Speed_LOW;

	GPIO_Init(&Button);
}

void TIM_setup(void)
{
	htim2.pTIMx = TIM2;
	htim2.TIM_TimeBase.TIM_Prescaler = 99;
	htim2.TIM_TimeBase.TIM_Period = 3199; // T = 20ms
	htim2.TIM_TimeBase.TIM_CounterMode = TIM_CouterMode_UP;

	TIM_TimeBaseInit(&htim2);

	// Periodo PWM: T = 20ms
	//   0º -> Ton = 0.5ms,   DC = 2.5%
	//	90º -> Ton = 1.5ms, DC = 7.5%
	// 180º -> Ton = 2.5ms,   DC = 12.5%
	CCR1_Pulse[0] = (25 * (htim2.TIM_TimeBase.TIM_Period + 1))/1000;
	CCR1_Pulse[1] = (75 * (htim2.TIM_TimeBase.TIM_Period + 1))/1000;
	CCR1_Pulse[2] = (125 * (htim2.TIM_TimeBase.TIM_Period + 1))/1000;


	htim2.TIM_OutputCompare.TIM_Channel = TIM_CH1;
	htim2.TIM_OutputCompare.TIM_OCMode = TIM_OCMode_PWM1;
	htim2.TIM_OutputCompare.TIM_OCPolarity = TIM_OCPolarity_Active_HIGH;
	htim2.TIM_OutputCompare.TIM_Pulse = CCR1_Pulse[0];
	TIM_OCInit(&htim2);

}

int main(void)
{
	GPIO_setup();
	TIM_setup();

	TIM_Cmd(htim2.pTIMx, ENABLE);

	NVIC_IRQ_Enable(IRQ_EXTI15_10);
	uint8_t idx = 0;
	while(1){
		if(button_pressed_f){
			delay(70000);
			button_pressed_f = 0;

			idx++;
			if(idx > 2)
				idx = 0;

			TIM_SetCompare(htim2.pTIMx, TIM_CH1, CCR1_Pulse[idx]);
		}
	}
}

void EXTI15_10_IRQHandler(void)
{
	GPIO_IRQHandler(GPIO_PIN_13);
	button_pressed_f = 1;
}

void assert_failed(uint8_t *file, uint32_t line){
	while(1);
}
