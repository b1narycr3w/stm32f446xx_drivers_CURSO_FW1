

#include <stm32f446xx.h>
#include "stm32f446xx_gpio.h"


GPIO_handle_t LED;
GPIO_handle_t Button;

void delay(uint32_t cnt)
{
	while(cnt)
		cnt--;
}

void GPIO_setup(void)
{
	LED.pGPIOx = GPIOA;
	LED.GPIO_config.GPIO_Mode = GPIO_Mode_OUT;
	LED.GPIO_config.GPIO_OType = GPIO_OType_PP;
	LED.GPIO_config.GPIO_Pin = GPIO_PIN_5;
	LED.GPIO_config.GPIO_PuPd = GPIO_PuPd_NONE;
	LED.GPIO_config.GPIO_Speed = GPIO_Speed_LOW;

	GPIO_Init(&LED);

	Button.pGPIOx = GPIOC;
	Button.GPIO_config.GPIO_Mode = GPIO_Mode_IN;
	Button.GPIO_config.GPIO_Pin = GPIO_PIN_13;
	Button.GPIO_config.GPIO_PuPd = GPIO_PuPd_NONE;
	Button.GPIO_config.GPIO_Speed = GPIO_Speed_LOW;

	GPIO_Init(&Button);
}

int main(void)
{
	GPIO_setup();

	while(1){
		if(!GPIO_ReadPin(Button.pGPIOx, GPIO_PIN_13)){
			GPIO_TogglePin(LED.pGPIOx, GPIO_PIN_5);
			delay(70000);
		}else
			GPIO_WritePin(LED.pGPIOx, GPIO_PIN_5, RESET);
	}
}

