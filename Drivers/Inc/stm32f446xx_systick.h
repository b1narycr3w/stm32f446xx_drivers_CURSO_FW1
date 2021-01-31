
#ifndef INC_STM32F446XX_SYSTICK_H_
#define INC_STM32F446XX_SYSTICK_H_

#include "stm32f446xx.h"

/*
 * @SYSTICK_Clk_Source
 */
typedef enum{
	SYSTICK_Clk_Source_External,
	SYSTICK_Clk_Source_Processor
}SYSTICK_Clk_Source_t;

typedef struct{
	uint32_t SYSTICK_Period;
	SYSTICK_Clk_Source_t SYSTICK_Clock_Source;
}SYSTICK_Config_t;

void SYSTICK_Init(SYSTICK_Config_t *SYSTICK_config);
void SYSTICK_Cmd(uint8_t status);
void SYSTICK_ITConfig(uint8_t status);

uint32_t SYSTICK_GetCounter(void);
void SYSTICK_SetPeriod(uint32_t value);
uint8_t SYSTICK_GetCountFlag(void);
uint32_t SYSTICK_GetCalib(void);

#endif /* INC_STM32F446XX_SYSTICK_H_ */
