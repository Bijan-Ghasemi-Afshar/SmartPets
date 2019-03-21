#include "GUI_Utility.h"
#include "Board_GLCD.h"
#include "GLCD_Config.h"
#include "App_GUI_Content.h"
#include "Board_Touch.h"
#include <string.h>
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_gpio.h"


extern GLCD_FONT GLCD_Font_16x24;

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
	
	ScreenLabel scrLabel;
	Clock clock;
	Button dayButton, nightButton, playButton, manButton;
	Bargraph waterBargraph, foodBargraph;
	
	// ====================== Screen Label ======================
	scrLabel.posX = 20;
	scrLabel.posY = 20;
	scrLabel.name = "Home";
	
	// ====================== Clock ======================
	clock.hour = 11;
	clock.minute = 20;
	clock.second = 30;
	clock.posX = GLCD_SIZE_X/4 + 20;
	clock.posY = 20;
	
	// ====================== Buttons ======================
	dayButton.posX = BUTTON_DAY_POS_X;
	dayButton.posY = BUTTON_DAY_POS_Y;
	dayButton.width = BUTTON_DAY_WIDTH;
	dayButton.height = BUTTON_DAY_HEIGHT;
	dayButton.bitmap = BUTTON_DAY_BITMAP;
	dayButton.backgroundColor = GLCD_COLOR_PURPLE;
	dayButton.color = BUTTON_DAY_TEXT_COLOR;
	dayButton.label = BUTTON_DAY_LABEL;
	dayButton.navigation = BUTTON_DAY_NAVIGATION;
	
	nightButton.posX = BUTTON_NIGHT_POS_X;
	nightButton.posY = BUTTON_NIGHT_POS_Y;
	nightButton.width = BUTTON_NIGHT_WIDTH;
	nightButton.height = BUTTON_NIGHT_HEIGHT;
	nightButton.bitmap = BUTTON_NIGHT_BITMAP;
	nightButton.backgroundColor = BUTTON_NIGHT_BACKGROUND_COLOR;
	nightButton.color = BUTTON_NIGHT_TEXT_COLOR;
	nightButton.label = BUTTON_NIGHT_LABEL;
	nightButton.navigation = BUTTON_NIGHT_NAVIGATION;
	
	playButton.posX = BUTTON_PLAY_POS_X;
	playButton.posY = BUTTON_PLAY_POS_Y;
	playButton.width = BUTTON_PLAY_WIDTH;
	playButton.height = BUTTON_PLAY_HEIGHT;
	playButton.bitmap = BUTTON_PLAY_BITMAP;
	playButton.backgroundColor = BUTTON_PLAY_BACKGROUND_COLOR;
	playButton.color = BUTTON_PLAY_TEXT_COLOR;
	playButton.label = BUTTON_PLAY_LABEL;
	playButton.navigation = BUTTON_PLAY_NAVIGATION;
	
	manButton.posX = BUTTON_MANUAL_POS_X;
	manButton.posY = BUTTON_MANUAL_POS_Y;
	manButton.width = BUTTON_MANUAL_WIDTH;
	manButton.height = BUTTON_MANUAL_HEIGHT;
	manButton.bitmap = BUTTON_MANUAL_BITMAP;
	manButton.backgroundColor = BUTTON_MANUAL_BACKGROUND_COLOR;
	manButton.color = BUTTON_MANUAL_TEXT_COLOR;
	manButton.label = BUTTON_MANUAL_LABEL;
	manButton.navigation = BUTTON_MANUAL_NAVIGATION;
	
	// ====================== Bargraph ======================
	waterBargraph.posX = GLCD_SIZE_X/4 - 20;
	waterBargraph.posY = GLCD_SIZE_Y/5 * 4 - 10;
	waterBargraph.width = GLCD_SIZE_X/2 + 40;
	waterBargraph.height = 10;
	waterBargraph.label = "Water";
	waterBargraph.bitmap = 0;
	
	foodBargraph.posX = GLCD_SIZE_X/4 - 20;
	foodBargraph.posY = GLCD_SIZE_Y/5 * 4 + 10;
	foodBargraph.width = GLCD_SIZE_X/2 + 40;
	foodBargraph.height = 10;
	foodBargraph.label = "Food";
	foodBargraph.bitmap = 0;
	
	// Draw Screen Label
	app_drawScreenLabel(&scrLabel);
	
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
	
	ScreenLabel scrLabel;
	Button doorButton, lightsButton, homeButton;
	Functionality lightsButtonFunc, doorButtonFunc;
	
	// ====================== Screen Label ======================
	scrLabel.posX = 20;
	scrLabel.posY = 20;
	scrLabel.name = "Manual";
	
	// ====================== Functionality ======================
	lightsButtonFunc.pin = BUTTON_LIGHTS_PIN;
	lightsButtonFunc.state = BUTTON_LIGHTS_STATE;
	
	doorButtonFunc.pin = BUTTON_DOOR_PIN;
	doorButtonFunc.state = BUTTON_DOOR_STATE;
	
	// ====================== Buttons ======================
	doorButton.posX = BUTTON_DOOR_POS_X;
	doorButton.posY = BUTTON_DOOR_POS_Y;
	doorButton.width = BUTTON_DOOR_WIDTH;
	doorButton.height = BUTTON_DOOR_HEIGHT;
	doorButton.bitmap = BUTTON_DOOR_BITMAP;
	doorButton.backgroundColor = BUTTON_DOOR_BACKGROUND_COLOR;
	doorButton.color = BUTTON_DOOR_TEXT_COLOR;
	doorButton.label = BUTTON_DOOR_LABEL;
	doorButton.navigation = BUTTON_DOOR_NAVIGATION;
	doorButton.funtionality = doorButtonFunc;
	
	lightsButton.posX = BUTTON_LIGHTS_POS_X;
	lightsButton.posY = BUTTON_LIGHTS_POS_Y;
	lightsButton.width = BUTTON_LIGHTS_WIDTH;
	lightsButton.height = BUTTON_LIGHTS_HEIGHT;
	lightsButton.bitmap = BUTTON_LIGHTS_BITMAP;
	lightsButton.backgroundColor = BUTTON_LIGHTS_BACKGROUND_COLOR;
	lightsButton.color = BUTTON_LIGHTS_TEXT_COLOR;
	lightsButton.label = BUTTON_LIGHTS_LABEL;
	lightsButton.navigation = BUTTON_LIGHTS_NAVIGATION;
	lightsButton.funtionality = lightsButtonFunc;
	
	homeButton.posX = BUTTON_HOME_POS_X;
	homeButton.posY = BUTTON_HOME_POS_Y;
	homeButton.width = BUTTON_HOME_WIDTH;
	homeButton.height = BUTTON_HOME_HEIGHT;
	homeButton.bitmap = BUTTON_HOME_BITMAP;
	homeButton.backgroundColor = BUTTON_HOME_BACKGROUND_COLOR;
	homeButton.color = BUTTON_HOME_TEXT_COLOR;
	homeButton.label = BUTTON_HOME_LABEL;
	homeButton.navigation = BUTTON_HOME_NAVIGATION;
	
	
	// Draw Screen Label
	app_drawScreenLabel(&scrLabel);
	
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
	TOUCH_STATE tscState;
	// Initialize array of buttons
	Button buttons[4];
	
	buttons[0].posX = BUTTON_DAY_POS_X;
	buttons[0].posY = BUTTON_DAY_POS_Y;
	buttons[0].width = BUTTON_DAY_WIDTH;
	buttons[0].height = BUTTON_DAY_HEIGHT;
	buttons[0].bitmap = BUTTON_DAY_BITMAP;
	buttons[0].backgroundColor = GLCD_COLOR_PURPLE;
	buttons[0].color = BUTTON_DAY_TEXT_COLOR;
	buttons[0].label = BUTTON_DAY_LABEL;
	buttons[0].navigation = BUTTON_DAY_NAVIGATION;
	
	buttons[1].posX = BUTTON_NIGHT_POS_X;
	buttons[1].posY = BUTTON_NIGHT_POS_Y;
	buttons[1].width = BUTTON_NIGHT_WIDTH;
	buttons[1].height = BUTTON_NIGHT_HEIGHT;
	buttons[1].bitmap = BUTTON_NIGHT_BITMAP;
	buttons[1].backgroundColor = BUTTON_NIGHT_BACKGROUND_COLOR;
	buttons[1].color = BUTTON_NIGHT_TEXT_COLOR;
	buttons[1].label = BUTTON_NIGHT_LABEL;
	buttons[1].navigation = BUTTON_NIGHT_NAVIGATION;
	
	buttons[2].posX = BUTTON_PLAY_POS_X;
	buttons[2].posY = BUTTON_PLAY_POS_Y;
	buttons[2].width = BUTTON_PLAY_WIDTH;
	buttons[2].height = BUTTON_PLAY_HEIGHT;
	buttons[2].bitmap = BUTTON_PLAY_BITMAP;
	buttons[2].backgroundColor = BUTTON_PLAY_BACKGROUND_COLOR;
	buttons[2].color = BUTTON_PLAY_TEXT_COLOR;
	buttons[2].label = BUTTON_PLAY_LABEL;
	buttons[2].navigation = BUTTON_PLAY_NAVIGATION;
	
	buttons[3].posX = BUTTON_MANUAL_POS_X;
	buttons[3].posY = BUTTON_MANUAL_POS_Y;
	buttons[3].width = BUTTON_MANUAL_WIDTH;
	buttons[3].height = BUTTON_MANUAL_HEIGHT;
	buttons[3].bitmap = BUTTON_MANUAL_BITMAP;
	buttons[3].backgroundColor = BUTTON_MANUAL_BACKGROUND_COLOR;
	buttons[3].color = BUTTON_MANUAL_TEXT_COLOR;
	buttons[3].label = BUTTON_MANUAL_LABEL;
	buttons[3].navigation = BUTTON_MANUAL_NAVIGATION;
	
	while(1)
	{
		if (strcmp(*page, "Home") == 0)
		{
			Touch_GetState(&tscState);
			if (tscState.pressed)
			{
				for (i = 0; i < 4; i++)
				{
					if (tscState.x > buttons[i].posX && tscState.x < (buttons[i].width + buttons[i].posX)
					 && tscState.y > buttons[i].posY && tscState.y < (buttons[i].height + buttons[i].posY))
					{
						GLCD_SetFont (&GLCD_Font_16x24);
						GLCD_SetBackgroundColor (GLCD_COLOR_LIGHT_GREY);
						GLCD_SetForegroundColor (GLCD_COLOR_WHITE);
						GLCD_DrawString (20, 40, buttons[i].label);
						
						*page = buttons[i].label;
						
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

// Home Page Navigation
void manualPageNavigation(char **page)
{
	unsigned short i = 0;
	TOUCH_STATE tscState;
	GPIO_InitTypeDef gpio[8];	
	Functionality lightsButtonFunc, doorButtonFunc;
	// Initialize array of buttons
	Button buttons[3];
	
	// ====================== GPIO ======================	
	gpio[0].Pin = GPIO_PIN_7;
	gpio[1].Pin = GPIO_PIN_6;
	gpio[2].Pin = GPIO_PIN_6;
	gpio[3].Pin = GPIO_PIN_4;
	gpio[4].Pin = GPIO_PIN_7;
	gpio[5].Pin = GPIO_PIN_0;
	gpio[6].Pin = GPIO_PIN_6;
	gpio[7].Pin = GPIO_PIN_3;
	
	
	// ====================== Functionality ======================
	lightsButtonFunc.pin = BUTTON_LIGHTS_PIN;
	lightsButtonFunc.state = BUTTON_LIGHTS_STATE;
	
	doorButtonFunc.pin = BUTTON_DOOR_PIN;
	doorButtonFunc.state = BUTTON_DOOR_STATE;
	
	buttons[0].posX = BUTTON_DOOR_POS_X;
	buttons[0].posY = BUTTON_DOOR_POS_Y;
	buttons[0].width = BUTTON_DOOR_WIDTH;
	buttons[0].height = BUTTON_DOOR_HEIGHT;
	buttons[0].bitmap = BUTTON_DOOR_BITMAP;
	buttons[0].backgroundColor = BUTTON_DOOR_BACKGROUND_COLOR;
	buttons[0].color = BUTTON_DOOR_TEXT_COLOR;
	buttons[0].label = BUTTON_DOOR_LABEL;
	buttons[0].navigation = BUTTON_DOOR_NAVIGATION;
	buttons[0].funtionality = doorButtonFunc;
	
	buttons[1].posX = BUTTON_LIGHTS_POS_X;
	buttons[1].posY = BUTTON_LIGHTS_POS_Y;
	buttons[1].width = BUTTON_LIGHTS_WIDTH;
	buttons[1].height = BUTTON_LIGHTS_HEIGHT;
	buttons[1].bitmap = BUTTON_LIGHTS_BITMAP;
	buttons[1].backgroundColor = BUTTON_LIGHTS_BACKGROUND_COLOR;
	buttons[1].color = BUTTON_LIGHTS_TEXT_COLOR;
	buttons[1].label = BUTTON_LIGHTS_LABEL;
	buttons[1].navigation = BUTTON_LIGHTS_NAVIGATION;
	buttons[1].funtionality = lightsButtonFunc;
	
	buttons[2].posX = BUTTON_HOME_POS_X;
	buttons[2].posY = BUTTON_HOME_POS_Y;
	buttons[2].width = BUTTON_HOME_WIDTH;
	buttons[2].height = BUTTON_HOME_HEIGHT;
	buttons[2].bitmap = BUTTON_HOME_BITMAP;
	buttons[2].backgroundColor = BUTTON_HOME_BACKGROUND_COLOR;
	buttons[2].color = BUTTON_HOME_TEXT_COLOR;
	buttons[2].label = BUTTON_HOME_LABEL;
	buttons[2].navigation = BUTTON_HOME_NAVIGATION;
	
	
	while(1)
	{
		if (strcmp(*page, "Manual") == 0)
		{
			Touch_GetState(&tscState);
			if (tscState.pressed)
			{
				for (i = 0; i < 3; i++)
				{
					if (tscState.x > buttons[i].posX && tscState.x < (buttons[i].width + buttons[i].posX)
					 && tscState.y > buttons[i].posY && tscState.y < (buttons[i].height + buttons[i].posY))
					{
						GLCD_SetFont (&GLCD_Font_16x24);
						GLCD_SetBackgroundColor (GLCD_COLOR_LIGHT_GREY);
						GLCD_SetForegroundColor (GLCD_COLOR_WHITE);
						GLCD_DrawString (20, 40, buttons[i].label);
						
						if (buttons[i].navigation)
						{
							*page = buttons[i].label;
						} else {
							if (buttons[i].funtionality.state == 0)
							{
								HAL_GPIO_WritePin(GPIOC, gpio[buttons[i].funtionality.pin].Pin, GPIO_PIN_SET);
								buttons[i].backgroundColor = GLCD_COLOR_GREEN;
								app_drawButton(&buttons[i]);
								buttons[i].funtionality.state = 1;
								wait(50000000);
							} else {
								HAL_GPIO_WritePin(GPIOC, gpio[buttons[i].funtionality.pin].Pin, GPIO_PIN_RESET);
								buttons[i].backgroundColor = GLCD_COLOR_RED;
								app_drawButton(&buttons[i]);
								buttons[i].funtionality.state = 0;
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