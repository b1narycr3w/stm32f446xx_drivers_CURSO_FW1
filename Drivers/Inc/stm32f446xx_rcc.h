
#ifndef INC_STM32F446XX_RCC_H_
#define INC_STM32F446XX_RCC_H_

#include "stm32f446xx.h"

#define IS_VALID_PLLM_VALUE(x)	(((x) < 64)&&((x) > 1))
#define IS_VALID_PLLN_VALUE(x)	(((x) < 433) && ((x) > 50))
#define IS_VALID_PLLP_VALUE(x)	(((x) == 2) || ((x) == 4) || ((x) == 6) || ((x) == 8))
#define IS_VALID_PLLQ_VALUE(x)	(((x) < 16) && ((x) > 1))
#define IS_VALID_PLLR_VALUE(x)	(((x) < 8) && ((x) > 1))

/*
 * @RCC_HSE_Status
 */
typedef enum{
	RCC_HSE_OFF,
	RCC_HSE_ON,
	RCC_HSE_BYP,
}RCC_HSE_Status_t;

/*
 * @RCC_LSE_Status
 */
typedef enum{
	RCC_LSE_OFF,
	RCC_LSE_ON,
	RCC_LSE_BYP,
}RCC_LSE_Status_t;

/*
 * @RCC_PLL_Source
 */
typedef enum{
	RCC_PLL_Source_HSI,
	RCC_PLL_Source_HSE
}RCC_PLL_Source_t;

/*
 * @RCC_MCO1_Source
 */
typedef enum{
	RCC_MCO1_Source_HSI,
	RCC_MCO1_Source_LSE,
	RCC_MCO1_Source_HSE,
	RCC_MCO1_Source_PLL,
}RCC_MCO1_Source_t;

/*
 * @RCC_MCO1_Prescaler
 */
typedef enum{
	RCC_MCO1_Prescaler_None,
	RCC_MCO1_Prescaler_2 = 4,
	RCC_MCO1_Prescaler_3 = 5,
	RCC_MCO1_Prescaler_4 = 6,
	RCC_MCO1_Prescaler_5 = 7
}RCC_MCO1_Prescaler_t;

/*
 * @RCC_Clock
 */
typedef enum{
	RCC_Clock_HSI,
	RCC_Clock_HSE,
	RCC_Clock_PLL,
	RCC_Clock_LSE
}RCC_Clock_t;

/*
 * @RCC_SYSCLK_Source
 */
typedef enum{
	RCC_SYSCLK_Source_HSI,
	RCC_SYSCLK_Source_HSE,
	RCC_SYSCLK_Source_PLL_P,
	RCC_SYSCLK_Source_PLL_R,
}RCC_SYSCLK_Source_t;

/*
 * @RCC_AHB_Prescaler
 */
typedef enum{
	RCC_AHB_Prescaler_None = 0,
	RCC_AHB_Prescaler_2 = 8,
	RCC_AHB_Prescaler_4 = 9,
	RCC_AHB_Prescaler_8 = 10,
	RCC_AHB_Prescaler_16 = 11,
	RCC_AHB_Prescaler_64 = 12,
	RCC_AHB_Prescaler_128 = 13,
	RCC_AHB_Prescaler_256 = 14,
	RCC_AHB_Prescaler_512 = 15
}RCC_AHB_Prescaler_t;

/*
 * @RCC_APB_Prescaler
 */
typedef enum{
	RCC_APB_Prescaler_None = 0,
	RCC_APB_Prescaler_2 = 4,
	RCC_APB_Prescaler_4 = 5,
	RCC_APB_Prescaler_8 = 6,
	RCC_APB_Prescaler_16 = 7
}RCC_APB_Prescaler_t;

/* Configuración external clocks (On, off o bypass) */
void RCC_HSEConfig(RCC_HSE_Status_t HSE_Status);
void RCC_LSEConfig(RCC_LSE_Status_t LSE_Status);

/* Configuración PLL */
void RCC_PLLConfig(RCC_PLL_Source_t PLL_Source, uint32_t PLLM, uint32_t PLLN, uint32_t PLLP, uint32_t PLLQ, uint32_t PLLR);

/* Habilitación/Deshabilitación internal clocks y PLL */
void RCC_HSICmd(uint8_t status);
void RCC_LSICmd(uint8_t status);
void RCC_PLLCmd(uint8_t status);
//
///* Configuración salidas MCO1 y MCO2 */
void RCC_MCO1Config(RCC_MCO1_Source_t MCO1_Source, RCC_MCO1_Prescaler_t MCO1_Prescaler);
//void RCC_MCO2Config(uint32_t RCC_MCO2Source, uint32_t RCC_MCO2Div); //<-- se deja como ejercicio al alumno

/* Rutina para esperar a que un determinado clock esté OK */
void RCC_WaitForCLKRDY(RCC_Clock_t clk);

/* Configurar la fuente de clock del sistema */
void RCC_SYSCLKConfig(RCC_SYSCLK_Source_t SYSCLK_Source);

/* Obtener la fuente de clock del sistema */
RCC_SYSCLK_Source_t RCC_GetSYSCLKSource(void);

///* Configurar prescalers de AHB, APB1 y APB2 */
void RCC_AHBCLKConfig(RCC_AHB_Prescaler_t AHB_Prescaler);
void RCC_APB1CLKConfig(RCC_APB_Prescaler_t APB1_Prescaler);
void RCC_APB2CLKConfig(RCC_APB_Prescaler_t APB2_Prescaler);

/* Obtener frecuencia de clock del sistema y de los buses */
uint32_t RCC_GetSYSCLK(void);
uint32_t RCC_GetAHBCLK(void);
uint32_t RCC_GetAPB1CLK(void);
uint32_t RCC_GetAPB2CLK(void);
uint32_t RCC_GetAPB1_TimerCLK(void);
uint32_t RCC_GetAPB2_TimerCLK(void);


#endif /* INC_STM32F446XX_RCC_H_ */
