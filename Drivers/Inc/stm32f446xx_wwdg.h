
#ifndef INC_STM32F446XX_WWDG_H_
#define INC_STM32F446XX_WWDG_H_

#include "stm32f446xx.h"

/*
 * @WWDG_Prescaler
 */
typedef enum{
	WWDG_Prescaler_4096,
	WWDG_Prescaler_4096x2,
	WWDG_Prescaler_4096x4,
	WWDG_Prescaler_4096x8
}WWDG_Prescaler_t;

typedef struct{
	WWDG_Prescaler_t WWDG_Prescaler;
	uint8_t WWDG_Counter;
	uint8_t WWDG_Window;
}WWDG_Config_t;

void WWDG_Init(WWDG_Config_t *WWDG_Config);
void WWDG_Deinit(void);
void WWDG_cmd(uint8_t status);
void WWDG_Refresh(WWDG_Config_t *WWDG_Config);
void WWDG_ITConfig(uint8_t status);
uint8_t WWDG_GetFlag(void);

#endif /* INC_STM32F446XX_WWDG_H_ */
