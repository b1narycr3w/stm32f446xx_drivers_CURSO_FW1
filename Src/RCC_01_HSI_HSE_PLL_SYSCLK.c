

#include <stm32f446xx.h>
#include "stm32f446xx_gpio.h"
#include "stm32f446xx_rcc.h"



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
	PC10_debug.GPIO_config.GPIO_OType = GPIO_OType_PP;
	PC10_debug.GPIO_config.GPIO_PuPd = GPIO_PuPd_NONE;
	PC10_debug.GPIO_config.GPIO_Speed = GPIO_Speed_FAST;

	GPIO_Init(&PC10_debug);

	GPIO_handle_t PA8_MCO1;

	PA8_MCO1.pGPIOx = GPIOA;
	PA8_MCO1.GPIO_config.GPIO_Pin = GPIO_PIN_8;
	PA8_MCO1.GPIO_config.GPIO_Mode = GPIO_Mode_AF;
	PA8_MCO1.GPIO_config.GPIO_AltFun = GPIO_ALTFUN_0;
	PA8_MCO1.GPIO_config.GPIO_Speed = GPIO_Speed_FAST;

	GPIO_Init(&PA8_MCO1);
}

void SYSCLK_HSE_setup(void)
{
	// Habilitar HSE
	RCC_HSEConfig(RCC_HSE_ON);

	// Esperar a que HSE este OK
	RCC_WaitForCLKRDY(RCC_Clock_HSE);

	// Activar el bit de bypass
	RCC->CR |= (1 << RCC_CR_HSEBYP);

	// Seleccionar HSE como fuente de reloj del sistema
	RCC_SYSCLKConfig(RCC_SYSCLK_Source_HSE);
}

void SYSCLK_HSI_setup(void)
{
	// Habilitar HSI
	RCC_HSICmd(ENABLE);

	// Esperar a que HSI este OK
	RCC_WaitForCLKRDY(RCC_Clock_HSI);

	// Seleccionar HSI como fuente de reloj del sistema
	RCC_SYSCLKConfig(RCC_SYSCLK_Source_HSI);
}

void SYSCLK_PLL_setup(void)
{
	uint32_t PLLM, PLLN, PLLP, PLLQ, PLLR;
	PLLM = 8;
	PLLN = 336;
	PLLP = 2;
	PLLQ = 7;
	PLLR = 5;

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

	GPIO_setup();

	delay(500000);

	/*********************** HSE ***********************/
	// 1. Configurar HSE como fuente de reloj del sistema
	SYSCLK_HSE_setup();
	// 2. Configurar MCO1 para sacar HSE por su pin
	RCC_MCO1Config(RCC_MCO1_Source_HSE, RCC_MCO1_Prescaler_4);
	// 3. Leer frecuencia de SYSCLK
	freq = RCC_GetSYSCLK();
	// 4. Mostrar tiempo de procesamiento de espera en PC10
	GPIO_WritePin(GPIOC, GPIO_PIN_10, SET);
	delay(500000);
	GPIO_WritePin(GPIOC, GPIO_PIN_10, RESET);

	delay(500000);

	/*********************** HSI ***********************/
	// 1. Configurar HSI como fuente de reloj del sistema
	SYSCLK_HSI_setup();
	// 2. Configurar MCO1 para sacar HSI por su pin
	RCC_MCO1Config(RCC_MCO1_Source_HSI, RCC_MCO1_Prescaler_4);
	// 3. Leer frecuencia de SYSCLK
	freq = RCC_GetSYSCLK();
	// 4. Mostrar tiempo de procesamiento de espera en PC10
	GPIO_WritePin(GPIOC, GPIO_PIN_10, SET);
	delay(500000);
	GPIO_WritePin(GPIOC, GPIO_PIN_10, RESET);
	delay(500000);

	/*********************** PLL ***********************/
	// 1. Configurar PLL como fuente de reloj del sistema
	SYSCLK_PLL_setup();
	// 2. Configurar MCO1 para sacar PLL por su pin
	RCC_MCO1Config(RCC_MCO1_Source_PLL, RCC_MCO1_Prescaler_5);
	// 3. Leer frecuencia de SYSCLK
	freq = RCC_GetSYSCLK();
	// 4. Mostrar tiempo de procesamiento de espera en PC10
	GPIO_WritePin(GPIOC, GPIO_PIN_10, SET);
	delay(500000);
	GPIO_WritePin(GPIOC, GPIO_PIN_10, RESET);

	while(1){
	}
}

void assert_failed(uint8_t *file, uint32_t line)
{
	while(1);
}
