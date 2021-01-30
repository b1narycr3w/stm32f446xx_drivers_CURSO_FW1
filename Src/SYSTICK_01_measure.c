#include <stdio.h>
#include <string.h>

#include <stm32f446xx.h>
#include "stm32f446xx_gpio.h"
#include "stm32f446xx_nvic.h"
#include "stm32f446xx_rcc.h"
#include "stm32f446xx_systick.h"

void SYSCLK_PLL_setup(void);

void delay(uint32_t cnt)
{
	while(cnt)
		cnt--;
}

void GPIO_setup(void)
{
	GPIO_handle_t PC10_debug;

	PC10_debug.pGPIOx = GPIOC;
	PC10_debug.GPIO_config.GPIO_Pin = GPIO_PIN_10;
	PC10_debug.GPIO_config.GPIO_Mode = GPIO_Mode_OUT;
	PC10_debug.GPIO_config.GPIO_Speed = GPIO_Speed_FAST;

	GPIO_Init(&PC10_debug);
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
	SYSCLK_PLL_setup();

	GPIO_setup();
	SYSTICK_setup();

	SYSTICK_ITConfig(ENABLE);
	SYSTICK_Cmd(ENABLE);

	while(1){

		delay(50000);
	}
}

void SysTick_Handler(void)
{
	GPIO_TogglePin(GPIOC, GPIO_PIN_10);
}


void SYSCLK_PLL_setup(void)
{
	uint32_t PLLM, PLLN, PLLP, PLLQ, PLLR;
	// 150MHz
	PLLM = 4;
	PLLN = 150;
	PLLP = 2;
	PLLR = 5;
	PLLQ = 4;

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

