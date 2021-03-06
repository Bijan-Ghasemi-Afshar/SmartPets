/*-----------------------------------------------------------------------------
 * Name:    main.c
 * Purpose: The main function of the SmartPets program.
 * Rev.:    1.0.0
 * Authors:    Bijan Ghasemi Afshar - Richard Sabiers
 * Date: April 2019
 *-----------------------------------------------------------------------------*/
 
 
#include "GLCD_Config.h"
#include "Board_GLCD.h"
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_adc.h"
#include "cmsis_os.h"
#include <string.h>

/*---------------------- HAL Delay definition ---------------*/
#define wait_delay HAL_Delay

/*---------------------- Defining the used fonts ---------------*/
extern GLCD_FONT GLCD_Font_16x24;

/*---------------------- Function Definitions ---------------*/
static void SystemClock_Config(void);
static void initDisplay(void);

/**
  \fn          void SystemClock_Config(void)
  \brief       Function for configuring the system clock.
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
  \fn          int main(void)
  \brief       The main starting point of the application
	\returns
   - \b  0: function succeeded
   - \b  1: function failed
*/
int main(void)
{
	char *page = "Home";

	HAL_Init (); /* Init Hardware Abstraction Layer */
	SystemClock_Config (); /* Config Clocks */
	
	initializePins();
	GLCD_Initialize();
	Touch_Initialize();
	ConfigureADC();
	
	GLCD_SetFont (&GLCD_Font_16x24);
	GLCD_SetForegroundColor (GLCD_COLOR_WHITE);
	
	// SUPER LOOP
	while(1)
	{
		if (strcmp(page,"Home") == 0)
		{
			GLCD_SetBackgroundColor (GLCD_COLOR_LIGHT_GREY);
			GLCD_ClearScreen ();
			GLCD_SetBackgroundColor (GLCD_COLOR_PURPLE);
			drawHomePage(&page);
		} else if (strcmp(page,"Manual") == 0){
			GLCD_SetBackgroundColor (GLCD_COLOR_LIGHT_GREY);
			GLCD_ClearScreen ();
			GLCD_SetBackgroundColor (GLCD_COLOR_PURPLE);
			drawManualPage(&page);
		} else {
		}
	}
}