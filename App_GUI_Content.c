#include "GUI_Utility.h"
#include "Board_GLCD.h"
#include "GLCD_Config.h"

extern GLCD_FONT GLCD_Font_16x24;

void drawHomeScreen(void)
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
	dayButton.label = "Day";
	
	nightButton.posX = ((GLCD_SIZE_X/4) * 2) + 20;
	nightButton.posY = GLCD_SIZE_Y/4;
	nightButton.width = GLCD_SIZE_X/4;
	nightButton.height = GLCD_SIZE_Y/5;
	nightButton.bitmap = 0;
	nightButton.label = "Night";
	
	playButton.posX = GLCD_SIZE_X/4 - 20;
	playButton.posY = GLCD_SIZE_Y/4 * 2;
	playButton.width = GLCD_SIZE_X/4;
	playButton.height = GLCD_SIZE_Y/5;
	playButton.bitmap = 0;
	playButton.label = "Play";
	
	manButton.posX = ((GLCD_SIZE_X/4) * 2) + 20;
	manButton.posY = (GLCD_SIZE_Y/4) * 2;
	manButton.width = GLCD_SIZE_X/4;
	manButton.height = GLCD_SIZE_Y/5;
	manButton.bitmap = 0;
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