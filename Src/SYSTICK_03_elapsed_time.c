#include <stdio.h>
#include <string.h>

#include <stm32f446xx.h>
#include "stm32f446xx_gpio.h"
#include "stm32f446xx_nvic.h"
#include "stm32f446xx_rcc.h"
#include "stm32f446xx_systick.h"

#include "usart2.h"


GPIO_handle_t LED;
uint32_t systick_delay;
uint32_t system_ticks;
uint8_t button_pressed_f;

void SYSCLK_PLL_setup(void);

void delay_ms(uint32_t ms)
{
	systick_delay = ms;
	while(systick_delay);
}

void EXTI15_10_IRQHandler(void)
{
	GPIO_IRQHandler(GPIO_PIN_13);

	button_pressed_f = 1;
}

void SysTick_Handler(void)
{
	if(systick_delay > 0)
		systick_delay--;

	system_ticks++;
}

void GPIO_setup(void)
{
	GPIO_handle_t Button;
	Button.pGPIOx = GPIOC;
	Button.GPIO_config.GPIO_Mode = GPIO_Mode_IT_FE;
	Button.GPIO_config.GPIO_Pin = GPIO_PIN_13;
	Button.GPIO_config.GPIO_PuPd = GPIO_PuPd_NONE;
	Button.GPIO_config.GPIO_Speed = GPIO_Speed_LOW;

	GPIO_Init(&Button);
}

void SYSTICK_setup(void)
{
	SYSTICK_Config_t SYSTICK_Config = {0};

	SYSTICK_Config.SYSTICK_Clock_Source = SYSTICK_Clk_Source_External;
	SYSTICK_Config.SYSTICK_Period = (SYSTICK_GetCalib() & 0x00FFFFFF) - 1;

	SYSTICK_Init(&SYSTICK_Config);
}

int main(void)
{
	uint32_t last_ticks = 0;
	uint32_t current_ticks;
	uint32_t elapsed_ticks;
	uint8_t system_ticks_overflow;
	uint8_t msg[64];

	SYSCLK_PLL_setup();
	GPIO_setup();
	SYSTICK_setup();

	USART2_PIN_setup();
	USART2_Init();

	SYSTICK_ITConfig(ENABLE);
	SYSTICK_Cmd(ENABLE);

	NVIC_IRQ_Enable(IRQ_EXTI15_10);

	while(1){
		if(button_pressed_f){
			current_ticks = system_ticks;
			delay_ms(100);
			button_pressed_f = 0;

			if(current_ticks >= last_ticks){
				system_ticks_overflow = 0;
				elapsed_ticks = current_ticks - last_ticks;
			}else{
				system_ticks_overflow = 1;
				elapsed_ticks = (0xffffffff - last_ticks - 1) + current_ticks;
			}
			snprintf((char *)msg, sizeof(msg),"ET: %ld [ms] (overflow: %d)\r\n", elapsed_ticks, system_ticks_overflow);
			USART2_SendData(msg, strlen((char *)msg));

			last_ticks = current_ticks;
		}
	}
}


void SYSCLK_PLL_setup(void)
{
	uint32_t PLLM, PLLN, PLLP, PLLQ, PLLR;
	// 150MHz
	PLLM = 4;
	PLLN = 150;
	PLLP = 2;
	PLLR = 2;
	PLLQ = 8;

	// Configurar prescaler APB1 y APB2
	RCC_APB1CLKConfig(RCC_APB_Prescaler_4); // 37.5MHz
	RCC_APB2CLKConfig(RCC_APB_Prescaler_2); // 75MHz

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
	*((volatile uint32_t *)0x40023C00) = 0x04;

	// Seleccionar PLL_P como fuente de reloj del sistema
	RCC_SYSCLKConfig(RCC_SYSCLK_Source_PLL_P);

}

void assert_failed(uint8_t *file, uint32_t line){
	while(1);
}

