#include "GUI_Utility.h"
#include "Board_GLCD.h"
#include "GLCD_Config.h"

extern GLCD_FONT GLCD_Font_16x24;

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
	dayButton.posX = GLCD_SIZE_X/4 - 20;
	dayButton.posY = GLCD_SIZE_Y/4;
	dayButton.width = GLCD_SIZE_X/4;
	dayButton.height = GLCD_SIZE_Y/5;
	dayButton.bitmap = 0;
	dayButton.backgroundColor = GLCD_COLOR_PURPLE;
	dayButton.color = GLCD_COLOR_WHITE;
	dayButton.label = "Day";
	
	nightButton.posX = ((GLCD_SIZE_X/4) * 2) + 20;
	nightButton.posY = GLCD_SIZE_Y/4;
	nightButton.width = GLCD_SIZE_X/4;
	nightButton.height = GLCD_SIZE_Y/5;
	nightButton.bitmap = 0;
	nightButton.backgroundColor = GLCD_COLOR_PURPLE;
	nightButton.color = GLCD_COLOR_WHITE;
	nightButton.label = "Night";
	
	playButton.posX = GLCD_SIZE_X/4 - 20;
	playButton.posY = GLCD_SIZE_Y/4 * 2;
	playButton.width = GLCD_SIZE_X/4;
	playButton.height = GLCD_SIZE_Y/5;
	playButton.bitmap = 0;
	playButton.backgroundColor = GLCD_COLOR_PURPLE;
	playButton.color = GLCD_COLOR_WHITE;
	playButton.label = "Play";
	
	manButton.posX = ((GLCD_SIZE_X/4) * 2) + 20;
	manButton.posY = (GLCD_SIZE_Y/4) * 2;
	manButton.width = GLCD_SIZE_X/4;
	manButton.height = GLCD_SIZE_Y/5;
	manButton.bitmap = 0;
	manButton.backgroundColor = GLCD_COLOR_PURPLE;
	manButton.color = GLCD_COLOR_WHITE;
	manButton.label = "Manual";
	
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
	
	// ====================== Screen Label ======================
	scrLabel.posX = 20;
	scrLabel.posY = 20;
	scrLabel.name = "Manual";
	
	// ====================== Buttons ======================
	doorButton.posX = GLCD_SIZE_X/4 - 20;
	doorButton.posY = GLCD_SIZE_Y/2 - 20;
	doorButton.width = GLCD_SIZE_X/4;
	doorButton.height = GLCD_SIZE_Y/5;
	doorButton.bitmap = 0;
	doorButton.backgroundColor = GLCD_COLOR_RED;
	doorButton.color = GLCD_COLOR_WHITE;
	doorButton.label = "Door";
	
	lightsButton.posX = ((GLCD_SIZE_X/4) * 2) + 20;
	lightsButton.posY = GLCD_SIZE_Y/2 - 20;
	lightsButton.width = GLCD_SIZE_X/4;
	lightsButton.height = GLCD_SIZE_Y/5;
	lightsButton.bitmap = 0;
	lightsButton.backgroundColor = GLCD_COLOR_GREEN;
	lightsButton.color = GLCD_COLOR_WHITE;
	lightsButton.label = "Lights";
	
	homeButton.posX = GLCD_SIZE_X/2 - ((GLCD_SIZE_X/4)/2);
	homeButton.posY = (GLCD_SIZE_Y/5 * 3) + 40;
	homeButton.width = GLCD_SIZE_X/4;
	homeButton.height = GLCD_SIZE_Y/5;
	homeButton.bitmap = 0;
	homeButton.backgroundColor = GLCD_COLOR_YELLOW;
	homeButton.color = GLCD_COLOR_BLACK;
	homeButton.label = "Home";
	
	
	// Draw Screen Label
	app_drawScreenLabel(&scrLabel);
	
	// Draw Door Button
	app_drawButton(&doorButton);
	
	// Draw Lights Button
	app_drawButton(&lightsButton);
	
	// Draw Home Button
	app_drawButton(&homeButton);
	
}