
#ifndef INC_STM32F446XX_IWDG_H_
#define INC_STM32F446XX_IWDG_H_


#include "stm32f446xx.h"

#define IWDG_ENABLE_KEY				((uint16_t)0xCCCC)
#define IWDG_DISABLE_KEY			((uint16_t)0x0000)
#define IWDG_WRITEACCESS_KEY		((uint16_t)0x5555)
#define IWDG_RELOAD_KEY				((uint16_t)0xAAAA)

/*
 * @IWDG_Prescaler
 */
typedef enum{
	IWDG_Prescaler_4,
	IWDG_Prescaler_8,
	IWDG_Prescaler_16,
	IWDG_Prescaler_32,
	IWDG_Prescaler_64,
	IWDG_Prescaler_128,
	IWDG_Prescaler_256
}IWDG_Prescaler_t;

/*
 * @IWDG_StatusFlag
 */
typedef enum{
	IWDG_StatusFlag_PVU,
	IWDG_StatusFlag_RVU
}IWDG_StatusFlag_t;


typedef struct{
	IWDG_Prescaler_t IWDG_Prescaler;
	uint32_t IWDG_Period;
}IWDG_Config_t;

void IWDG_Init(IWDG_Config_t *IWDG_Config);
void IWDG_cmd(uint8_t status);
void IWDG_WriteAccess(uint8_t status);
void IWDG_SetPrescaler(IWDG_Prescaler_t prescaler);
void IWDG_SetPeriod(uint32_t period);
uint8_t IWDG_GetFlag(IWDG_StatusFlag_t flag);
void IWDG_Refresh(void);


#endif /* INC_STM32F446XX_IWDG_H_ */
