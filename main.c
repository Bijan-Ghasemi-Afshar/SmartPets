#include <stdio.h>
#include "GLCD_Config.h"
#include "Board_GLCD.h"
#include "Board_Touch.h"
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_gpio.h"
#include "GUI_Utility.h"
#include "App_GUI_Content.h"

#define wait_delay HAL_Delay
extern GLCD_FONT GLCD_Font_6x8;
extern GLCD_FONT GLCD_Font_16x24;

#ifdef __RTX
extern uint32_t os_time;
uint32_t HAL_GetTick(void) {
return os_time;
}
#endif

extern GLCD_FONT GLCD_Font_6x8;
static void SystemClock_Config(void);
static void Error_Handler(void);
static void CPU_CACHE_Enable(void);
static void initDisplay(void);

/**
* System Clock Configuration
*/
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct;
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	/* Enable Power Control clock */
	__HAL_RCC_PWR_CLK_ENABLE();
	/* The voltage scaling allows optimizing the power
	consumption when the device is clocked below the
	maximum system frequency (see datasheet). */
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
	/* Enable HSE Oscillator and activate PLL
	with HSE as source */
	RCC_OscInitStruct.OscillatorType =RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 25;
	RCC_OscInitStruct.PLL.PLLN = 336;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 7;
	HAL_RCC_OscConfig(&RCC_OscInitStruct);
	/* Select PLL as system clock source and configure
	the HCLK, PCLK1 and PCLK2 clocks dividers */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK |
	RCC_CLOCKTYPE_PCLK1 |
	RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource =
	RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
	HAL_RCC_ClockConfig(&RCC_ClkInitStruct,
	FLASH_LATENCY_5);
}

/**
* Initialize Display
*/
void initDisplay()
{
	
	GLCD_Initialize();
	GLCD_SetBackgroundColor (GLCD_COLOR_LIGHT_GREY);
	GLCD_ClearScreen ();
	GLCD_SetBackgroundColor (GLCD_COLOR_PURPLE);
	
	drawHomeScreen();
	
	
}


/**
* Main Function
*/
int main(void)
{
	unsigned int count;
	GPIO_InitTypeDef gpio;
	bool doorOpen = 1;
	TOUCH_STATE openDoorBtn;
	openDoorBtn.x = 20;
	openDoorBtn.y = 20;
	openDoorBtn.padding = 10;
	openDoorBtn.pressed = 0;

	HAL_Init (); /* Init Hardware Abstraction Layer */
	SystemClock_Config (); /* Config Clocks */
	
	initDisplay();
	Touch_Initialize();
	
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
	
	
	while(1){
		Touch_GetState(&openDoorBtn);
		if (openDoorBtn.pressed && !doorOpen) {
			GLCD_SetBackgroundColor (GLCD_COLOR_GREEN);
			GLCD_DrawBargraph(40,40,70,70,0);
			doorOpen = 1;
			HAL_GPIO_WritePin(GPIOC, gpio.Pin, GPIO_PIN_SET);
		} else if (openDoorBtn.pressed && doorOpen) {
			GLCD_SetBackgroundColor (GLCD_COLOR_RED);
			GLCD_DrawBargraph(40,40,70,70,0);
			doorOpen = 0;
			HAL_GPIO_WritePin(GPIOC, gpio.Pin, GPIO_PIN_RESET);
		} else {
			
		}
	}
	
}