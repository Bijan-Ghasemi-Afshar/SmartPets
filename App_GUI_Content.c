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
//GPIO_InitTypeDef pinD8 = {GPIO_PIN_2, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_HIGH};
//GPIO_InitTypeDef pinD9 = {GPIO_PIN_15, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_HIGH};
//GPIO_InitTypeDef pinD10 = {GPIO_PIN_8, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_HIGH};
//GPIO_InitTypeDef pinD11 = {GPIO_PIN_15, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_HIGH};
//GPIO_InitTypeDef pinD12 = {GPIO_PIN_14, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_HIGH};
//GPIO_InitTypeDef pinD13 = {GPIO_PIN_1, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_HIGH};
//GPIO_InitTypeDef pinD14 = {GPIO_PIN_9, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_HIGH};
//GPIO_InitTypeDef pinD15 = {GPIO_PIN_8, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_HIGH};
//GPIO_InitTypeDef *CN7Pins[8] = {&pinD8, &pinD9, &pinD10, &pinD11, &pinD12, &pinD13, &pinD14, &pinD15};

// ====================== CN5 GPIO PINS ======================
//GPIO_InitTypeDef pinA0 = {GPIO_PIN_0, GPIO_MODE_ANALOG, GPIO_NOPULL, GPIO_SPEED_HIGH};
//GPIO_InitTypeDef pinA1 = {GPIO_PIN_10, GPIO_MODE_ANALOG, GPIO_NOPULL, GPIO_SPEED_HIGH};
//GPIO_InitTypeDef pinA2 = {GPIO_PIN_9, GPIO_MODE_ANALOG, GPIO_NOPULL, GPIO_SPEED_HIGH};
//GPIO_InitTypeDef pinA3 = {GPIO_PIN_8, GPIO_MODE_ANALOG, GPIO_NOPULL, GPIO_SPEED_HIGH};
//GPIO_InitTypeDef pinA4 = {GPIO_PIN_7, GPIO_MODE_ANALOG, GPIO_NOPULL, GPIO_SPEED_HIGH};
//GPIO_InitTypeDef pinA5 = {GPIO_PIN_6, GPIO_MODE_ANALOG, GPIO_NOPULL, GPIO_SPEED_HIGH};
//GPIO_InitTypeDef *CN5Pins[6] = {&pinA0, &pinA1, &pinA2, &pinA3, &pinA4, &pinA5};

// ====================== Screen Label ======================
ScreenLabel homeLabel = {20, 20, "Home"};
ScreenLabel manualLabel = {20, 20, "Manual"};
ScreenLabel dayLabel = {20, 20, "Day"};
ScreenLabel nightLabel = {20, 20, "Night"};
ScreenLabel playLabel = {20, 20, "Play"};
ScreenLabel startLabel = {20, 70, "Start"};
ScreenLabel editLabel = {20, 140, "Edit"};

// ====================== Clock ======================
Clock clock = {CLOCK_POS_X, CLOCK_POS_Y, CLOCK_HOUR, CLOCK_MIN, CLOCK_SEC};
Clock dayProgramClock = {DAY_PROGRAM_CLOCK_POS_X, DAY_PROGRAM_CLOCK_POS_Y, DAY_PROGRAM_CLOCK_HOUR, DAY_PROGRAM_CLOCK_MIN};
Clock nightProgramClock = {NIGHT_PROGRAM_CLOCK_POS_X, NIGHT_PROGRAM_CLOCK_POS_Y, NIGHT_PROGRAM_CLOCK_HOUR, NIGHT_PROGRAM_CLOCK_MIN};

// ====================== Home Buttons ======================
Button dayButton = {BUTTON_DAY_POS_X, BUTTON_DAY_POS_Y, BUTTON_DAY_WIDTH, BUTTON_DAY_HEIGHT, BUTTON_DAY_BACKGROUND_COLOR, BUTTON_DAY_LABEL, BUTTON_DAY_NAVIGATION};
Button nightButton = {BUTTON_NIGHT_POS_X, BUTTON_NIGHT_POS_Y, BUTTON_NIGHT_WIDTH, BUTTON_NIGHT_HEIGHT, BUTTON_NIGHT_BACKGROUND_COLOR, BUTTON_NIGHT_LABEL, BUTTON_NIGHT_NAVIGATION};
Button playButton = {BUTTON_PLAY_POS_X, BUTTON_PLAY_POS_Y, BUTTON_PLAY_WIDTH, BUTTON_PLAY_HEIGHT, BUTTON_PLAY_BACKGROUND_COLOR, BUTTON_PLAY_LABEL, BUTTON_PLAY_NAVIGATION};
Button manButton = {BUTTON_MANUAL_POS_X, BUTTON_MANUAL_POS_Y, BUTTON_MANUAL_WIDTH, BUTTON_MANUAL_HEIGHT, BUTTON_MANUAL_BACKGROUND_COLOR, BUTTON_MANUAL_LABEL, BUTTON_MANUAL_NAVIGATION};
Button *homeButtons[4] = {&dayButton, &nightButton, &playButton, &manButton};

// ====================== Manual Buttons ======================
Functionality doorButtonFunc = {BUTTON_DOOR_PIN, BUTTON_DOOR_STATE};
Button doorButton = {BUTTON_DOOR_POS_X, BUTTON_DOOR_POS_Y, BUTTON_DOOR_WIDTH, BUTTON_DOOR_HEIGHT, BUTTON_DOOR_BACKGROUND_COLOR, BUTTON_DOOR_LABEL, BUTTON_DOOR_NAVIGATION, &doorButtonFunc};
Functionality lightsButtonFunc = {BUTTON_LIGHTS_PIN, BUTTON_LIGHTS_STATE};
Button lightsButton = {BUTTON_LIGHTS_POS_X, BUTTON_LIGHTS_POS_Y, BUTTON_LIGHTS_WIDTH, BUTTON_LIGHTS_HEIGHT, BUTTON_LIGHTS_BACKGROUND_COLOR, BUTTON_LIGHTS_LABEL, BUTTON_LIGHTS_NAVIGATION, &lightsButtonFunc};
Button homeButton = {BUTTON_HOME_POS_X, BUTTON_HOME_POS_Y, BUTTON_HOME_WIDTH, BUTTON_HOME_HEIGHT, BUTTON_HOME_BACKGROUND_COLOR, BUTTON_HOME_LABEL, BUTTON_HOME_NAVIGATION};
Button *manualButtons[3] = {&doorButton, &lightsButton, &homeButton};

// ====================== Day Buttons ======================
Button *dayButtons[1] = {&homeButton};

// ====================== Night Buttons ======================
Button *nightButtons[1] = {&homeButton};

// ====================== Play Buttons ======================
Button *playButtons[1] = {&homeButton};

// ====================== Bargraph ======================
Bargraph waterBargraph = { WATER_BARGRAPH_POS_X, WATER_BARGRAPH_POS_Y, WATER_BARGRAPH_WIDTH, WATER_BARGRAPH_HEIGHT, WATER_BARGRAPH_LABEL };
Bargraph foodBargraph = { FOOD_BARGRAPH_POS_X, FOOD_BARGRAPH_POS_Y, FOOD_BARGRAPH_WIDTH, FOOD_BARGRAPH_HEIGHT, FOOD_BARGRAPH_LABEL };

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
//	HAL_GPIO_Init(GPIOI, &pinD8);
//	HAL_GPIO_WritePin(GPIOI, pinD8.Pin, GPIO_PIN_RESET);
//	
//	// Initialize Pin D9
//	HAL_GPIO_Init(GPIOA, &pinD9);
//	HAL_GPIO_WritePin(GPIOA, pinD9.Pin, GPIO_PIN_RESET);
//	
//	// Initialize Pin D10
//	HAL_GPIO_Init(GPIOA, &pinD10);
//	HAL_GPIO_WritePin(GPIOA, pinD10.Pin, GPIO_PIN_RESET);
//	
//	// Initialize Pin D11
//	HAL_GPIO_Init(GPIOB, &pinD11);
//	HAL_GPIO_WritePin(GPIOB, pinD11.Pin, GPIO_PIN_RESET);
//	
//	// Initialize Pin D12
//	HAL_GPIO_Init(GPIOB, &pinD12);
//	HAL_GPIO_WritePin(GPIOB, pinD12.Pin, GPIO_PIN_RESET);
//	
//	// Initialize Pin D13
//	HAL_GPIO_Init(GPIOI, &pinD13);
//	HAL_GPIO_WritePin(GPIOI, pinD13.Pin, GPIO_PIN_RESET);
//	
//	// Initialize Pin D14
//	HAL_GPIO_Init(GPIOB, &pinD14);
//	HAL_GPIO_WritePin(GPIOB, pinD14.Pin, GPIO_PIN_RESET);
//	
//	// Initialize Pin D15
//	HAL_GPIO_Init(GPIOB, &pinD15);
//	HAL_GPIO_WritePin(GPIOB, pinD15.Pin, GPIO_PIN_RESET);
//	
//	// Initialize Pin A0
//	HAL_GPIO_Init(GPIOA, &pinA0);
//	HAL_GPIO_WritePin(GPIOA, pinA0.Pin, GPIO_PIN_RESET);
//	
//	// Initialize Pin A1
//	HAL_GPIO_Init(GPIOF, &pinA1);
//	HAL_GPIO_WritePin(GPIOF, pinA1.Pin, GPIO_PIN_RESET);
//	
//	// Initialize Pin A2
//	HAL_GPIO_Init(GPIOF, &pinA2);
//	HAL_GPIO_WritePin(GPIOF, pinA2.Pin, GPIO_PIN_RESET);
//	
//	// Initialize Pin A3
//	HAL_GPIO_Init(GPIOF, &pinA3);
//	HAL_GPIO_WritePin(GPIOF, pinA3.Pin, GPIO_PIN_RESET);
//	
//	// Initialize Pin A4
//	HAL_GPIO_Init(GPIOF, &pinA4);
//	HAL_GPIO_WritePin(GPIOF, pinA4.Pin, GPIO_PIN_RESET);
//	
//	// Initialize Pin A5
//	HAL_GPIO_Init(GPIOF, &pinA5);
//	HAL_GPIO_WritePin(GPIOF, pinA5.Pin, GPIO_PIN_RESET);
}


// Draws the home page
void drawHomePage(void)
{
	
	// Draw Screen Label
	app_drawScreenLabel(&homeLabel);
	
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
void drawManualPage(void)
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

// Draws the day program page
void drawDayProgramPage(void)
{
	// Draw Screen Label
	app_drawScreenLabel(&dayLabel);
	
	// Draw Program time Label
	app_drawScreenLabel(&startLabel);
	
	// Draw Edit Label
	app_drawScreenLabel(&editLabel);
	
	// Draw Program Clock
	app_drawProgramClock(&dayProgramClock);
	
	// Draw Edit Buttons
	app_drawProgramTimeEdit((GLCD_SIZE_X/4 + 20), 140, &dayProgramClock);
	
	// Draw Home Button
	app_drawButton(&homeButton);
}

// Draws the night program page
void drawNightProgramPage(void)
{
	// Draw Screen Label
	app_drawScreenLabel(&nightLabel);
	
	// Draw Program time Label
	app_drawScreenLabel(&startLabel);
	
	// Draw Edit Label
	app_drawScreenLabel(&editLabel);
	
	// Draw Program Clock
	app_drawProgramClock(&nightProgramClock);
	
	// Draw Edit Buttons
	app_drawProgramTimeEdit((GLCD_SIZE_X/4 + 20), 140, &nightProgramClock);
	
	// Draw Home Button
	app_drawButton(&homeButton);
}

// Draws the night program page
void drawPlayProgramPage(void)
{
	// Draw Screen Label
	app_drawScreenLabel(&playLabel);
	
	// Draw Clock
	app_drawClock(&clock);
	
	// Draw Home Button
	app_drawButton(&homeButton);
}

// Home Page Navigation
void homePageNavigation(char **page)
{
	app_userInputHandle(page, 4, homeButtons, CN4Pins, &clock);
}

// Manual Page Navigation
void manualPageNavigation(char **page)
{
	app_userInputHandle(page, 3, manualButtons, CN4Pins, &clock);
}

// Day Page Navigation
void dayPageNavigation(char **page)
{
	app_userInputHandle(page, 1, dayButtons, CN4Pins, &clock);
}

// Night Page Navigation
void nightPageNavigation(char **page)
{
	app_userInputHandle(page, 1, nightButtons, CN4Pins, &clock);
}

// Play Page Navigation
void playPageNavigation(char **page)
{
	app_userInputHandle(page, 1, playButtons, CN4Pins, &clock);
}



