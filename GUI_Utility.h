#include "stm32f7xx_hal_gpio.h"
#define DAY 8640000; /* 10 ms ticks in a day */


/**
* This struct contains properties related to a functionality ( concept level functionality )
*/
typedef struct
{
	unsigned char pin;
	
	unsigned char state;
}Functionality;
/**
* This struct contains properties related to a button ( concept level button )
*/
typedef struct
{
	unsigned short posX;
	
	unsigned short posY; 
	
	unsigned short width; 
	
	unsigned short height; 
	
	char *label;
	
	char navigation;
	
	Functionality *funtionality;
	
}Button;

/**
* This struct contains properties related to a Clock ( concept level clock )
*/
typedef struct
{
	unsigned short posX;
	
	unsigned short posY;
	
	unsigned short hour;
	
	unsigned short minute;
	
	unsigned short second;
	
	unsigned short tic;
	
	unsigned short toc;
	
	unsigned int elapsed_t;
	
}Clock;

/**
* This struct contains properties related to a screen label ( concept level screen label )
*/
typedef struct
{
	unsigned short posX;
	
	unsigned short posY;
	
	char *name;
	
}ScreenLabel;

/**
* This struct contains properties related to a bargraph ( concept level screen bargraph )
*/
typedef struct
{
	unsigned short posX;
	
	unsigned short posY; 
	
	unsigned short width; 
	
	unsigned short height; 
	
	char *label;
	
}Bargraph;


// Draws a button with a label on top of it
void app_drawButton(Button *btn);

// Draws a clock
void app_drawClock(Clock *clk);

// Draw program time
void app_drawProgramClock(Clock *clk);

// Draw program time edit
void app_drawProgramTimeEdit(short xPos, short yPos, Clock *clock);

// Draws the screen label
void app_drawScreenLabel(ScreenLabel *scrLbl);

// Draws the bargraph
void app_drawBargraph(Bargraph *bargraph);

// Clock functionality
void app_clockTicToc(Clock *clock);

// User input Handler
void app_userInputHandle(char **page, short numOfButtons, Button **buttons, GPIO_InitTypeDef **pins, Clock *clock);

// Wait
void wait(int delay);

// Open Door
void app_openDoor(void);

// Close Door
void app_closeDoor(void);