

#include "usart2.h"


void USART2_PIN_setup(void)
{
	GPIO_handle_t USART2_PINs = {0};

	/*
	 * PA2 -> USART2_TX
	 * PA3 -> USART2_RX
	 * ALT function mode : 7
	 */

	USART2_PINs.pGPIOx = GPIOA;
	USART2_PINs.GPIO_config.GPIO_Mode = GPIO_Mode_AF;
	USART2_PINs.GPIO_config.GPIO_AltFun = 7;
	USART2_PINs.GPIO_config.GPIO_OType = GPIO_OType_PP;
	USART2_PINs.GPIO_config.GPIO_Speed = GPIO_Speed_FAST;
	USART2_PINs.GPIO_config.GPIO_PuPd = GPIO_PuPd_UP;

	// TX
	USART2_PINs.GPIO_config.GPIO_Pin = GPIO_PIN_2;
	GPIO_Init(&USART2_PINs);

	// RX
	USART2_PINs.GPIO_config.GPIO_Pin = GPIO_PIN_3;
	GPIO_Init(&USART2_PINs);

}

void USART2_Init(void)
{
	uint32_t tempreg = 0;
	uint8_t carry = 0;

	// Enable USART2 peripheral clock
	RCC->APB1ENR |= (1 << 17);
	tempreg |= (1 << 3) | (1 << 2);
	*((volatile uint32_t *)(USART2_CR1_ADDR)) = tempreg;
	uint32_t APB1Clk;
	APB1Clk = RCC_GetAPB1CLK();
	uint32_t usartdiv = (APB1Clk * 100)/(16*115200);
	uint32_t DIV_Fraction = (usartdiv % 100)*16;
	DIV_Fraction = (DIV_Fraction + 50)/100;
	if(DIV_Fraction >= 16){
		carry = 1;
		DIV_Fraction = 0;
	}
	uint32_t DIV_Mantissa = usartdiv/100 + carry;
	tempreg = 0;
	tempreg |= (DIV_Mantissa << 4) | (DIV_Fraction & 0x0f);
	*((volatile uint32_t *)(USART2_BRR_ADDR)) = tempreg;

	*((volatile uint32_t *)(USART2_CR1_ADDR)) |= (1 << 13);
}

void USART2_SendData(uint8_t *pTxBuffer, uint32_t len)
{
	for(uint32_t i = 0 ; i < len; i++){
		while(!(*((volatile uint32_t *)(USART2_SR_ADDR)) & (1 << 7)));
		*((volatile uint32_t *)(USART2_DR_ADDR)) = (*pTxBuffer  & (uint8_t)0xFF);
		pTxBuffer++;
	}

	while(!(*((volatile uint32_t *)(USART2_SR_ADDR)) & (1 << 6)));
}
