#include <stdio.h>
#include <string.h>

#include <stm32f446xx.h>
#include "stm32f446xx_gpio.h"
#include "stm32f446xx_tim.h"
#include "stm32f446xx_nvic.h"
#include "stm32f446xx_rcc.h"

#include "usart2.h"

TIM_handle_t htim2;
TIM_handle_t htim5;

uint32_t TIM5_CCR1_Pulse;

uint8_t button_pressed_f;
uint8_t duty_cicle = 25; // Rango: 25 a 125 (DC multiplicado por 10 para evitar decimales)

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

	GPIO_handle_t TIM5_PIN = {0};

	TIM5_PIN.pGPIOx = GPIOA;
	TIM5_PIN.GPIO_config.GPIO_Pin = GPIO_PIN_1;
	TIM5_PIN.GPIO_config.GPIO_Mode = GPIO_Mode_AF;
	TIM5_PIN.GPIO_config.GPIO_AltFun = GPIO_ALTFUN_2;
	TIM5_PIN.GPIO_config.GPIO_Speed = GPIO_Speed_LOW;

	GPIO_Init(&TIM5_PIN);

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
	/********************* TIM2 (Medicion PWM) **********************/
	htim2.pTIMx = TIM2;
	htim2.TIM_TimeBase.TIM_Prescaler = 1;
	htim2.TIM_TimeBase.TIM_Period = 0xffffffff;
	htim2.TIM_TimeBase.TIM_CounterMode = TIM_CouterMode_UP;

	TIM_TimeBaseInit(&htim2);

	// Canal 1: modo directo y flanco de subida
	htim2.TIM_InputCapture.TIM_Channel = TIM_CH1;
	htim2.TIM_InputCapture.TIM_ICSelection = TIM_ICSelection_Direct;
	htim2.TIM_InputCapture.TIM_ICPolarity = TIM_ICPolarity_RE;
	TIM_ICInit(&htim2);

	// Canal 2: modo indirecto y flanco de bajada
	htim2.TIM_InputCapture.TIM_Channel = TIM_CH2;
	htim2.TIM_InputCapture.TIM_ICSelection = TIM_ICSelection_Indirect;
	htim2.TIM_InputCapture.TIM_ICPolarity = TIM_ICPolarity_FE;
	TIM_ICInit(&htim2);

	// Modo esclavo: Input trigger el timer input 1 y modo reset
	TIM_InputTrigger(htim2.pTIMx, TIM_Trigger_Filtered_Timer_Input_1);
	TIM_SlaveMode(htim2.pTIMx, TIM_Slave_Reset_Mode);

	/********************* TIM5 (Generacion PWM) **********************/
	htim5.pTIMx = TIM5;
	htim5.TIM_TimeBase.TIM_Prescaler = 99;
	htim5.TIM_TimeBase.TIM_Period = 3199; // T = 20ms
	htim5.TIM_TimeBase.TIM_CounterMode = TIM_CouterMode_UP;

	TIM5_CCR1_Pulse = 0;
	htim5.TIM_OutputCompare.TIM_Channel = TIM_CH2;
	htim5.TIM_OutputCompare.TIM_OCMode = TIM_OCMode_PWM1;
	htim5.TIM_OutputCompare.TIM_OCPolarity = TIM_OCPolarity_Active_HIGH;
	htim5.TIM_OutputCompare.TIM_Pulse = TIM5_CCR1_Pulse;
	TIM_OCInit(&htim5);

}

int main(void)
{
	uint32_t cc1r;
	uint32_t PWM_T;
	float PWM_DC;

	GPIO_setup();
	TIM_setup();

	USART2_PIN_setup();
	USART2_Init();

	// Habilitamos timers 2 y 5
	TIM_Cmd(htim5.pTIMx, ENABLE);
	TIM_Cmd(htim2.pTIMx, ENABLE);

	// Habilitarmos interrupcion de pulsador
	NVIC_IRQ_Enable(IRQ_EXTI15_10);

	uint8_t msg[48];
	while(1){
		if(button_pressed_f){
			// Incrementar duty cycle
			delay(70000);
			button_pressed_f = 0;

			duty_cicle += 5;
			if(duty_cicle > 125)
				duty_cicle = 25;

			TIM5_CCR1_Pulse = (duty_cicle * (htim5.TIM_TimeBase.TIM_Period + 1))/1000;
			TIM_SetCompare(htim5.pTIMx, TIM_CH2, TIM5_CCR1_Pulse);
		}

		cc1r = TIM_GetCapture(htim2.pTIMx, TIM_CH1);
		if(cc1r > 0){
			PWM_T = (cc1r + 1)*1000/(RCC_GetAPB1_TimerCLK()/(htim2.TIM_TimeBase.TIM_Prescaler + 1)); // ms
			PWM_DC = 100.0*(TIM_GetCapture(htim2.pTIMx, TIM_CH2)+1)/(cc1r + 1);
		}else{
			PWM_T = 0;
			PWM_DC = 0;
		}
		snprintf((char *)msg, sizeof(msg),"T: %ldms  DC: %.2f%%\r\n", PWM_T, PWM_DC);
		USART2_SendData(msg, strlen((char *)msg));

		delay(500000);
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
