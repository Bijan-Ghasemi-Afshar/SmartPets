#include <stdio.h>
#include "GLCD_Config.h"
#include "Board_GLCD.h"
#include "Board_Touch.h"
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_gpio.h"
#include "GUI_Utility.h"
#include "App_GUI_Content.h"
#include <string.h>

#define wait_delay HAL_Delay
extern GLCD_FONT GLCD_Font_6x8;
extern GLCD_FONT GLCD_Font_16x24;


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
* Initialize Pin
*/
void initializePins(void)
{
	int i = 0;
	
	GPIO_InitTypeDef gpio[8];	
	gpio[0].Pin = GPIO_PIN_7;
	gpio[1].Pin = GPIO_PIN_6;
	gpio[2].Pin = GPIO_PIN_6;
	gpio[3].Pin = GPIO_PIN_4;
	gpio[4].Pin = GPIO_PIN_7;
	gpio[5].Pin = GPIO_PIN_0;
	gpio[6].Pin = GPIO_PIN_6;
	gpio[7].Pin = GPIO_PIN_3;
	
	// enable clock for B base
	// two "_" infront of HAL
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOI_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
		
	
	for (i = 0; i < 8; i++)
	{

			// set mode as output, nopull D0
			gpio[i].Mode 		= GPIO_MODE_OUTPUT_PP;
			gpio[i].Pull 		= GPIO_NOPULL;
			gpio[i].Speed 	= GPIO_SPEED_HIGH;			
			
			if(i == 0 || i == 1)
			{
				
				// initialise the pin
				HAL_GPIO_Init(GPIOC, &gpio[i]);
		
				// enable the segment
				HAL_GPIO_WritePin(GPIOC, gpio[i].Pin, GPIO_PIN_RESET);
				
			} else if (i == 2 || i == 4)
			{
				
				// initialise the pin
				HAL_GPIO_Init(GPIOG, &gpio[i]);
		
				// enable the segment
				HAL_GPIO_WritePin(GPIOG, gpio[i].Pin, GPIO_PIN_RESET);
				
			} else if (i == 5 || i == 7)
			{
				
				// initialise the pin
				HAL_GPIO_Init(GPIOI, &gpio[i]);
		
				// enable the segment
				HAL_GPIO_WritePin(GPIOI, gpio[i].Pin, GPIO_PIN_RESET);
				
			} else if (i == 3)
			{
				// initialise the pin
				HAL_GPIO_Init(GPIOB, &gpio[i]);
		
				// enable the segment
				HAL_GPIO_WritePin(GPIOB, gpio[i].Pin, GPIO_PIN_RESET);
				
			} else
			{
				// initialise the pin
				HAL_GPIO_Init(GPIOH, &gpio[i]);
		
				// enable the segment
				HAL_GPIO_WritePin(GPIOH, gpio[i].Pin, GPIO_PIN_RESET);
			}
	}
}


/**
* Main Function
*/
int main(void)
{
	unsigned int count;
	GPIO_InitTypeDef gpio;
	char *page = "Home";

	HAL_Init (); /* Init Hardware Abstraction Layer */
	SystemClock_Config (); /* Config Clocks */
	
	initializePins();
	GLCD_Initialize();
	Touch_Initialize();
	
	// SUPER LOOP
	while(1)
	{
		if (strcmp(page,"Home") == 0)
		{
			GLCD_SetBackgroundColor (GLCD_COLOR_LIGHT_GREY);
			GLCD_ClearScreen ();
			drawHomePage();
			wait(50000000);
			homePageNavigation(&page);
		} else if (strcmp(page,"Manual") == 0){
			GLCD_SetBackgroundColor (GLCD_COLOR_LIGHT_GREY);
			GLCD_ClearScreen ();
			drawManualPage();
			wait(50000000);
			manualPageNavigation(&page);
		}
	}
}