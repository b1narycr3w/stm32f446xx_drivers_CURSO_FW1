

#include "stm32f446xx_systick.h"



void SYSTICK_Init(SYSTICK_Config_t *SYSTICK_config)
{
	SYSTICK_Cmd(DISABLE);
	SYSTICK->CSR &= (1 << SYSTICK_CSR_CLKSOURCE);
	SYSTICK->CSR |= (SYSTICK_config->SYSTICK_Clock_Source << SYSTICK_CSR_CLKSOURCE);

	SYSTICK->RVR = SYSTICK_config->SYSTICK_Period;
}

void SYSTICK_Cmd(uint8_t status)
{
	if(status == ENABLE){
		SYSTICK->CSR |= (1 << SYSTICK_CSR_ENABLE);
	}if(status == DISABLE){
		SYSTICK->CSR &= ~(1 << SYSTICK_CSR_ENABLE);
	}
}

void SYSTICK_ITConfig(uint8_t status)
{
	if(status == ENABLE){
		SYSTICK->CSR |= (1 << SYSTICK_CSR_TICKINT);
	}if(status == DISABLE){
		SYSTICK->CSR &= ~(1 << SYSTICK_CSR_TICKINT);
	}
}

uint32_t SYSTICK_GetCounter(void)
{
	return SYSTICK->CVR;
}

void SYSTICK_SetPeriod(uint32_t value)
{
	SYSTICK->RVR = value;
}

uint8_t SYSTICK_GetCountFlag(void)
{
	return ((SYSTICK->CSR & (1 << SYSTICK_CSR_COUNTFLAG)) != 0);
}

uint32_t SYSTICK_GetCalib(void)
{
	return SYSTICK->CALIB;
}

