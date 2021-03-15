

#include "stm32f446xx_iwdg.h"


void IWDG_Init(IWDG_Config_t *IWDG_Config)
{
	IWDG_cmd(ENABLE);
	IWDG_WriteAccess(ENABLE);

	while(IWDG_GetFlag(IWDG_StatusFlag_PVU));
	IWDG_SetPrescaler(IWDG_Config->IWDG_Prescaler);

	while(IWDG_GetFlag(IWDG_StatusFlag_RVU));
	IWDG_SetPeriod(IWDG_Config->IWDG_Period);

	while(IWDG->SR & 0x03);
}

void IWDG_Refresh(void)
{
	IWDG->KR = IWDG_RELOAD_KEY;
}

void IWDG_cmd(uint8_t status)
{
	if(status == ENABLE){
		IWDG->KR = IWDG_ENABLE_KEY;
	}else if(status == DISABLE){
		IWDG->KR = IWDG_DISABLE_KEY;
	}
}

void IWDG_WriteAccess(uint8_t status)
{
	if(status == ENABLE){
		IWDG->KR = IWDG_WRITEACCESS_KEY;
	}else if(status == DISABLE){
		IWDG->KR = IWDG_DISABLE_KEY;
	}
}

void IWDG_SetPrescaler(IWDG_Prescaler_t prescaler)
{
	IWDG->PR = (prescaler & 0x07);
}

void IWDG_SetPeriod(uint32_t period)
{
	IWDG->RLR = (period & 0xFFF);
}

uint8_t IWDG_GetFlag(IWDG_StatusFlag_t flag)
{
	return (IWDG->SR & (1 << flag));
}
