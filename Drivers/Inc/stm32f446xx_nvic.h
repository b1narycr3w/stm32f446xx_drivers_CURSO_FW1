

#ifndef INC_STM32F446XX_NVIC_H_
#define INC_STM32F446XX_NVIC_H_

#include "stm32f446xx.h"

void NVIC_IRQ_Enable(uint8_t IRQ);
void NVIC_IRQ_Disable(uint8_t IRQ);
void NVIC_Priority(uint8_t IRQ, uint32_t priority);

#endif /* INC_STM32F446XX_NVIC_H_ */
