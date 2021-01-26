
#include "stm32f446xx_gpio.h"

void GPIO_ClkCtrl(GPIO_RegDef_t *pGPIOx, uint8_t status)
{
	if(status == ENABLE){
		if(pGPIOx == GPIOA)
			GPIOA_EN_CLK();
		else if(pGPIOx == GPIOB)
			GPIOB_EN_CLK();
		else if(pGPIOx == GPIOC)
			GPIOC_EN_CLK();
		else if(pGPIOx == GPIOD)
			GPIOD_EN_CLK();
		else if(pGPIOx == GPIOE)
			GPIOE_EN_CLK();
		else if(pGPIOx == GPIOF)
			GPIOF_EN_CLK();
		else if(pGPIOx == GPIOG)
			GPIOG_EN_CLK();
		else if(pGPIOx == GPIOH)
			GPIOH_EN_CLK();
	}else if(status == DISABLE){
		if(pGPIOx == GPIOA)
			GPIOA_DIS_CLK();
		else if(pGPIOx == GPIOB)
			GPIOB_DIS_CLK();
		else if(pGPIOx == GPIOC)
			GPIOC_DIS_CLK();
		else if(pGPIOx == GPIOD)
			GPIOD_DIS_CLK();
		else if(pGPIOx == GPIOE)
			GPIOE_DIS_CLK();
		else if(pGPIOx == GPIOF)
			GPIOF_DIS_CLK();
		else if(pGPIOx == GPIOG)
			GPIOG_DIS_CLK();
		else if(pGPIOx == GPIOH)
			GPIOH_DIS_CLK();
	}
}

void GPIO_Init(GPIO_handle_t *pGPIOHandle)
{
	// 1. Habilitar clock
	GPIO_ClkCtrl(pGPIOHandle->pGPIOx, ENABLE);

	// 2. Configurar modo (IN. OUT, AF ,AN,IT_RE, IT_FE, IT_RFE)
	if(pGPIOHandle->GPIO_config.GPIO_Mode > GPIO_Mode_AN){
		// Modo con interrupcion
		// Configurar flancos de disparo
		if(pGPIOHandle->GPIO_config.GPIO_Mode == GPIO_Mode_IT_FE){
			EXTI->FTSR |= (1 << pGPIOHandle->GPIO_config.GPIO_Pin);
			EXTI->RTSR &= ~(1 << pGPIOHandle->GPIO_config.GPIO_Pin);
		}else if(pGPIOHandle->GPIO_config.GPIO_Mode == GPIO_Mode_IT_RE){
			EXTI->RTSR |= (1 << pGPIOHandle->GPIO_config.GPIO_Pin);
			EXTI->FTSR &= ~(1 << pGPIOHandle->GPIO_config.GPIO_Pin);
		}else if(pGPIOHandle->GPIO_config.GPIO_Mode == GPIO_Mode_IT_RFE){
			EXTI->FTSR |= (1 << pGPIOHandle->GPIO_config.GPIO_Pin);
			EXTI->RTSR |= (1 << pGPIOHandle->GPIO_config.GPIO_Pin);
		}
		// Configurar SYSCFG
		SYSCFG_EN_CLK();
		uint8_t regidx;
		uint8_t blkidx;
		regidx = pGPIOHandle->GPIO_config.GPIO_Pin / 4;
		blkidx = pGPIOHandle->GPIO_config.GPIO_Pin % 4;
		SYSCFG->EXTICR[regidx] &= ~(0x0f << (blkidx * 4));
		SYSCFG->EXTICR[regidx] |= (PORT_NUMBER(pGPIOHandle->pGPIOx) << (blkidx * 4));

		// Habilitar la interrupcion EXTI
		EXTI->IMR |= (1 << pGPIOHandle->GPIO_config.GPIO_Pin);

	}else{
		// Modo sin interrupcion
		pGPIOHandle->pGPIOx->MODER &= ~(0x03 << (pGPIOHandle->GPIO_config.GPIO_Pin * 2));
		pGPIOHandle->pGPIOx->MODER |= (pGPIOHandle->GPIO_config.GPIO_Mode << (pGPIOHandle->GPIO_config.GPIO_Pin * 2));
	}
	// 3. COnfigurar speed
	pGPIOHandle->pGPIOx->OSPEEDR &= ~(0x03 << (pGPIOHandle->GPIO_config.GPIO_Pin * 2));
	pGPIOHandle->pGPIOx->OSPEEDR |= (pGPIOHandle->GPIO_config.GPIO_Speed << (pGPIOHandle->GPIO_config.GPIO_Pin * 2));

	// 4. Configurar pull-up/pull-down
	pGPIOHandle->pGPIOx->PUPDR &= ~(0x03 << (pGPIOHandle->GPIO_config.GPIO_Pin * 2));
	pGPIOHandle->pGPIOx->PUPDR |= (pGPIOHandle->GPIO_config.GPIO_PuPd << (pGPIOHandle->GPIO_config.GPIO_Pin * 2));

	// 5. Configurar tipo de salida (Push-Pull/Open drain)
	pGPIOHandle->pGPIOx->OTYPER &= ~(0x01 << pGPIOHandle->GPIO_config.GPIO_Pin);
	pGPIOHandle->pGPIOx->OTYPER |= (pGPIOHandle->GPIO_config.GPIO_OType << pGPIOHandle->GPIO_config.GPIO_Pin);

	// 6. Configurar funcion alternativa
	if(pGPIOHandle->GPIO_config.GPIO_Mode == GPIO_Mode_AF){
		uint8_t regidx;
		uint8_t blkidx;
		regidx = pGPIOHandle->GPIO_config.GPIO_Pin / 8;
		blkidx = pGPIOHandle->GPIO_config.GPIO_Pin % 8;
		pGPIOHandle->pGPIOx->AFR[regidx] &= ~(0x0f << (blkidx * 4));
		pGPIOHandle->pGPIOx->AFR[regidx] |= (pGPIOHandle->GPIO_config.GPIO_AltFun << (blkidx * 4));
	}
}

void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{
	if(pGPIOx == GPIOA)
		GPIOA_RESET();
	else if(pGPIOx == GPIOB)
		GPIOB_RESET();
	else if(pGPIOx == GPIOC)
		GPIOC_RESET();
	else if(pGPIOx == GPIOD)
		GPIOD_RESET();
	else if(pGPIOx == GPIOE)
		GPIOE_RESET();
	else if(pGPIOx == GPIOF)
		GPIOF_RESET();
	else if(pGPIOx == GPIOG)
		GPIOG_RESET();
	else if(pGPIOx == GPIOH)
		GPIOH_RESET();
}

uint8_t GPIO_ReadPin(GPIO_RegDef_t *pGPIOx, GPIO_Pin_t pin)
{
	return (uint8_t)((pGPIOx->IDR >> pin) & 0x01);
}

uint16_t GPIO_ReadPort(GPIO_RegDef_t *pGPIOx)
{
	return (uint16_t)(pGPIOx->IDR & 0xFFFF);
}

void GPIO_WritePin(GPIO_RegDef_t *pGPIOx, GPIO_Pin_t pin, uint8_t value)
{
	if(value == SET){
		pGPIOx->ODR |= (1 << pin);
	}else if(value == RESET){
		pGPIOx->ODR &= ~(1 << pin);
	}
}

void GPIO_WritePort(GPIO_RegDef_t *pGPIOx, uint16_t value)
{
	pGPIOx->ODR = (uint32_t)value;
}

void GPIO_TogglePin(GPIO_RegDef_t *pGPIOx, GPIO_Pin_t pin)
{
	pGPIOx->ODR ^= (1 << pin);
}


void GPIO_IRQHandler(uint8_t pin)
{
	if(EXTI->PR & (1 << pin))
		EXTI->PR |= (1 << pin);
}


