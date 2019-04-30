#include "stm32f7xx_hal.h"

#define DAY 8640000; /* 10 ms ticks in a day */

// PLAY Button Properties
#define BUTTON_PLAY_POS_X GLCD_SIZE_X/4 - 20
#define BUTTON_PLAY_POS_Y GLCD_SIZE_Y/4 * 2
#define BUTTON_PLAY_WIDTH GLCD_SIZE_X/4
#define BUTTON_PLAY_HEIGHT GLCD_SIZE_Y/5
#define BUTTON_PLAY_LABEL "Play"
#define BUTTON_PLAY_NAVIGATION 1

// MANUAL Button Properties
#define BUTTON_MANUAL_POS_X ((GLCD_SIZE_X/4) * 2) + 20
#define BUTTON_MANUAL_POS_Y (GLCD_SIZE_Y/4) * 2
#define BUTTON_MANUAL_WIDTH GLCD_SIZE_X/4
#define BUTTON_MANUAL_HEIGHT GLCD_SIZE_Y/5
#define BUTTON_MANUAL_LABEL "Manual"
#define BUTTON_MANUAL_NAVIGATION 1

// DOOR Button Properties
#define BUTTON_DOOR_POS_X GLCD_SIZE_X/4 - 20
#define BUTTON_DOOR_POS_Y GLCD_SIZE_Y/3 - 30
#define BUTTON_DOOR_WIDTH GLCD_SIZE_X/4
#define BUTTON_DOOR_HEIGHT GLCD_SIZE_Y/5
#define BUTTON_DOOR_LABEL "Door"
#define BUTTON_DOOR_NAVIGATION 0
#define BUTTON_DOOR_PIN 6
#define BUTTON_DOOR_STATE 0

// TREAT Button Properties
#define BUTTON_TREAT_POS_X GLCD_SIZE_X/4 - 80
#define BUTTON_TREAT_POS_Y (GLCD_SIZE_Y/5 * 3) + 40
#define BUTTON_TREAT_WIDTH GLCD_SIZE_X/4
#define BUTTON_TREAT_HEIGHT GLCD_SIZE_Y/5
#define BUTTON_TREAT_LABEL "Treat"
#define BUTTON_TREAT_NAVIGATION 0
#define BUTTON_TREAT_PIN 7
#define BUTTON_TREAT_STATE 0

// ALARM Button Properties
#define BUTTON_ALARM_POS_X ((GLCD_SIZE_X/4) * 2) + 80
#define BUTTON_ALARM_POS_Y (GLCD_SIZE_Y/5 * 3) + 40
#define BUTTON_ALARM_WIDTH GLCD_SIZE_X/4
#define BUTTON_ALARM_HEIGHT GLCD_SIZE_Y/5
#define BUTTON_ALARM_LABEL "Alarm"
#define BUTTON_ALARM_NAVIGATION 0
#define BUTTON_ALARM_PIN 5
#define BUTTON_ALARM_STATE 0

// LIGHTS Button Properties
#define BUTTON_LIGHTS_POS_X ((GLCD_SIZE_X/4) * 2) + 20
#define BUTTON_LIGHTS_POS_Y GLCD_SIZE_Y/3 - 30
#define BUTTON_LIGHTS_WIDTH GLCD_SIZE_X/4
#define BUTTON_LIGHTS_HEIGHT GLCD_SIZE_Y/5
#define BUTTON_LIGHTS_LABEL "Lights"
#define BUTTON_LIGHTS_NAVIGATION 0
#define BUTTON_LIGHTS_PIN 0
#define BUTTON_LIGHTS_STATE 0

// HEATING Button Properties
#define BUTTON_HEATING_POS_X ((GLCD_SIZE_X/4) * 2) + 20
#define BUTTON_HEATING_POS_Y GLCD_SIZE_Y/3 + 25
#define BUTTON_HEATING_WIDTH GLCD_SIZE_X/4
#define BUTTON_HEATING_HEIGHT GLCD_SIZE_Y/5
#define BUTTON_HEATING_LABEL "Heating"
#define BUTTON_HEATING_NAVIGATION 0
#define BUTTON_HEATING_PIN 1
#define BUTTON_HEATING_STATE 0

// FAN Button Properties
#define BUTTON_FAN_POS_X GLCD_SIZE_X/4 - 20
#define BUTTON_FAN_POS_Y GLCD_SIZE_Y/3 + 25
#define BUTTON_FAN_WIDTH GLCD_SIZE_X/4
#define BUTTON_FAN_HEIGHT GLCD_SIZE_Y/5
#define BUTTON_FAN_LABEL "Fan"
#define BUTTON_FAN_NAVIGATION 0
#define BUTTON_FAN_PIN 2
#define BUTTON_FAN_STATE 0

// CAMERA Button Properties
#define BUTTON_CAMERA_POS_X ((GLCD_SIZE_X/4) * 2) + 80
#define BUTTON_CAMERA_POS_Y (GLCD_SIZE_Y/5 * 3) + 40
#define BUTTON_CAMERA_WIDTH GLCD_SIZE_X/4
#define BUTTON_CAMERA_HEIGHT GLCD_SIZE_Y/5
#define BUTTON_CAMERA_LABEL "Camera"
#define BUTTON_CAMERA_NAVIGATION 0
#define BUTTON_CAMERA_PIN 8
#define BUTTON_CAMERA_STATE 0

// HOME Button Properties
#define BUTTON_HOME_POS_X GLCD_SIZE_X/2 - ((GLCD_SIZE_X/4)/2)
#define BUTTON_HOME_POS_Y (GLCD_SIZE_Y/5 * 3) + 40
#define BUTTON_HOME_WIDTH GLCD_SIZE_X/4
#define BUTTON_HOME_HEIGHT GLCD_SIZE_Y/5
#define BUTTON_HOME_LABEL "Home"
#define BUTTON_HOME_NAVIGATION 1

// CLOCK Properties
#define CLOCK_POS_X GLCD_SIZE_X/4 + 20
#define CLOCK_POS_Y 20
#define CLOCK_SEC 30
#define CLOCK_MIN 20
#define CLOCK_HOUR 11

// WATER Bargraph
#define WATER_BARGRAPH_POS_X GLCD_SIZE_X/4 - 20
#define WATER_BARGRAPH_POS_Y GLCD_SIZE_Y/5 * 4 - 10
#define WATER_BARGRAPH_WIDTH 40
#define WATER_BARGRAPH_HEIGHT 10
#define WATER_BARGRAPH_LABEL "Water"

// FOOD Bargraph
#define FOOD_BARGRAPH_POS_X GLCD_SIZE_X/4 - 20
#define FOOD_BARGRAPH_POS_Y GLCD_SIZE_Y/5 * 4 + 10
#define FOOD_BARGRAPH_WIDTH GLCD_SIZE_X/2 + 40
#define FOOD_BARGRAPH_HEIGHT 10
#define FOOD_BARGRAPH_LABEL "Food"

/**
* Function to draw the home page
*/
void drawHomePage(char **page);

/**
* Function to draw the manual page
*/
void drawManualPage(char **page);

/**
* This struct contains properties related to a FUNCTIONALITY of a BUTTON
*/
typedef struct
{
	unsigned char pin;
	
	GPIO_TypeDef *base;
	
	unsigned char state;
	
	unsigned char *type;
	
}Functionality;
/**
* This struct contains properties related to a BUTTON
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
* This struct contains properties related to a CLOCK
*/
typedef struct
{
	unsigned short posX;
	
	unsigned short posY;
	
	unsigned short hour;
	
	unsigned short minute;
	
	unsigned short second;
	
	unsigned char programRunning;
	
	unsigned short tic;
	
	unsigned short toc;
	
	unsigned int elapsed_t;
	
}Clock;

/**
* This struct contains properties related to a SCREEN LABLE
*/
typedef struct
{
	unsigned short posX;
	
	unsigned short posY;
	
	char *name;
	
}ScreenLabel;

/**
* This struct contains properties related to a BARGRAPH
*/
typedef struct
{
	unsigned short posX;
	
	unsigned short posY; 
	
	unsigned short width; 
	
	unsigned short height; 
	
	unsigned short background;
	
	char *label;
	
}Bargraph;


/**
* This struct contains properties related to a PROGRAM (Day, Night, Play)
*/
typedef struct
{
	unsigned short hour;
	
	unsigned short minute;
	
	unsigned char programRunning;
	
	GPIO_InitTypeDef **pin;
	
}Program;


// Draws a button with a label on top of it
void app_drawButton(Button *btn);

// A milisecond delay function
void milDelay(int dl);

// Turn Wheel ON
void turnOnWheel(void);

// Turn Wheel OFF
void turnOffWheel(void);

// Buzz
void buzz(void);

// Configure Analog to Digital Converter
void ConfigureADC(void);

// Draws a clock
void app_drawClock();

// Draws the screen label
void app_drawScreenLabel(ScreenLabel *scrLbl);

// Draws the bargraph
void app_drawBargraph(Bargraph *bargraph);

// Clock functionality
void app_clockTicToc();

// User input Handler
void app_userInputHandle(char **page, short numOfButtons, Button **buttons);

// Home page specific logic
void app_homePageSpecific(void);

// Handle sensor type
void app_handleSensor(Button *button,  short pin);

// Turn ON the FAN
void turnOnFan(void);

// Turn OFF the FAN
void turnOffFan(void);

// Stop treat
void app_stopTreat(void);

// Open Door (Used for both the door and starting the treat)
void app_openDoor(Button *button, short pin);

// Close Door (Uses Mutex to hold the resource to make sure the door is clear)
void app_closeDoor();

// Update water level
void app_updateWaterLevel(Bargraph *bargraph);

// Update food level
void app_updateFoodLevel(Bargraph *bargraph);

// Send a request to the tempreture sensor for getting a value
void DHT11Start(GPIO_InitTypeDef* pin);	

// Checking the response of the tempreture sensor
void checkResponse(GPIO_InitTypeDef* pin);

// Reading the data of the tempreture sensor
int readData(GPIO_InitTypeDef* pin);

// Update Tempreture
void app_updateTempreture();