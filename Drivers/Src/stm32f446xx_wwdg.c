
#include "stm32f446xx_wwdg.h"

void WWDG_Init(WWDG_Config_t *WWDG_Config)
{
	uint32_t temp_reg;

	// Habilitar clock
	WWDG_EN_CLK();

	// Set prescaler
	temp_reg = WWDG->CFR;
	temp_reg &= ~(0x03 << WWDG_CFR_WDGTB);
	temp_reg |= WWDG_Config->WWDG_Prescaler << WWDG_CFR_WDGTB;
	WWDG->CFR = temp_reg;

	// Set counter
	temp_reg = WWDG->CR;
	temp_reg &= ~0x7F;
	temp_reg |= WWDG_Config->WWDG_Counter & 0x7F;
	WWDG->CR = temp_reg;

	// Set window
	temp_reg = WWDG->CFR;
	temp_reg &= ~0x7F;
	temp_reg |= WWDG_Config->WWDG_Window & 0x7F;
	WWDG->CFR = temp_reg;
}

void WWDG_Deinit(void)
{
	WWDG_RESET();
}

void WWDG_cmd(uint8_t status)
{
	if(status == ENABLE){
		WWDG->CR |= (1 << WWDG_CR_WDGA);
	}else if(status == DISABLE){
		WWDG->CR &= ~(1 << WWDG_CR_WDGA);
	}
}

void WWDG_Refresh(WWDG_Config_t *WWDG_Config)
{
	uint32_t temp_reg;
	temp_reg = WWDG->CR;

	temp_reg &= ~0x7F;
	temp_reg |= WWDG_Config->WWDG_Counter & 0x7F;

	WWDG->CR = temp_reg;
}

uint8_t WWDG_GetFlag(void)
{
	return (WWDG->SR & 0x01);
}

void WWDG_ITConfig(uint8_t status)
{
	if(status == ENABLE){
		WWDG->CFR |= (1 << WWDG_CFR_EWI);
	}else if(status == DISABLE){
		WWDG->CFR &= ~(1 << WWDG_CFR_EWI);
	}
}
