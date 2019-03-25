#include "GUI_Utility.h"
#include "Board_GLCD.h"
#include "GLCD_Config.h"
#include "App_GUI_Content.h"
#include "Board_Touch.h"
#include <string.h>
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_gpio.h"


extern GLCD_FONT GLCD_Font_16x24;


// ====================== CN4 GPIO PINS ======================
GPIO_InitTypeDef pinD0 = {GPIO_PIN_7, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_HIGH};
GPIO_InitTypeDef pinD1 = {GPIO_PIN_6, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_HIGH};
GPIO_InitTypeDef pinD2 = {GPIO_PIN_6, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_HIGH};
GPIO_InitTypeDef pinD3 = {GPIO_PIN_4, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_HIGH};
GPIO_InitTypeDef pinD4 = {GPIO_PIN_7, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_HIGH};
GPIO_InitTypeDef pinD5 = {GPIO_PIN_0, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_HIGH};
GPIO_InitTypeDef pinD6 = {GPIO_PIN_6, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_HIGH};
GPIO_InitTypeDef pinD7 = {GPIO_PIN_3, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_HIGH};
GPIO_InitTypeDef *CN4Pins[8] = {&pinD0, &pinD1, &pinD2, &pinD3, &pinD4, &pinD5, &pinD6, &pinD7};

// ====================== CN7 GPIO PINS ======================
GPIO_InitTypeDef pinD8 = {GPIO_PIN_2, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_HIGH};
GPIO_InitTypeDef pinD9 = {GPIO_PIN_15, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_HIGH};
GPIO_InitTypeDef pinD10 = {GPIO_PIN_8, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_HIGH};
GPIO_InitTypeDef pinD11 = {GPIO_PIN_15, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_HIGH};
GPIO_InitTypeDef pinD12 = {GPIO_PIN_14, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_HIGH};
GPIO_InitTypeDef pinD13 = {GPIO_PIN_1, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_HIGH};
GPIO_InitTypeDef pinD14 = {GPIO_PIN_9, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_HIGH};
GPIO_InitTypeDef pinD15 = {GPIO_PIN_8, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_HIGH};
GPIO_InitTypeDef *CN7Pins[8] = {&pinD8, &pinD9, &pinD10, &pinD11, &pinD12, &pinD13, &pinD14, &pinD15};

// ====================== CN5 GPIO PINS ======================
GPIO_InitTypeDef pinA0 = {GPIO_PIN_0, GPIO_MODE_ANALOG, GPIO_NOPULL, GPIO_SPEED_HIGH};
GPIO_InitTypeDef pinA1 = {GPIO_PIN_10, GPIO_MODE_ANALOG, GPIO_NOPULL, GPIO_SPEED_HIGH};
GPIO_InitTypeDef pinA2 = {GPIO_PIN_9, GPIO_MODE_ANALOG, GPIO_NOPULL, GPIO_SPEED_HIGH};
GPIO_InitTypeDef pinA3 = {GPIO_PIN_8, GPIO_MODE_ANALOG, GPIO_NOPULL, GPIO_SPEED_HIGH};
GPIO_InitTypeDef pinA4 = {GPIO_PIN_7, GPIO_MODE_ANALOG, GPIO_NOPULL, GPIO_SPEED_HIGH};
GPIO_InitTypeDef pinA5 = {GPIO_PIN_6, GPIO_MODE_ANALOG, GPIO_NOPULL, GPIO_SPEED_HIGH};
GPIO_InitTypeDef *CN5Pins[6] = {&pinA0, &pinA1, &pinA2, &pinA3, &pinA4, &pinA5};

// ====================== Screen Label ======================
ScreenLabel homeLabel = {20, 20, "Home"};
ScreenLabel manualLabel = {20, 20, "Manual"};

// ====================== Clock ======================
Clock clock = {CLOCK_POS_X, CLOCK_POS_Y, CLOCK_HOUR, CLOCK_MIN, CLOCK_SEC};

// ====================== Home Buttons ======================
Button dayButton = {BUTTON_DAY_POS_X, BUTTON_DAY_POS_Y, BUTTON_DAY_WIDTH, BUTTON_DAY_HEIGHT, BUTTON_DAY_BITMAP, BUTTON_DAY_BACKGROUND_COLOR, BUTTON_DAY_TEXT_COLOR, BUTTON_DAY_LABEL, BUTTON_DAY_NAVIGATION};
Button nightButton = {BUTTON_NIGHT_POS_X, BUTTON_NIGHT_POS_Y, BUTTON_NIGHT_WIDTH, BUTTON_NIGHT_HEIGHT, BUTTON_NIGHT_BITMAP, BUTTON_NIGHT_BACKGROUND_COLOR, BUTTON_NIGHT_TEXT_COLOR, BUTTON_NIGHT_LABEL, BUTTON_NIGHT_NAVIGATION};
Button playButton = {BUTTON_PLAY_POS_X, BUTTON_PLAY_POS_Y, BUTTON_PLAY_WIDTH, BUTTON_PLAY_HEIGHT, BUTTON_PLAY_BITMAP, BUTTON_PLAY_BACKGROUND_COLOR, BUTTON_PLAY_TEXT_COLOR, BUTTON_PLAY_LABEL, BUTTON_PLAY_NAVIGATION};
Button manButton = {BUTTON_MANUAL_POS_X, BUTTON_MANUAL_POS_Y, BUTTON_MANUAL_WIDTH, BUTTON_MANUAL_HEIGHT, BUTTON_MANUAL_BITMAP, BUTTON_MANUAL_BACKGROUND_COLOR, BUTTON_MANUAL_TEXT_COLOR, BUTTON_MANUAL_LABEL, BUTTON_MANUAL_NAVIGATION};
Button *homeButtons[4] = {&dayButton, &nightButton, &playButton, &manButton};

// ====================== Manual Buttons ======================
Functionality doorButtonFunc = {BUTTON_DOOR_PIN, BUTTON_DOOR_STATE};
Button doorButton = {BUTTON_DOOR_POS_X, BUTTON_DOOR_POS_Y, BUTTON_DOOR_WIDTH, BUTTON_DOOR_HEIGHT, BUTTON_DOOR_BITMAP, BUTTON_DOOR_BACKGROUND_COLOR, BUTTON_DOOR_TEXT_COLOR, BUTTON_DOOR_LABEL, BUTTON_DOOR_NAVIGATION, &doorButtonFunc};
Functionality lightsButtonFunc = {BUTTON_LIGHTS_PIN, BUTTON_LIGHTS_STATE};
Button lightsButton = {BUTTON_LIGHTS_POS_X, BUTTON_LIGHTS_POS_Y, BUTTON_LIGHTS_WIDTH, BUTTON_LIGHTS_HEIGHT, BUTTON_LIGHTS_BITMAP, BUTTON_LIGHTS_BACKGROUND_COLOR, BUTTON_LIGHTS_TEXT_COLOR, BUTTON_LIGHTS_LABEL, BUTTON_LIGHTS_NAVIGATION, &lightsButtonFunc};
Button homeButton = {BUTTON_HOME_POS_X, BUTTON_HOME_POS_Y, BUTTON_HOME_WIDTH, BUTTON_HOME_HEIGHT, BUTTON_HOME_BITMAP, BUTTON_HOME_BACKGROUND_COLOR, BUTTON_HOME_TEXT_COLOR, BUTTON_HOME_LABEL, BUTTON_HOME_NAVIGATION};
Button *manualButtons[3] = {&doorButton, &lightsButton, &homeButton};


// ====================== Bargraph ======================
Bargraph waterBargraph = { WATER_BARGRAPH_POS_X, WATER_BARGRAPH_POS_Y, WATER_BARGRAPH_WIDTH, WATER_BARGRAPH_HEIGHT, WATER_BARGRAPH_BITMAP, WATER_BARGRAPH_LABEL };
Bargraph foodBargraph = { FOOD_BARGRAPH_POS_X, FOOD_BARGRAPH_POS_Y, FOOD_BARGRAPH_WIDTH, FOOD_BARGRAPH_HEIGHT, FOOD_BARGRAPH_BITMAP, FOOD_BARGRAPH_LABEL };

// Initialize Pins
void initializePins()
{
	// Enable all bases
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOI_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	
	// Initialize Pin D0
	HAL_GPIO_Init(GPIOC, &pinD0);
	HAL_GPIO_WritePin(GPIOC, pinD0.Pin, GPIO_PIN_RESET);
	
	// Initialize Pin D1
	HAL_GPIO_Init(GPIOC, &pinD1);
	HAL_GPIO_WritePin(GPIOC, pinD1.Pin, GPIO_PIN_RESET);
	
	// Initialize Pin D2
	HAL_GPIO_Init(GPIOG, &pinD2);
	HAL_GPIO_WritePin(GPIOG, pinD2.Pin, GPIO_PIN_RESET);
	
	// Initialize Pin D3
	HAL_GPIO_Init(GPIOB, &pinD3);
	HAL_GPIO_WritePin(GPIOB, pinD3.Pin, GPIO_PIN_RESET);
	
	// Initialize Pin D4
	HAL_GPIO_Init(GPIOG, &pinD4);
	HAL_GPIO_WritePin(GPIOG, pinD4.Pin, GPIO_PIN_RESET);
	
	// Initialize Pin D5
	HAL_GPIO_Init(GPIOI, &pinD5);
	HAL_GPIO_WritePin(GPIOI, pinD5.Pin, GPIO_PIN_RESET);
	
	// Initialize Pin D6
	HAL_GPIO_Init(GPIOH, &pinD6);
	HAL_GPIO_WritePin(GPIOH, pinD6.Pin, GPIO_PIN_RESET);
	
	// Initialize Pin D7
	HAL_GPIO_Init(GPIOI, &pinD7);
	HAL_GPIO_WritePin(GPIOI, pinD7.Pin, GPIO_PIN_RESET);
	
	// Initialize Pin D8
	HAL_GPIO_Init(GPIOI, &pinD8);
	HAL_GPIO_WritePin(GPIOI, pinD8.Pin, GPIO_PIN_RESET);
	
	// Initialize Pin D9
	HAL_GPIO_Init(GPIOA, &pinD9);
	HAL_GPIO_WritePin(GPIOA, pinD9.Pin, GPIO_PIN_RESET);
	
	// Initialize Pin D10
	HAL_GPIO_Init(GPIOA, &pinD10);
	HAL_GPIO_WritePin(GPIOA, pinD10.Pin, GPIO_PIN_RESET);
	
	// Initialize Pin D11
	HAL_GPIO_Init(GPIOB, &pinD11);
	HAL_GPIO_WritePin(GPIOB, pinD11.Pin, GPIO_PIN_RESET);
	
	// Initialize Pin D12
	HAL_GPIO_Init(GPIOB, &pinD12);
	HAL_GPIO_WritePin(GPIOB, pinD12.Pin, GPIO_PIN_RESET);
	
	// Initialize Pin D13
	HAL_GPIO_Init(GPIOI, &pinD13);
	HAL_GPIO_WritePin(GPIOI, pinD13.Pin, GPIO_PIN_RESET);
	
	// Initialize Pin D14
	HAL_GPIO_Init(GPIOB, &pinD14);
	HAL_GPIO_WritePin(GPIOB, pinD14.Pin, GPIO_PIN_RESET);
	
	// Initialize Pin D15
	HAL_GPIO_Init(GPIOB, &pinD15);
	HAL_GPIO_WritePin(GPIOB, pinD15.Pin, GPIO_PIN_RESET);
	
	// Initialize Pin A0
	HAL_GPIO_Init(GPIOA, &pinA0);
	HAL_GPIO_WritePin(GPIOA, pinA0.Pin, GPIO_PIN_RESET);
	
	// Initialize Pin A1
	HAL_GPIO_Init(GPIOF, &pinA1);
	HAL_GPIO_WritePin(GPIOF, pinA1.Pin, GPIO_PIN_RESET);
	
	// Initialize Pin A2
	HAL_GPIO_Init(GPIOF, &pinA2);
	HAL_GPIO_WritePin(GPIOF, pinA2.Pin, GPIO_PIN_RESET);
	
	// Initialize Pin A3
	HAL_GPIO_Init(GPIOF, &pinA3);
	HAL_GPIO_WritePin(GPIOF, pinA3.Pin, GPIO_PIN_RESET);
	
	// Initialize Pin A4
	HAL_GPIO_Init(GPIOF, &pinA4);
	HAL_GPIO_WritePin(GPIOF, pinA4.Pin, GPIO_PIN_RESET);
	
	// Initialize Pin A5
	HAL_GPIO_Init(GPIOF, &pinA5);
	HAL_GPIO_WritePin(GPIOF, pinA5.Pin, GPIO_PIN_RESET);
}

// Delay Function
void wait(int delay)
{
	int i = 0;
	for(i = 0; i < delay; i++)
	{
	}
}

// Draws the home page
void drawHomePage(void)
{
	
	// Draw Screen Label
	app_drawScreenLabel(&homeLabel);
	
	// Draw Clock
	app_drawClock(&clock);
	
	// Set Background To Purple
	GLCD_SetBackgroundColor (GLCD_COLOR_PURPLE);
	
	// Draw Day Button
	app_drawButton(&dayButton);

	// Draw Night Button
	app_drawButton(&nightButton);
	
	// Draw Play Button
	app_drawButton(&playButton);
	
	// Draw Manual Button
	app_drawButton(&manButton);
	
	// Draw Water Level
	app_drawBargraph(&waterBargraph);
	
	// Draw Food Level
	app_drawBargraph(&foodBargraph);
	
}

// Draws the manual page
void drawManualPage()
{
	
	// Draw Screen Label
	app_drawScreenLabel(&manualLabel);
	
	// Draw Door Button
	app_drawButton(&doorButton);
	
	// Draw Lights Button
	app_drawButton(&lightsButton);
	
	// Draw Home Button
	app_drawButton(&homeButton);
	
}

// Home Page Navigation
void homePageNavigation(char **page)
{
	unsigned short i = 0;
	uint32_t tic, toc = 0;
	uint32_t elapsed_t;
	TOUCH_STATE tscState;
	
	/* elapsed_t is elapsed (10 * msec) since midnight */
	elapsed_t = clock.second*100+clock.minute*60*100+clock.hour*60*60*100;
	
	while(1)
	{
		if (strcmp(*page, "Home") == 0)
		{
			app_clockTicToc(&tic, &toc, &elapsed_t, &clock);
			Touch_GetState(&tscState);
			if (tscState.pressed)
			{
				for (i = 0; i < 4; i++)
				{
					if (tscState.x > homeButtons[i]->posX && tscState.x < (homeButtons[i]->width + homeButtons[i]->posX)
					 && tscState.y > homeButtons[i]->posY && tscState.y < (homeButtons[i]->height + homeButtons[i]->posY))
					{
						GLCD_SetFont (&GLCD_Font_16x24);
						GLCD_SetBackgroundColor (GLCD_COLOR_LIGHT_GREY);
						GLCD_SetForegroundColor (GLCD_COLOR_WHITE);
						GLCD_DrawString (20, 40, homeButtons[i]->label);
						
						*page = homeButtons[i]->label;
						
					}
				}
			} else {
				GLCD_SetFont (&GLCD_Font_16x24);
				GLCD_SetBackgroundColor (GLCD_COLOR_LIGHT_GREY);
				GLCD_SetForegroundColor (GLCD_COLOR_WHITE);
			}
		} else {
			break;
		}
	}
}

// Home Page Navigation
void manualPageNavigation(char **page)
{
	unsigned short i = 0;
	TOUCH_STATE tscState;
	
	while(1)
	{
		if (strcmp(*page, "Manual") == 0)
		{
			Touch_GetState(&tscState);
			if (tscState.pressed)
			{
				for (i = 0; i < 3; i++)
				{
					if (tscState.x > manualButtons[i]->posX && tscState.x < (manualButtons[i]->width + manualButtons[i]->posX)
					 && tscState.y > manualButtons[i]->posY && tscState.y < (manualButtons[i]->height + manualButtons[i]->posY))
					{
						GLCD_SetFont (&GLCD_Font_16x24);
						GLCD_SetBackgroundColor (GLCD_COLOR_LIGHT_GREY);
						GLCD_SetForegroundColor (GLCD_COLOR_WHITE);
						GLCD_DrawString (20, 40, manualButtons[i]->label);
						
						if (manualButtons[i]->navigation)
						{
							*page = manualButtons[i]->label;
						} else {
							if (manualButtons[i]->funtionality->state == 0)
							{
								HAL_GPIO_WritePin(GPIOC, CN4Pins[manualButtons[i]->funtionality->pin]->Pin, GPIO_PIN_SET);
								manualButtons[i]->backgroundColor = GLCD_COLOR_GREEN;
								app_drawButton(&*manualButtons[i]);
								manualButtons[i]->funtionality->state = 1;
								wait(50000000);
							} else {
								HAL_GPIO_WritePin(GPIOC, CN4Pins[manualButtons[i]->funtionality->pin]->Pin, GPIO_PIN_RESET);
								manualButtons[i]->backgroundColor = GLCD_COLOR_RED;
								app_drawButton(&*manualButtons[i]);
								manualButtons[i]->funtionality->state = 0;
								wait(50000000);
							}
						}
						
					}
				}
			} else {
				GLCD_SetFont (&GLCD_Font_16x24);
				GLCD_SetBackgroundColor (GLCD_COLOR_LIGHT_GREY);
				GLCD_SetForegroundColor (GLCD_COLOR_WHITE);
				GLCD_DrawString (20, 40, "            ");
			}
		} else {
			break;
		}
	}
	
}