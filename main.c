#include <stdio.h>
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_gpio.h"

int main(void)
{
	GPIO_InitTypeDef gpio;
	
	// enable clock for B base
	__HAL_RCC_GPIOC_CLK_ENABLE();
	
	// set mode as output, nonpull
	gpio.Mode 	= GPIO_MODE_OUTPUT_PP;
	gpio.Pull 	= GPIO_NOPULL;
	gpio.Speed 	= GPIO_SPEED_HIGH;
	gpio.Pin 		= GPIO_PIN_7;
	
	// initialize the pin
	HAL_GPIO_Init(GPIOC, &gpio);
	
	// enable the segment
	HAL_GPIO_WritePin(GPIOC, gpio.Pin, GPIO_PIN_SET);
}