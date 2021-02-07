

#include <stm32f446xx_tim.h>
#include <sys/_stdint.h>




void TIM_ClkCtrl(TIM_RegDef_t *pTIMx, uint8_t status)
{
	if(status == ENABLE){
		if(pTIMx == TIM1)
			TIM1_EN_CLK();
		else if(pTIMx == TIM2)
			TIM2_EN_CLK();
		else if(pTIMx == TIM3)
			TIM3_EN_CLK();
		else if(pTIMx == TIM4)
			TIM4_EN_CLK();
		else if(pTIMx == TIM5)
			TIM5_EN_CLK();
		else if(pTIMx == TIM6)
			TIM6_EN_CLK();
		else if(pTIMx == TIM7)
			TIM7_EN_CLK();
		else if(pTIMx == TIM8)
			TIM8_EN_CLK();
		else if(pTIMx == TIM9)
			TIM9_EN_CLK();
		else if(pTIMx == TIM10)
			TIM10_EN_CLK();
		else if(pTIMx == TIM11)
			TIM11_EN_CLK();
		else if(pTIMx == TIM12)
			TIM12_EN_CLK();
		else if(pTIMx == TIM13)
			TIM13_EN_CLK();
		else if(pTIMx == TIM14)
			TIM14_EN_CLK();
	}else if(status == DISABLE){
		if(pTIMx == TIM1)
			TIM1_DIS_CLK();
		else if(pTIMx == TIM2)
			TIM2_DIS_CLK();
		else if(pTIMx == TIM3)
			TIM3_DIS_CLK();
		else if(pTIMx == TIM4)
			TIM4_DIS_CLK();
		else if(pTIMx == TIM5)
			TIM5_DIS_CLK();
		else if(pTIMx == TIM6)
			TIM6_DIS_CLK();
		else if(pTIMx == TIM7)
			TIM7_DIS_CLK();
		else if(pTIMx == TIM8)
			TIM8_DIS_CLK();
		else if(pTIMx == TIM9)
			TIM9_DIS_CLK();
		else if(pTIMx == TIM10)
			TIM10_DIS_CLK();
		else if(pTIMx == TIM11)
			TIM11_DIS_CLK();
		else if(pTIMx == TIM12)
			TIM12_DIS_CLK();
		else if(pTIMx == TIM13)
			TIM13_DIS_CLK();
		else if(pTIMx == TIM14)
			TIM14_DIS_CLK();
	}
}

void TIM_DeInit(TIM_RegDef_t *pTIMx)
{
	if(pTIMx == TIM1)
		TIM1_RESET();
	else if(pTIMx == TIM2)
		TIM2_RESET();
	else if(pTIMx == TIM3)
		TIM3_RESET();
	else if(pTIMx == TIM4)
		TIM4_RESET();
	else if(pTIMx == TIM5)
		TIM5_RESET();
	else if(pTIMx == TIM6)
		TIM6_RESET();
	else if(pTIMx == TIM7)
		TIM7_RESET();
	else if(pTIMx == TIM8)
		TIM8_RESET();
	else if(pTIMx == TIM9)
		TIM9_RESET();
	else if(pTIMx == TIM10)
		TIM10_RESET();
	else if(pTIMx == TIM11)
		TIM11_RESET();
	else if(pTIMx == TIM12)
		TIM12_RESET();
	else if(pTIMx == TIM13)
		TIM13_RESET();
	else if(pTIMx == TIM14)
		TIM14_RESET();
}

uint8_t TIM_GetITStatus(TIM_RegDef_t *pTIMx, uint16_t TIM_IT)
{
	uint16_t IT_status = 0x0, IT_enable = 0x0;

	IT_status = pTIMx->SR & TIM_IT;
	IT_enable = pTIMx->DIER & TIM_IT;

	if ((IT_status != (uint16_t)RESET) && (IT_enable != (uint16_t)RESET))
		return SET;

	return RESET;
}

void TIM_ClearITPendingBit(TIM_RegDef_t *pTIMx, uint16_t TIM_IT)
{
	pTIMx->SR = (uint16_t)~TIM_IT;
}

void TIM_TimeBaseInit(TIM_handle_t *pTIMHandle)
{
	// Habilitar clock
	TIM_ClkCtrl(pTIMHandle->pTIMx, ENABLE);

	pTIMHandle->pTIMx->ARR = pTIMHandle->TIM_TimeBase.TIM_Period;
	pTIMHandle->pTIMx->PSC = pTIMHandle->TIM_TimeBase.TIM_Prescaler;

	if(!TIM_IS_BASIC_TIMER(pTIMHandle->pTIMx)){
		if(pTIMHandle->TIM_TimeBase.TIM_CounterMode == TIM_CouterMode_UP){
			pTIMHandle->pTIMx->CR1 &= ~(0x03 << TIM_CR1_CMS);
			pTIMHandle->pTIMx->CR1 &= ~(1 << TIM_CR1_DIR);
		}else if(pTIMHandle->TIM_TimeBase.TIM_CounterMode == TIM_CouterMode_DOWN){
			pTIMHandle->pTIMx->CR1 &= ~(0x03 << TIM_CR1_CMS);
			pTIMHandle->pTIMx->CR1 |= 1 << TIM_CR1_DIR;
		}else{
			pTIMHandle->pTIMx->CR1 &= ~(0x03 << TIM_CR1_CMS);
			pTIMHandle->pTIMx->CR1 |= pTIMHandle->TIM_TimeBase.TIM_CounterMode << TIM_CR1_CMS;
		}
	}

	pTIMHandle->pTIMx->EGR = 1;
}

void TIM_ICInit(TIM_handle_t *pTIMHandle)
{
	uint16_t temp_CCMRx = 0, temp_CCER = 0;

	ASSERT_FALSE(TIM_IS_BASIC_TIMER(pTIMHandle->pTIMx));

	// Habilitar clock
	TIM_ClkCtrl(pTIMHandle->pTIMx, ENABLE);

	if(pTIMHandle->TIM_InputCapture.TIM_Channel == TIM_CH1){

		// Reset del bit CC1E para deshabilitar el canal
		pTIMHandle->pTIMx->CCER &= ~(1 << TIM_CCER_CC1E);

		temp_CCMRx = pTIMHandle->pTIMx->CCMR1;
		temp_CCER = pTIMHandle->pTIMx->CCER;

		// Configurar entrada en registro CCMR1
		temp_CCMRx &= ~(0x03 << TIM_CCMR1_CC1S);
		temp_CCMRx |= (pTIMHandle->TIM_InputCapture.TIM_ICSelection << TIM_CCMR1_CC1S);

		// Configurar filtro en registro CCMR1
		temp_CCMRx &= ~(0x0F << TIM_CCMR1_IC1F);
		temp_CCMRx |= (pTIMHandle->TIM_InputCapture.TIM_ICFilter << TIM_CCMR1_IC1F);

		// Input Capture Prescaler
		temp_CCMRx &= ~(0x03 << TIM_CCMR1_IC1PSC);
		temp_CCMRx |= (pTIMHandle->TIM_InputCapture.TIM_ICPrescaler << TIM_CCMR1_IC1PSC);

		// Polaridad en registro CCER
		temp_CCER &= ~((1 << TIM_CCER_CC1P) | (1 << TIM_CCER_CC1NP));
		if(pTIMHandle->TIM_InputCapture.TIM_ICPolarity == TIM_ICPolarity_RE){
			// CC1NP = 0 y CC1P = 0
			// Ya lo estan, nada que hacer
		}else if(pTIMHandle->TIM_InputCapture.TIM_ICPolarity == TIM_ICPolarity_FE){
			// CC1NP = 0 y CC1P = 1
			temp_CCER |= (1 << TIM_CCER_CC1P);
		}else if(pTIMHandle->TIM_InputCapture.TIM_ICPolarity == TIM_ICPolarity_RFE){
			// CC1NP = 1 y CC1P = 1
			temp_CCER |= ((1 << TIM_CCER_CC1P) | (1 << TIM_CCER_CC1NP));
		}

		// Habilitar canal
		temp_CCER |= (1 << TIM_CCER_CC1E);

		// Asignar valores a registros
		pTIMHandle->pTIMx->CCMR1 = temp_CCMRx;
		pTIMHandle->pTIMx->CCER = temp_CCER;

	}else if(pTIMHandle->TIM_InputCapture.TIM_Channel == TIM_CH2){

		ASSERT_TRUE(TIM_HAS_CH2(pTIMHandle->pTIMx));

		// Reset del bit CC2E para deshabilitar el canal
		pTIMHandle->pTIMx->CCER &= ~(1 << TIM_CCER_CC2E);

		temp_CCMRx = pTIMHandle->pTIMx->CCMR1;
		temp_CCER = pTIMHandle->pTIMx->CCER;
		// Configurar entrada en registro CCMR1
		temp_CCMRx &= ~(0x03 << TIM_CCMR1_CC2S);
		temp_CCMRx |= (pTIMHandle->TIM_InputCapture.TIM_ICSelection << TIM_CCMR1_CC2S);

		// Configurar filtro en registro CCMR1
		temp_CCMRx &= ~(0x0F << TIM_CCMR1_IC2F);
		temp_CCMRx |= (pTIMHandle->TIM_InputCapture.TIM_ICFilter << TIM_CCMR1_IC2F);

		// Input Capture Prescaler
		temp_CCMRx &= ~(0x03 << TIM_CCMR1_IC2PSC);
		temp_CCMRx |= (pTIMHandle->TIM_InputCapture.TIM_ICPrescaler << TIM_CCMR1_IC2PSC);

		// Configurar polaridad en registro CCER
		temp_CCER &= ~((1 << TIM_CCER_CC2P) | (1 << TIM_CCER_CC2NP));
		if(pTIMHandle->TIM_InputCapture.TIM_ICPolarity == TIM_ICPolarity_RE){
			// CC2NP = 0 y CC2P = 0
			// Ya lo estan, nada que hacer
		}else if(pTIMHandle->TIM_InputCapture.TIM_ICPolarity == TIM_ICPolarity_FE){
			// CC2NP = 0 y CC2P = 1
			temp_CCER |= (1 << TIM_CCER_CC2P);
		}else if(pTIMHandle->TIM_InputCapture.TIM_ICPolarity == TIM_ICPolarity_RFE){
			// CC2NP = 1 y CC2P = 1
			temp_CCER |= (1 << TIM_CCER_CC2NP);
			temp_CCER |= (1 << TIM_CCER_CC2P);
		}
		// Habilitar el canal
		temp_CCER |= (1 << TIM_CCER_CC2E);

		// Asignar valores a registros
		pTIMHandle->pTIMx->CCMR1 = temp_CCMRx;
		pTIMHandle->pTIMx->CCER = temp_CCER;

	}else if(pTIMHandle->TIM_InputCapture.TIM_Channel == TIM_CH3){

		ASSERT_TRUE(TIM_HAS_CH3(pTIMHandle->pTIMx));

		// Reset del bit CC3E para deshabilitar el canal
		pTIMHandle->pTIMx->CCER &= ~(1 << TIM_CCER_CC3E);

		temp_CCMRx = pTIMHandle->pTIMx->CCMR2;
		temp_CCER = pTIMHandle->pTIMx->CCER;
		// Configurar entrada en registro CCMR2
		temp_CCMRx &= ~(0x03 << TIM_CCMR2_CC3S);
		temp_CCMRx |= (pTIMHandle->TIM_InputCapture.TIM_ICSelection << TIM_CCMR2_CC3S);

		// Configurar filtro en registro CCMR2
		temp_CCMRx &= ~(0x0F << TIM_CCMR2_IC3F);
		temp_CCMRx |= (pTIMHandle->TIM_InputCapture.TIM_ICFilter << TIM_CCMR2_IC3F);

		// Input Capture Prescaler
		temp_CCMRx &= ~(0x03 << TIM_CCMR2_IC3PSC);
		temp_CCMRx |= (pTIMHandle->TIM_InputCapture.TIM_ICPrescaler << TIM_CCMR2_IC3PSC);

		// Configurar polaridad en registro CCER
		temp_CCER &= ~((1 << TIM_CCER_CC3P) | (1 << TIM_CCER_CC3NP));
		if(pTIMHandle->TIM_InputCapture.TIM_ICPolarity == TIM_ICPolarity_RE){
			// CC3NP = 0 y CC3P = 0
			// Ya lo estan, nada que hacer
		}else if(pTIMHandle->TIM_InputCapture.TIM_ICPolarity == TIM_ICPolarity_FE){
			// CC3NP = 0 y CC3P = 1
			temp_CCER |= (1 << TIM_CCER_CC3P);
		}else if(pTIMHandle->TIM_InputCapture.TIM_ICPolarity == TIM_ICPolarity_RFE){
			// CC3NP = 1 y CC3P = 1
			temp_CCER |= (1 << TIM_CCER_CC3NP);
			temp_CCER |= (1 << TIM_CCER_CC3P);
		}
		// Habilitar el canal
		temp_CCER |= (1 << TIM_CCER_CC3E);

		// Asigno valores a registros
		pTIMHandle->pTIMx->CCMR2 = temp_CCMRx;
		pTIMHandle->pTIMx->CCER = temp_CCER;


	}else if(pTIMHandle->TIM_InputCapture.TIM_Channel == TIM_CH4){

		ASSERT_TRUE(TIM_HAS_CH4(pTIMHandle->pTIMx));

		// Reset del bit CC4E para deshabilitar el canal
		pTIMHandle->pTIMx->CCER &= ~(1 << TIM_CCER_CC4E);

		temp_CCMRx = pTIMHandle->pTIMx->CCMR2;
		temp_CCER = pTIMHandle->pTIMx->CCER;
		// Configurar entrada en registro CCMR2
		temp_CCMRx &= ~(0x03 << TIM_CCMR2_CC4S);
		temp_CCMRx |= (pTIMHandle->TIM_InputCapture.TIM_ICSelection << TIM_CCMR2_CC4S);

		// Configurar filtro en registro CCMR2
		temp_CCMRx &= ~(0x0F << TIM_CCMR2_IC4F);
		temp_CCMRx |= (pTIMHandle->TIM_InputCapture.TIM_ICFilter << TIM_CCMR2_IC4F);

		// Input Capture Prescaler
		temp_CCMRx &= ~(0x03 << TIM_CCMR2_IC4PSC);
		temp_CCMRx |= (pTIMHandle->TIM_InputCapture.TIM_ICPrescaler << TIM_CCMR2_IC4PSC);

		// Configurar polaridad en registro CCER
		temp_CCER &= ~((1 << TIM_CCER_CC4P) | (1 << TIM_CCER_CC4NP));
		if(pTIMHandle->TIM_InputCapture.TIM_ICPolarity == TIM_ICPolarity_RE){
			// CC4NP = 0 y CC4P = 0
			// Ya lo estan, nada que hacer
		}else if(pTIMHandle->TIM_InputCapture.TIM_ICPolarity == TIM_ICPolarity_FE){
			// CC4NP = 0 y CC4P = 1
			temp_CCER |= (1 << TIM_CCER_CC4P);
		}else if(pTIMHandle->TIM_InputCapture.TIM_ICPolarity == TIM_ICPolarity_RFE){
			// CC4NP = 1 y CC4P = 1
			temp_CCER |= (1 << TIM_CCER_CC4NP);
			temp_CCER |= (1 << TIM_CCER_CC4P);
		}
		// Habilitar el canal
		temp_CCER |= (1 << TIM_CCER_CC4E);

		// Asigno valores a registros
		pTIMHandle->pTIMx->CCMR2 = temp_CCMRx;
		pTIMHandle->pTIMx->CCER = temp_CCER;
	}

}

void TIM_OCInit(TIM_handle_t *pTIMHandle)
{
	uint16_t temp_CCMRx = 0, temp_CCER = 0;

	ASSERT_FALSE(TIM_IS_BASIC_TIMER(pTIMHandle->pTIMx));

	// Habilitar clock
	TIM_ClkCtrl(pTIMHandle->pTIMx, ENABLE);

	if(pTIMHandle->TIM_OutputCompare.TIM_Channel == TIM_CH1){
		// Reset del bit CC1E para deshabilitar el canal
		pTIMHandle->pTIMx->CCER &= ~(1 << TIM_CCER_CC1E);

		temp_CCMRx = pTIMHandle->pTIMx->CCMR1;
		temp_CCER = pTIMHandle->pTIMx->CCER;

		// Configurar como salida en registro CCMR1
		temp_CCMRx &= ~(0x03 << TIM_CCMR1_CC1S);

		// Configurar el modo en registro CCMR
		temp_CCMRx &= ~(0x07 << TIM_CCMR1_OC1M);
		temp_CCMRx |= (pTIMHandle->TIM_OutputCompare.TIM_OCMode << TIM_CCMR1_OC1M);

		// Configurar polaridad en registro CCER
		temp_CCER &= ~(1 < TIM_CCER_CC1P);
		temp_CCER |= (pTIMHandle->TIM_OutputCompare.TIM_OCPolarity << TIM_CCER_CC1P);

		// Habilito el canal
		temp_CCER |= (1 << TIM_CCER_CC1E);

		// Actualizar registro CCMR1
		pTIMHandle->pTIMx->CCMR1 = temp_CCMRx;

		// Configurar CCR1 con el valor de pulso
		pTIMHandle->pTIMx->CCR1 = pTIMHandle->TIM_OutputCompare.TIM_Pulse;

		// Actualizar registro CCER
		pTIMHandle->pTIMx->CCER = temp_CCER;

	}else if(pTIMHandle->TIM_OutputCompare.TIM_Channel == TIM_CH2){
		ASSERT_TRUE(TIM_HAS_CH2(pTIMHandle->pTIMx));

		// Reset del bit CC2E para deshabilitar el canal
		pTIMHandle->pTIMx->CCER &= ~(1 << TIM_CCER_CC2E);

		temp_CCMRx = pTIMHandle->pTIMx->CCMR1;
		temp_CCER = pTIMHandle->pTIMx->CCER;

		// Configurar como salida en registro CCMR1
		temp_CCMRx &= ~(0x03 << TIM_CCMR1_CC2S);

		// Configurar el modo en registro CCMR
		temp_CCMRx &= ~(0x07 << TIM_CCMR1_OC2M);
		temp_CCMRx |= (pTIMHandle->TIM_OutputCompare.TIM_OCMode << TIM_CCMR1_OC2M);

		// Configurar polaridad en registro CCER
		temp_CCER &= ~(1 << TIM_CCER_CC2P);
		temp_CCER |= (pTIMHandle->TIM_OutputCompare.TIM_OCPolarity << TIM_CCER_CC2P);

		// Habilitar el canal
		temp_CCER |= (1 << TIM_CCER_CC2E);

		// Actualizar registro CCMR1
		pTIMHandle->pTIMx->CCMR1 = temp_CCMRx;
		// Configurar CCR2 con el valor de pulso
		pTIMHandle->pTIMx->CCR2 = pTIMHandle->TIM_OutputCompare.TIM_Pulse;
		// Actualizo registro CCER
		pTIMHandle->pTIMx->CCER = temp_CCER;

	}else if(pTIMHandle->TIM_OutputCompare.TIM_Channel == TIM_CH3){
		ASSERT_TRUE(TIM_HAS_CH3(pTIMHandle->pTIMx));

		// Reset del bit CC3E para deshabilitar el canal
		pTIMHandle->pTIMx->CCER &= ~(1 << TIM_CCER_CC3E);

		temp_CCMRx = pTIMHandle->pTIMx->CCMR2;
		temp_CCER = pTIMHandle->pTIMx->CCER;

		// Configurar como salida en registro CCMR2
		temp_CCMRx &= ~(0x03 << TIM_CCMR2_CC3S);

		// Configurar el modo en registro CCMR
		temp_CCMRx &= ~(0x07 << TIM_CCMR2_OC3M);
		temp_CCMRx |= (pTIMHandle->TIM_OutputCompare.TIM_OCMode << TIM_CCMR2_OC3M);

		// Configurar polaridad en registro CCER
		temp_CCER &= ~(1 << TIM_CCER_CC3P);
		temp_CCER |= (pTIMHandle->TIM_OutputCompare.TIM_OCPolarity << TIM_CCER_CC3P);

		// Habilitar el canal
		temp_CCER |= (1 << TIM_CCER_CC3E);

		// Actualizar registro CCMR2
		pTIMHandle->pTIMx->CCMR2 = temp_CCMRx;

		// Configurar CCR3 con el valor de pulso
		pTIMHandle->pTIMx->CCR3 = pTIMHandle->TIM_OutputCompare.TIM_Pulse;

		// Actualizar registro CCER
		pTIMHandle->pTIMx->CCER = temp_CCER;

	}else if(pTIMHandle->TIM_OutputCompare.TIM_Channel == TIM_CH4){
		ASSERT_TRUE(TIM_HAS_CH4(pTIMHandle->pTIMx));

		// Reset del bit CC4E para deshabilitar el canal
		pTIMHandle->pTIMx->CCER &= ~(1 << TIM_CCER_CC4E);

		temp_CCMRx = pTIMHandle->pTIMx->CCMR2;
		temp_CCER = pTIMHandle->pTIMx->CCER;

		// Configurar como salida en registro CCMR2
		temp_CCMRx &= ~(0x03 << TIM_CCMR2_CC4S);

		// Configurar el modo en registro CCMR2
		temp_CCMRx &= ~(0x07 << TIM_CCMR2_OC4M);
		temp_CCMRx |= (pTIMHandle->TIM_OutputCompare.TIM_OCMode << TIM_CCMR2_OC4M);

		// Configurar polaridad en registro CCER
		temp_CCER &= ~(1 << TIM_CCER_CC4P);
		temp_CCER |= (pTIMHandle->TIM_OutputCompare.TIM_OCPolarity << TIM_CCER_CC4P);

		// Habilitar el canal
		temp_CCER |= (1 << TIM_CCER_CC4E);

		// Actualizar registro CCMR2
		pTIMHandle->pTIMx->CCMR2 = temp_CCMRx;

		// Configurar CCR3 con el valor de pulso
		pTIMHandle->pTIMx->CCR4 = pTIMHandle->TIM_OutputCompare.TIM_Pulse;

		// Actualizar registro CCER
		pTIMHandle->pTIMx->CCER = temp_CCER;
	}
}

uint32_t TIM_GetCounter(TIM_RegDef_t *pTIMx)
{
	return pTIMx->CNT;
}

void TIM_SetCounter(TIM_RegDef_t *pTIMx, uint32_t counter)
{
	pTIMx->CNT = counter;
}

uint32_t TIM_GetCapture(TIM_RegDef_t *pTIMx, TIM_Channels_t TIM_Channel)
{
	ASSERT_FALSE(TIM_IS_BASIC_TIMER(pTIMx));

	if(TIM_Channel == TIM_CH1){
		return pTIMx->CCR1;
	}else if(TIM_Channel == TIM_CH2){
		ASSERT_TRUE(TIM_HAS_CH2(pTIMx));
		return pTIMx->CCR2;
	}else if(TIM_Channel == TIM_CH3){
		ASSERT_TRUE(TIM_HAS_CH3(pTIMx));
		return pTIMx->CCR3;
	}

	ASSERT_TRUE(TIM_HAS_CH4(pTIMx));
	return pTIMx->CCR4;
}

void TIM_SetCompare(TIM_RegDef_t *pTIMx, TIM_Channels_t TIM_Channel, uint32_t value)
{
	ASSERT_FALSE(TIM_IS_BASIC_TIMER(pTIMx));

	if(TIM_Channel == TIM_CH1){
		pTIMx->CCR1 = value;
	}else if(TIM_Channel == TIM_CH2){
		ASSERT_TRUE(TIM_HAS_CH2(pTIMx));
		pTIMx->CCR2 = value;
	}else if(TIM_Channel == TIM_CH3){
		ASSERT_TRUE(TIM_HAS_CH3(pTIMx));
		pTIMx->CCR3 = value;
	}else if(TIM_Channel == TIM_CH4){
		ASSERT_TRUE(TIM_HAS_CH4(pTIMx));
		pTIMx->CCR4 = value;
	}
}

/**
  * @brief  Configura el trigger del timer esclavo.
  * @note   Esta configuración solo se debe hacer si el modo esclavo está deshabilitado (SMS=000)
  * 		para evitar detecciones incorrectas durante la transición.
  * @param  pTIMx: puntero al timer
  * @param  trigger: tipo de trigger a utilizar
  *            @arg 	TIM_Trigger_Internal_0
  *            @arg 	TIM_Trigger_Internal_1
  *            @arg 	TIM_Trigger_Internal_2
  *            @arg 	TIM_Trigger_Internal_3
  *            @arg 	TIM_Trigger_Edge_Detector_TI1
  *            @arg 	TIM_Trigger_Filtered_Timer_Input_1
  *            @arg 	TIM_Trigger_Filtered_Timer_Input_2
  *            @arg 	TIM_Trigger_External
  * @retval None
  */
void TIM_InputTrigger(TIM_RegDef_t *pTIMx, TIM_Trigger_t trigger)
{
	uint16_t temp_SMCR;

	ASSERT_TRUE(TIM_HAS_MS_FUNCTIONALITY(pTIMx));

	temp_SMCR = pTIMx->SMCR;

	temp_SMCR &= ~(0x07 << TIM_SMCR_TS);
	temp_SMCR |= (trigger << TIM_SMCR_TS);

	pTIMx->SMCR = temp_SMCR;

}

void TIM_SlaveMode(TIM_RegDef_t *pTIMx, TIM_Slave_t mode)
{
	uint16_t temp_SMCR;

	ASSERT_TRUE(TIM_HAS_MS_FUNCTIONALITY(pTIMx));

	temp_SMCR = pTIMx->SMCR;

	temp_SMCR &= ~(0x07 << TIM_SMCR_SMS);
	temp_SMCR |= (mode << TIM_SMCR_SMS);

	pTIMx->SMCR = temp_SMCR;

}

void TIM_MasterTriggerOutput(TIM_RegDef_t *pTIMx, TIM_MasterOutput_t output)
{
	uint16_t temp_CR2;

	ASSERT_TRUE(TIM_HAS_MS_FUNCTIONALITY(pTIMx));

	temp_CR2 = pTIMx->CR2;

	temp_CR2 &= ~(0x07 << TIM_CR2_MMS);
	temp_CR2 |= (output << TIM_CR2_MMS);

	pTIMx->CR2 = temp_CR2;
}

void TIM_Cmd(TIM_RegDef_t *pTIMx, uint8_t status)
{
	if(status == ENABLE)
		pTIMx->CR1 |= (1 << TIM_CR1_CEN);
	else if(status == DISABLE)
		pTIMx->CR1 &= ~(1 << TIM_CR1_CEN);
}

void TIM_ITConfig(TIM_RegDef_t *pTIMx, uint16_t IT_type, uint8_t status)
{
	if(status == ENABLE){
		pTIMx->DIER |= IT_type;
	}else{
		pTIMx->DIER &= ~IT_type;
	}
}

void TIM_IRQHandler(TIM_handle_t *pTIMHandle)
{
	if(TIM_GetITStatus(pTIMHandle->pTIMx, TIM_IT_UI)){
		TIM_ClearITPendingBit(pTIMHandle->pTIMx, TIM_IT_UI);
		TIM_EventCallback(pTIMHandle, TIM_EVENT_UI);
	}

	if(TIM_GetITStatus(pTIMHandle->pTIMx, TIM_IT_CC1I)){
		TIM_ClearITPendingBit(pTIMHandle->pTIMx, TIM_IT_CC1I);
		TIM_EventCallback(pTIMHandle, TIM_EVENT_CC1I);
	}

	if(TIM_GetITStatus(pTIMHandle->pTIMx, TIM_IT_CC2I)){
		TIM_ClearITPendingBit(pTIMHandle->pTIMx, TIM_IT_CC2I);
		TIM_EventCallback(pTIMHandle, TIM_EVENT_CC2I);
	}

	if(TIM_GetITStatus(pTIMHandle->pTIMx, TIM_IT_CC3I)){
		TIM_ClearITPendingBit(pTIMHandle->pTIMx, TIM_IT_CC3I);
		TIM_EventCallback(pTIMHandle, TIM_EVENT_CC3I);
	}

	if(TIM_GetITStatus(pTIMHandle->pTIMx, TIM_IT_CC4I)){
		TIM_ClearITPendingBit(pTIMHandle->pTIMx, TIM_IT_CC4I);
		TIM_EventCallback(pTIMHandle, TIM_EVENT_CC4I);
	}

}

__attribute__((weak)) void TIM_EventCallback(TIM_handle_t *pTIMHandle, TIM_Event_t event)
{

}
