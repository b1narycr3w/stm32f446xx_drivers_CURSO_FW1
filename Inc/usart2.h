
#ifndef USART2_H_
#define USART2_H_

#include <stm32f446xx.h>
#include "stm32f446xx_gpio.h"
#include "stm32f446xx_rcc.h"

#define USART2_BASEADDRESS		(0x40004400UL)
#define USART2_CR1_ADDR			(USART2_BASEADDRESS + 0x0C)
#define USART2_BRR_ADDR			(USART2_BASEADDRESS + 0x08)
#define USART2_DR_ADDR			(USART2_BASEADDRESS + 0x04)
#define USART2_SR_ADDR			(USART2_BASEADDRESS + 0x00)


void USART2_Init(void);
void USART2_SendData(uint8_t *pTxBuffer, uint32_t len);
void USART2_PIN_setup(void);

#endif /* USART2_H_ */
