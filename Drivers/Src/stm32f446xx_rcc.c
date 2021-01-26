
#include "stm32f446xx_rcc.h"





/**
  * @brief  Configura el External High Speed oscillator (HSE).
  * @note   Posteriormente a la habilitación del HSE (RCC_HSE_ON o RCC_HSE_Bypass),
  * 		la aplicación debe esperar a que se setee el flag HSERDY antes de usarlo
  * 		como clock.
  * @note   No se puede cambiar el estado del HSE si está siendo usado (directamente o
  * 		a través del PLL) como clock del sistema. En ese caso, hay que configurar
  * 		primero otra fuente como reloj del sistema antes de configurar el HSE.
  * @note   Esta función resetea el bit CSSON por lo que, si el Clock security system(CSS)
  *         está siendo usado habrá que habilitarlo otra vez después de llamar a esta función.
  * @param  HSE_Status: estado del HSE, cuyos valores pueden ser:
  *            @arg RCC_HSE_OFF: deshabilita el HSE, el flag HSERDY se resetea después de
  *            					 6 ciclos de reloj.
  *            @arg RCC_HSE_ON: habilita el HSE
  *            @arg RCC_HSE_BYP: habilita el HSE para ser usado por una señal de reloj externa
  * @retval None
  */
void RCC_HSEConfig(RCC_HSE_Status_t HSE_Status)
{
	// Limpiar los bits del HSE antes de configurarlo (RCC_HSE_OFF)
	RCC->CR &= ~((RCC_CR_HSEON)|(RCC_CR_HSEBYP)|(RCC_CR_CSSON));

	if(HSE_Status == RCC_HSE_ON){
		RCC->CR |= (1 << RCC_CR_HSEON);
	}else if(HSE_Status == RCC_HSE_BYP){
		RCC->CR |= ((1 << RCC_CR_HSEBYP)|(1 << RCC_CR_HSEON));
	}
}

/**
  * @brief  Configura el External Low Speed oscillator (LSE).
  * @note 	Como el LSE está en el dominio de Backup y, después del reset, el acceso de
  * 		escritura no está permitido en ese dominio, es necesario habilitarlo mediante
  * 		el seteo del bit DBP (Disable backup domain write protection) en el registro
  * 		PWR_CR (Power Control Register).
  * @note   Posteriormente a la habilitación del LSE (RCC_LSE_ON o RCC_LSE_Bypass),
  * 		la aplicación debe esperar a que se setee el flag LSERDY antes de usarlo
  * 		como clock para el RTC.
  * @param  LSE_Status: estado del LSE, cuyos valores pueden ser:
  *            @arg RCC_LSE_OFF: deshabilita el LSE, el flag LSERDY se resetea después de
  *            					 6 ciclos de reloj.
  *            @arg RCC_LSE_ON: habilita el LSE
  *            @arg RCC_LSE_BYP: habilita el LSE para ser usado por una señal de reloj externa
  * @retval None
  */
void RCC_LSEConfig(RCC_LSE_Status_t LSE_Status)
{
	// Habilitar escritura
	PWR_EN_CLK();
	PWR->CR |= (1 << PWR_CR_DBP);

	// Limpiar los bits del LSE antes de configurarlo (RCC_LSE_OFF)
	RCC->BDCR &= ~((RCC_BDCR_LSEBYP)|(RCC_BDCR_LSEON)|(RCC_BDCR_LSEMOD));

	if(LSE_Status == RCC_LSE_ON){
		RCC->BDCR |= (1 << RCC_BDCR_LSEON);
	}else if(LSE_Status == RCC_LSE_BYP){
		RCC->BDCR |= ((1 << RCC_BDCR_LSEBYP)|(1 << RCC_BDCR_LSEON));
	}
}

void RCC_PLLConfig(RCC_PLL_Source_t PLL_Source, uint32_t PLLM, uint32_t PLLN, uint32_t PLLP, uint32_t PLLQ, uint32_t PLLR)
{
	uint32_t temp_RCC_PLLCFGR;

	ASSERT_TRUE(IS_VALID_PLLM_VALUE(PLLM));
	ASSERT_TRUE(IS_VALID_PLLN_VALUE(PLLN));
	ASSERT_TRUE(IS_VALID_PLLP_VALUE(PLLP));
	ASSERT_TRUE(IS_VALID_PLLQ_VALUE(PLLQ));
	ASSERT_TRUE(IS_VALID_PLLR_VALUE(PLLR));

	temp_RCC_PLLCFGR = PLLM | ( PLLN << RCC_PLLCFGR_PLLN) | ((PLLP >> 1) - 1) << RCC_PLLCFGR_PLLP | (PLL_Source << RCC_PLLCFGR_PLLSRC) |
			(PLLQ << RCC_PLLCFGR_PLLQ) | (PLLR << RCC_PLLCFGR_PLLR);

	RCC->PLLCFGR = temp_RCC_PLLCFGR;
}

void RCC_HSICmd(uint8_t status)
{
	if(status == ENABLE){
		RCC->CR |= (1 << RCC_CR_HSION);
	}else if(status == DISABLE){
		RCC->CR &= ~(1 << RCC_CR_HSION);
	}
}
void RCC_LSICmd(uint8_t status)
{
	if(status == ENABLE){
		RCC->CSR |= (1 << RCC_CSR_LSION);
	}else if(status == DISABLE){
		RCC->CSR &= ~(1 << RCC_CSR_LSION);
	}
}
void RCC_PLLCmd(uint8_t status)
{
	if(status == ENABLE){
		RCC->CR |= (1 << RCC_CR_PLLON);
	}else if(status == DISABLE){
		RCC->CR &= ~(1 << RCC_CR_PLLON);
	}
}

void RCC_MCO1Config(RCC_MCO1_Source_t MCO1_Source, RCC_MCO1_Prescaler_t MCO1_Prescaler)
{
	uint32_t temp_RCC_CFGR;
	temp_RCC_CFGR = RCC->CFGR;

	// Limpiar los bits de source
	temp_RCC_CFGR &= ~(0x03 << RCC_CFGR_MCO1);
	// Seteamos los bit de source
	temp_RCC_CFGR |= (MCO1_Source << RCC_CFGR_MCO1);

	// Limpiar los bits de prescaler
	temp_RCC_CFGR &= ~(0x07 << RCC_CFGR_MCO1PRE);
	// Seteamos los bit de prescaler
	temp_RCC_CFGR |= (MCO1_Prescaler << RCC_CFGR_MCO1PRE);

	RCC->CFGR = temp_RCC_CFGR;
}

void RCC_WaitForCLKRDY(RCC_Clock_t clk)
{
	if(clk == RCC_Clock_HSI){
		while(!(RCC->CR & (1 << RCC_CR_HSIRDY)));
	}else if(clk == RCC_Clock_HSE){
		while(!(RCC->CR & (1 << RCC_CR_HSERDY)));
	}else if(clk == RCC_Clock_PLL){
		while(!(RCC->CR & (1 << RCC_CR_PLLRDY)));
	}else if(clk == RCC_Clock_LSE){
		while(!(RCC->BDCR & (1 << RCC_BDCR_LSERDY)));
	}
}

void RCC_SYSCLKConfig(RCC_SYSCLK_Source_t SYSCLK_Source)
{
	uint32_t temp_RCC_CFGR;
	temp_RCC_CFGR = RCC->CFGR;

	// Limpiar bits de source
	temp_RCC_CFGR &= ~(0x03 << RCC_CFGR_SW);

	// Setear bits de source
	temp_RCC_CFGR |= (SYSCLK_Source << RCC_CFGR_SW);

	RCC->CFGR = temp_RCC_CFGR;
}

RCC_SYSCLK_Source_t RCC_GetSYSCLKSource(void)
{
	uint32_t sws;

	sws = (RCC->CFGR & 0x0C) >> RCC_CFGR_SWS;

	return (RCC_SYSCLK_Source_t)sws;
}

void RCC_AHBCLKConfig(RCC_AHB_Prescaler_t AHB_Prescaler)
{
	uint32_t temp_RCC_CFGR;
	temp_RCC_CFGR = RCC->CFGR;

	// Limpiar bits de prescaler
	temp_RCC_CFGR &= ~(0x0F << RCC_CFGR_HPRE);

	// Setear bits de prescaler
	temp_RCC_CFGR |= (AHB_Prescaler << RCC_CFGR_HPRE);

	RCC->CFGR = temp_RCC_CFGR;
}

void RCC_APB1CLKConfig(RCC_APB_Prescaler_t APB1_Prescaler)
{
	uint32_t temp_RCC_CFGR;
	temp_RCC_CFGR = RCC->CFGR;

	// Limpiar bits de prescaler
	temp_RCC_CFGR &= ~(0x07 << RCC_CFGR_PPRE1);

	// Setear bits de prescaler
	temp_RCC_CFGR |= (APB1_Prescaler << RCC_CFGR_PPRE1);

	RCC->CFGR = temp_RCC_CFGR;
}

void RCC_APB2CLKConfig(RCC_APB_Prescaler_t APB2_Prescaler)
{
	uint32_t temp_RCC_CFGR;
	temp_RCC_CFGR = RCC->CFGR;

	// Limpiar bits de prescaler
	temp_RCC_CFGR &= ~(0x07 << RCC_CFGR_PPRE2);

	// Setear bits de prescaler
	temp_RCC_CFGR |= (APB2_Prescaler << RCC_CFGR_PPRE2);

	RCC->CFGR = temp_RCC_CFGR;
}

uint32_t RCC_GetSYSCLK(void)
{
	uint32_t PLL_src;
	uint32_t PLL_M;
	uint32_t PLL_N;
	uint32_t PLL_VCO;
	uint32_t PLL_P;
	uint32_t PLL_R;
	uint32_t freq;
	uint32_t rcc_cfgr_sws;

	rcc_cfgr_sws = (RCC->CFGR >> RCC_CFGR_SWS) & 0x03;

	if(rcc_cfgr_sws == 0){
		/* HSI */
		freq = HSI_FREQ;
	}else if(rcc_cfgr_sws == 1){
		/* HSE */
		freq = HSE_FREQ;
	}if(rcc_cfgr_sws == 2){
		/********************** PLL P **********************
		 *  PLL_VCO = (PLL_src / PLLM) * PLLN
		 *  SYSCLK = PLL_VCO / PLLP
		 ***************************************************/
		PLL_src = (RCC->PLLCFGR >> RCC_PLLCFGR_PLLSRC) & 0x01;
		PLL_M = RCC->PLLCFGR & 0x3F;
		PLL_N = (RCC->PLLCFGR >> RCC_PLLCFGR_PLLN) & 0x1FF;

		if(PLL_src){
			/* HSE es la fuente de reloj del PLL */
			PLL_VCO = (HSE_FREQ / PLL_M) * PLL_N;
		}else{
			/* HSI es la fuente de reloj del PLL */
			PLL_VCO = (HSI_FREQ / PLL_M) * PLL_N;
		}
		PLL_P = (((RCC->PLLCFGR >> RCC_PLLCFGR_PLLP) & 0x03) + 1) * 2;
		freq = PLL_VCO / PLL_P;
	}if(rcc_cfgr_sws == 3){
		/********************** PLL R **********************
		 *  PLL_VCO = (PLL_src / PLLM) * PLLN
		 *  SYSCLK = PLL_VCO / PLLR
		 ***************************************************/
		PLL_src = (RCC->PLLCFGR >> RCC_PLLCFGR_PLLSRC) & 0x01;
		PLL_M = RCC->PLLCFGR & 0x3F;
		PLL_N = (RCC->PLLCFGR >> RCC_PLLCFGR_PLLN) & 0x1FF;

		if(PLL_src){
			/* HSE es la fuente de reloj del PLL */
			PLL_VCO = (HSE_FREQ / PLL_M) * PLL_N;
		}else{
			/* HSI es la fuente de reloj del PLL */
			PLL_VCO = (HSI_FREQ / PLL_M) * PLL_N;
		}
		PLL_R = (RCC->PLLCFGR >> RCC_PLLCFGR_PLLR) & 0x07;
		freq = PLL_VCO / PLL_R;
	}

	return freq;
}

uint16_t AHB_prescaler[16] = {1,1,1,1,1,1,1,1,2,4,8,16,64,128,256,512};
uint16_t APBx_prescaler[8] = {1,1,1,1,2,4,8,16};

uint32_t RCC_GetAHBCLK(void)
{
	uint32_t rcc_cfgr_hpre;
	uint16_t prescaler;

	rcc_cfgr_hpre = (RCC->CFGR >> RCC_CFGR_HPRE) & 0x0F;
	prescaler = AHB_prescaler[rcc_cfgr_hpre];

	return RCC_GetSYSCLK()/prescaler;

}

uint32_t RCC_GetAPB1CLK(void)
{
	uint32_t rcc_cfgr_ppre1;
	uint16_t prescaler;

	rcc_cfgr_ppre1 = (RCC->CFGR >> RCC_CFGR_PPRE1) & 0x07;
	prescaler = APBx_prescaler[rcc_cfgr_ppre1];

	return RCC_GetAHBCLK()/prescaler;
}

uint32_t RCC_GetAPB2CLK(void)
{
	uint32_t rcc_cfgr_ppre2;
	uint16_t prescaler;

	rcc_cfgr_ppre2 = (RCC->CFGR >> RCC_CFGR_PPRE2) & 0x07;
	prescaler = APBx_prescaler[rcc_cfgr_ppre2];

	return RCC_GetAHBCLK()/prescaler;
}

uint32_t RCC_GetAPB1_TimerCLK(void)
{
	uint32_t rcc_cfgr_ppre1;
	rcc_cfgr_ppre1 = (RCC->CFGR >> RCC_CFGR_PPRE1) & 0x07;

	if(rcc_cfgr_ppre1 == RCC_APB_Prescaler_None)
		return RCC_GetAPB1CLK();

	return RCC_GetAPB1CLK()*2;
}

uint32_t RCC_GetAPB2_TimerCLK(void)
{
	uint32_t rcc_cfgr_ppre2;
	rcc_cfgr_ppre2 = (RCC->CFGR >> RCC_CFGR_PPRE2) & 0x07;

	if(rcc_cfgr_ppre2 == RCC_APB_Prescaler_None)
		return RCC_GetAPB2CLK();

	return RCC_GetAPB2CLK()*2;
}







