

#include <stm32f446xx.h>
#include "stm32f446xx_gpio.h"
#include "stm32f446xx_nvic.h"

GPIO_handle_t LED;
GPIO_handle_t Button;

uint8_t button_pressed_f;

void delay(uint32_t cnt)
{
	while(cnt)
		cnt--;
}

void EXTI15_10_IRQHandler(void)
{
	GPIO_IRQHandler(GPIO_PIN_13);

	button_pressed_f = 1;
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
	Button.GPIO_config.GPIO_Mode = GPIO_Mode_IT_FE;
	Button.GPIO_config.GPIO_Pin = GPIO_PIN_13;
	Button.GPIO_config.GPIO_PuPd = GPIO_PuPd_NONE;
	Button.GPIO_config.GPIO_Speed = GPIO_Speed_LOW;

	GPIO_Init(&Button);
}

int main(void)
{
	GPIO_setup();

	NVIC_IRQ_Enable(IRQ_EXTI15_10);

	while(1){
		if(button_pressed_f){
			button_pressed_f = 0;
			GPIO_TogglePin(LED.pGPIOx, GPIO_PIN_5);
			delay(70000);
		}else
			GPIO_WritePin(LED.pGPIOx, GPIO_PIN_5, RESET);
	}
}

