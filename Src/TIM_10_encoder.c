#include <stdio.h>
#include <string.h>

#include <stm32f446xx.h>
#include "stm32f446xx_gpio.h"
#include "stm32f446xx_tim.h"
#include "stm32f446xx_nvic.h"
#include "stm32f446xx_rcc.h"

#include "usart2.h"

TIM_handle_t htim2;

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

	TIM2_PIN.GPIO_config.GPIO_Pin = GPIO_PIN_1;
	TIM2_PIN.GPIO_config.GPIO_Mode = GPIO_Mode_AF;
	TIM2_PIN.GPIO_config.GPIO_AltFun = GPIO_ALTFUN_1;
	TIM2_PIN.GPIO_config.GPIO_Speed = GPIO_Speed_LOW;

	GPIO_Init(&TIM2_PIN);

}

void TIM_setup(void)
{
	/********************* TIM2 (Medicion PWM) **********************/
	htim2.pTIMx = TIM2;

	// Canal 1: modo directo y flanco de subida
	htim2.TIM_InputCapture.TIM_Channel = TIM_CH1;
	htim2.TIM_InputCapture.TIM_ICSelection = TIM_ICSelection_Direct;
	htim2.TIM_InputCapture.TIM_ICPolarity = TIM_ICPolarity_RE;
	TIM_ICInit(&htim2);

	// Canal 2: modo directo y flanco de subida
	htim2.TIM_InputCapture.TIM_Channel = TIM_CH2;
	htim2.TIM_InputCapture.TIM_ICSelection = TIM_ICSelection_Direct;
	htim2.TIM_InputCapture.TIM_ICPolarity = TIM_ICPolarity_RE;
	TIM_ICInit(&htim2);

	// Modo esclavo: Encoder modo 3
	TIM_SlaveMode(htim2.pTIMx, TIM_Slave_Encoder_Mode_2);
}

int main(void)
{
	uint32_t tim2_cnt;
	uint8_t dir;
	GPIO_setup();
	TIM_setup();

	USART2_PIN_setup();
	USART2_Init();

	// Habilitamos timers 2
	TIM_Cmd(htim2.pTIMx, ENABLE);

	uint8_t msg[48];
	htim2.pTIMx->ARR = 100;
	while(1){

		tim2_cnt = TIM_GetCounter(htim2.pTIMx);
		dir = (htim2.pTIMx->CR1 >> TIM_CR1_DIR) & 0x01;

		snprintf((char *)msg, sizeof(msg),"CNT: %ld [%s]\r\n", tim2_cnt, dir ? "-":"+");
		USART2_SendData(msg, strlen((char *)msg));

		delay(50000);
	}
}

void assert_failed(uint8_t *file, uint32_t line){
	while(1);
}
