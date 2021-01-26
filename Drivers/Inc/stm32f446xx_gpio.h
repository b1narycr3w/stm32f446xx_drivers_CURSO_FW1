
#ifndef DRIVERS_INC_STM32F446XX_GPIO_H_
#define DRIVERS_INC_STM32F446XX_GPIO_H_

#include "stm32f446xx.h"

/*
 * @GPIO_PIN_NUMBERS
 */
typedef enum {
	GPIO_PIN_0,
	GPIO_PIN_1,
	GPIO_PIN_2,
	GPIO_PIN_3,
	GPIO_PIN_4,
	GPIO_PIN_5,
	GPIO_PIN_6,
	GPIO_PIN_7,
	GPIO_PIN_8,
	GPIO_PIN_9,
	GPIO_PIN_10,
	GPIO_PIN_11,
	GPIO_PIN_12,
	GPIO_PIN_13,
	GPIO_PIN_14,
	GPIO_PIN_15
}GPIO_Pin_t;

typedef enum{
	GPIO_Mode_IN,
	GPIO_Mode_OUT,
	GPIO_Mode_AF,
	GPIO_Mode_AN,
	GPIO_Mode_IT_RE,
	GPIO_Mode_IT_FE,
	GPIO_Mode_IT_RFE
}GPIO_Mode_t;

/*
 * @GPIO_SPEEDS
 */
typedef enum{
	GPIO_Speed_LOW,
	GPIO_Speed_MED,
	GPIO_Speed_FAST,
	GPIO_Speed_HIGH
}GPIO_Speed_t;

/*
 * @GPIO_PUPD
 */
typedef enum{
	GPIO_PuPd_NONE,
	GPIO_PuPd_UP,
	GPIO_PuPd_DOWN
}GPIO_PuPd_t;

/*
 * @GPIO_OTYPES
 */
typedef enum{
	GPIO_OType_PP, /* Push-Pull */
	GPIO_OType_OD  /* Open drain */
}GPIO_OType_t;

/*
 * @GPIO_ALT_FUNC
 */
typedef enum {
	GPIO_ALTFUN_0,
	GPIO_ALTFUN_1,
	GPIO_ALTFUN_2,
	GPIO_ALTFUN_3,
	GPIO_ALTFUN_4,
	GPIO_ALTFUN_5,
	GPIO_ALTFUN_6,
	GPIO_ALTFUN_7,
	GPIO_ALTFUN_8,
	GPIO_ALTFUN_9,
	GPIO_ALTFUN_10,
	GPIO_ALTFUN_11,
	GPIO_ALTFUN_12,
	GPIO_ALTFUN_13,
	GPIO_ALTFUN_14,
	GPIO_ALTFUN_15
}GPIO_AltFun_t;

typedef struct{
	GPIO_Pin_t	GPIO_Pin;			/* Numero de pin. Posibles valores: @GPIO_PIN_NUMBERS */
	GPIO_Mode_t	GPIO_Mode;			/* Mode de funcionamiento. Posibles valores: @GPIO_MODES */
	GPIO_Speed_t GPIO_Speed;		/* Velocidad. Posibles valores: @GPIO_SPEEDS */
	GPIO_PuPd_t GPIO_PuPd;			/* Pull-up, pull-down. Posibles valores: @GPIO_PUPD */
	GPIO_OType_t GPIO_OType;		/* Tipo de salida. Posibles valores: @GPIO_OTYPES */
	GPIO_AltFun_t GPIO_AltFun;		/* Función alternativa. Posibles valores: @GPIO_ALT_FUNC */
}GPIO_Config_t;

typedef struct{
	GPIO_RegDef_t *pGPIOx;
	GPIO_Config_t GPIO_config;
}GPIO_handle_t;


/* Funciones */

void GPIO_ClkCtrl(GPIO_RegDef_t *pGPIOx, uint8_t status);
void GPIO_Init(GPIO_handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);

uint8_t GPIO_ReadPin(GPIO_RegDef_t *pGPIOx, GPIO_Pin_t pin);
uint16_t GPIO_ReadPort(GPIO_RegDef_t *pGPIOx);
void GPIO_WritePin(GPIO_RegDef_t *pGPIOx, GPIO_Pin_t pin, uint8_t value);
void GPIO_WritePort(GPIO_RegDef_t *pGPIOx, uint16_t value);
void GPIO_TogglePin(GPIO_RegDef_t *pGPIOx, GPIO_Pin_t pin);

void GPIO_IRQHandler(uint8_t pin);

#endif /* DRIVERS_INC_STM32F446XX_GPIO_H_ */
