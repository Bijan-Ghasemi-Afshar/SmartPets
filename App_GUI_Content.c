#include "GUI_Utility.h"
#include "GLCD_Config.h"
#include "Board_GLCD.h"
#include "App_GUI_Content.h"
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_gpio.h"

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
Clock dayProgramClock = {DAY_PROGRAM_CLOCK_POS_X, DAY_PROGRAM_CLOCK_POS_Y, DAY_PROGRAM_CLOCK_HOUR, DAY_PROGRAM_CLOCK_MIN, 0, 0};
Clock nightProgramClock = {NIGHT_PROGRAM_CLOCK_POS_X, NIGHT_PROGRAM_CLOCK_POS_Y, NIGHT_PROGRAM_CLOCK_HOUR, NIGHT_PROGRAM_CLOCK_MIN, 0, 0};
Clock playProgramClock = {NIGHT_PROGRAM_CLOCK_POS_X, NIGHT_PROGRAM_CLOCK_POS_Y, 11, 23, 0, 0};
Clock *programs[3] = {&dayProgramClock, &nightProgramClock, &playProgramClock};

// ====================== Home Buttons ======================
Button dayButton = {GLCD_SIZE_X/4 - 20, GLCD_SIZE_Y/4, GLCD_SIZE_X/4, GLCD_SIZE_Y/5, "Day", 1};
Button nightButton = {((GLCD_SIZE_X/4) * 2) + 20, GLCD_SIZE_Y/4, GLCD_SIZE_X/4, GLCD_SIZE_Y/5, "Night", 1};
Button playButton = {BUTTON_PLAY_POS_X, BUTTON_PLAY_POS_Y, BUTTON_PLAY_WIDTH, BUTTON_PLAY_HEIGHT, BUTTON_PLAY_LABEL, BUTTON_PLAY_NAVIGATION};
Button manButton = {BUTTON_MANUAL_POS_X, BUTTON_MANUAL_POS_Y, BUTTON_MANUAL_WIDTH, BUTTON_MANUAL_HEIGHT, BUTTON_MANUAL_LABEL, BUTTON_MANUAL_NAVIGATION};
Button *homeButtons[4] = {&dayButton, &nightButton, &playButton, &manButton};

// ====================== Manual Buttons ======================
Functionality doorButtonFunc = {BUTTON_DOOR_PIN, GPIOC, BUTTON_DOOR_STATE, "pwm"};
Functionality lightsButtonFunc = {BUTTON_LIGHTS_PIN, GPIOC, BUTTON_LIGHTS_STATE, "digital"};
Functionality heatingButtonFunc = {BUTTON_HEATING_PIN, GPIOC, BUTTON_HEATING_STATE, "digital"};
Functionality fanButtonFunc = {BUTTON_FAN_PIN, GPIOG, BUTTON_FAN_STATE, "digital"};
Button doorButton = {BUTTON_DOOR_POS_X, BUTTON_DOOR_POS_Y, BUTTON_DOOR_WIDTH, BUTTON_DOOR_HEIGHT, BUTTON_DOOR_LABEL, BUTTON_DOOR_NAVIGATION, &doorButtonFunc};
Button lightsButton = {BUTTON_LIGHTS_POS_X, BUTTON_LIGHTS_POS_Y, BUTTON_LIGHTS_WIDTH, BUTTON_LIGHTS_HEIGHT, BUTTON_LIGHTS_LABEL, BUTTON_LIGHTS_NAVIGATION, &lightsButtonFunc};
Button HeatingButton = {BUTTON_HEATING_POS_X, BUTTON_HEATING_POS_Y, BUTTON_HEATING_WIDTH, BUTTON_HEATING_HEIGHT, BUTTON_HEATING_LABEL, BUTTON_HEATING_NAVIGATION, &heatingButtonFunc};
Button fanButton = {BUTTON_FAN_POS_X, BUTTON_FAN_POS_Y, BUTTON_FAN_WIDTH, BUTTON_FAN_HEIGHT, BUTTON_FAN_LABEL, BUTTON_FAN_NAVIGATION, &fanButtonFunc};
Button homeButton = {BUTTON_HOME_POS_X, BUTTON_HOME_POS_Y, BUTTON_HOME_WIDTH, BUTTON_HOME_HEIGHT, BUTTON_HOME_LABEL, BUTTON_HOME_NAVIGATION};
Button *manualButtons[5] = {&doorButton, &lightsButton, &homeButton, &HeatingButton, &fanButton};

// ====================== Edit Program Buttons ======================
Functionality editFunctionality = {0, 0, 0, "edit"};
Button editIncHour = {(GLCD_SIZE_X/4 + 60), 140, 40, 40, "+h", 0, &editFunctionality};
Button editDecHour = {(GLCD_SIZE_X/4 + 120), 140, 40, 40, "-h", 0, &editFunctionality};
Button editIncMin = {(GLCD_SIZE_X/4 + 250), 140, 40, 40, "+m", 0, &editFunctionality};
Button editDecMin = {(GLCD_SIZE_X/4 + 300), 140, 40, 40, "-m", 0, &editFunctionality};
Button *editButtons[5] = {&homeButton, &editIncHour, &editDecHour, &editIncMin, &editDecMin};

// ====================== Bargraph ======================
Bargraph waterBargraph = { WATER_BARGRAPH_POS_X, WATER_BARGRAPH_POS_Y, WATER_BARGRAPH_WIDTH, WATER_BARGRAPH_HEIGHT, GLCD_COLOR_GREEN, WATER_BARGRAPH_LABEL };
Bargraph foodBargraph = { FOOD_BARGRAPH_POS_X, FOOD_BARGRAPH_POS_Y, FOOD_BARGRAPH_WIDTH, FOOD_BARGRAPH_HEIGHT, GLCD_COLOR_GREEN, FOOD_BARGRAPH_LABEL };



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
void drawHomePage(char **page)
{
	// Draw Screen Label
	app_drawScreenLabel(&homeLabel);
	
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
	
	app_userInputHandle(page, 4, homeButtons, CN4Pins, &clock, programs);
}

// Draws the manual page
void drawManualPage(char **page)
{
	
	// Draw Screen Label
	app_drawScreenLabel(&manualLabel);
	
	// Draw Door Button
	app_drawButton(&doorButton);
	
	// Draw Lights Button
	app_drawButton(&lightsButton);
	
	// Draw Heating Button
	app_drawButton(&HeatingButton);
	
	// Draw Fan Button
	app_drawButton(&fanButton);
	
	// Draw Home Button
	app_drawButton(&homeButton);
	
	// Handle user input
	app_userInputHandle(page, 5, manualButtons, CN4Pins, &clock, programs);
	
}

// Draws the day program page
void drawDayProgramPage(char **page)
{
	// Draw Screen Label
	app_drawScreenLabel(&dayLabel);
	
	// Draw Program time Label
	app_drawScreenLabel(&startLabel);
	
	// Draw Edit Label
	app_drawScreenLabel(&editLabel);
	
	// Draw Home Button
	app_drawButton(&homeButton);
	
	// Draw Program Clock
	app_drawProgramClock(&dayProgramClock);
	
	// Draw Edit Buttons
	app_drawProgramTimeEdit(&editIncHour, &editDecHour, &editIncMin, &editDecMin ,&dayProgramClock);
	
	app_userInputHandle(page, 5, editButtons, CN4Pins, &clock, programs);
}

// Draws the night program page
void drawNightProgramPage(char **page)
{
	// Draw Screen Label
	app_drawScreenLabel(&nightLabel);
	
	// Draw Program time Label
	app_drawScreenLabel(&startLabel);
	
	// Draw Edit Label
	app_drawScreenLabel(&editLabel);
	
	// Draw Home Button
	app_drawButton(&homeButton);
	
	// Draw Program Clock
	app_drawProgramClock(&nightProgramClock);
	
	// Draw Edit Buttons
	app_drawProgramTimeEdit(&editIncHour, &editDecHour, &editIncMin, &editDecMin ,&nightProgramClock);
	
	app_userInputHandle(page, 5, editButtons, CN4Pins, &clock, programs);
}

// Draws the night program page
void drawPlayProgramPage(char **page)
{
	// Draw Screen Label
	app_drawScreenLabel(&playLabel);
	
	// Draw Program time Label
	app_drawScreenLabel(&startLabel);
	
	// Draw Edit Label
	app_drawScreenLabel(&editLabel);
	
	// Draw Home Button
	app_drawButton(&homeButton);
	
	// Draw Program Clock
	app_drawProgramClock(&playProgramClock);
	
	// Draw Edit Buttons
	app_drawProgramTimeEdit(&editIncHour, &editDecHour, &editIncMin, &editDecMin ,&playProgramClock);
	
	app_userInputHandle(page, 5, editButtons, CN4Pins, &clock, programs);
}

