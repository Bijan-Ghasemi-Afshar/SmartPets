/*-----------------------------------------------------------------------------
 * Name:    GUI_Utility.h
 * Purpose: The core logic of the SmartPets app.
 * Rev.:    1.0.0
 * Authors:    Bijan Ghasemi Afshar - Richard Sabiers
 * Date: April 2019
 *-----------------------------------------------------------------------------*/

#include "stm32f7xx_hal.h"
#include "cmsis_os.h"

/*---------------------- The number of 10 miliseconds in a day ---------------*/
#define DAY 8640000; /* 10 ms ticks in a day */

/*---------------------- PLAY Button Properties ---------------*/
#define BUTTON_PLAY_POS_X GLCD_SIZE_X/4 - 20
#define BUTTON_PLAY_POS_Y GLCD_SIZE_Y/4 * 2
#define BUTTON_PLAY_WIDTH GLCD_SIZE_X/4
#define BUTTON_PLAY_HEIGHT GLCD_SIZE_Y/5
#define BUTTON_PLAY_LABEL "Play"
#define BUTTON_PLAY_NAVIGATION 1

/*---------------------- MANUAL Button Properties ---------------*/
#define BUTTON_MANUAL_POS_X ((GLCD_SIZE_X/4) * 2) + 20
#define BUTTON_MANUAL_POS_Y (GLCD_SIZE_Y/4) * 2
#define BUTTON_MANUAL_WIDTH GLCD_SIZE_X/4
#define BUTTON_MANUAL_HEIGHT GLCD_SIZE_Y/5
#define BUTTON_MANUAL_LABEL "Manual"
#define BUTTON_MANUAL_NAVIGATION 1

/*---------------------- DOOR Button Properties ---------------*/
#define BUTTON_DOOR_POS_X GLCD_SIZE_X/4 - 20
#define BUTTON_DOOR_POS_Y GLCD_SIZE_Y/3 - 30
#define BUTTON_DOOR_WIDTH GLCD_SIZE_X/4
#define BUTTON_DOOR_HEIGHT GLCD_SIZE_Y/5
#define BUTTON_DOOR_LABEL "Door"
#define BUTTON_DOOR_NAVIGATION 0
#define BUTTON_DOOR_PIN 6
#define BUTTON_DOOR_STATE 0

/*---------------------- TREAT Button Properties ---------------*/
#define BUTTON_TREAT_POS_X GLCD_SIZE_X/4 - 80
#define BUTTON_TREAT_POS_Y (GLCD_SIZE_Y/5 * 3) + 40
#define BUTTON_TREAT_WIDTH GLCD_SIZE_X/4
#define BUTTON_TREAT_HEIGHT GLCD_SIZE_Y/5
#define BUTTON_TREAT_LABEL "Treat"
#define BUTTON_TREAT_NAVIGATION 0
#define BUTTON_TREAT_PIN 7
#define BUTTON_TREAT_STATE 0

/*---------------------- ALARM Button Properties ---------------*/
#define BUTTON_ALARM_POS_X ((GLCD_SIZE_X/4) * 2) + 80
#define BUTTON_ALARM_POS_Y (GLCD_SIZE_Y/5 * 3) + 40
#define BUTTON_ALARM_WIDTH GLCD_SIZE_X/4
#define BUTTON_ALARM_HEIGHT GLCD_SIZE_Y/5
#define BUTTON_ALARM_LABEL "Alarm"
#define BUTTON_ALARM_NAVIGATION 0
#define BUTTON_ALARM_PIN 5
#define BUTTON_ALARM_STATE 0

/*---------------------- LIGHTS Button Properties ---------------*/
#define BUTTON_LIGHTS_POS_X ((GLCD_SIZE_X/4) * 2) + 20
#define BUTTON_LIGHTS_POS_Y GLCD_SIZE_Y/3 - 30
#define BUTTON_LIGHTS_WIDTH GLCD_SIZE_X/4
#define BUTTON_LIGHTS_HEIGHT GLCD_SIZE_Y/5
#define BUTTON_LIGHTS_LABEL "Lights"
#define BUTTON_LIGHTS_NAVIGATION 0
#define BUTTON_LIGHTS_PIN 0
#define BUTTON_LIGHTS_STATE 0

/*---------------------- HEATING Button Properties ---------------*/
#define BUTTON_HEATING_POS_X ((GLCD_SIZE_X/4) * 2) + 20
#define BUTTON_HEATING_POS_Y GLCD_SIZE_Y/3 + 25
#define BUTTON_HEATING_WIDTH GLCD_SIZE_X/4
#define BUTTON_HEATING_HEIGHT GLCD_SIZE_Y/5
#define BUTTON_HEATING_LABEL "Heating"
#define BUTTON_HEATING_NAVIGATION 0
#define BUTTON_HEATING_PIN 1
#define BUTTON_HEATING_STATE 0

/*---------------------- FAN Button Properties ---------------*/
#define BUTTON_FAN_POS_X GLCD_SIZE_X/4 - 20
#define BUTTON_FAN_POS_Y GLCD_SIZE_Y/3 + 25
#define BUTTON_FAN_WIDTH GLCD_SIZE_X/4
#define BUTTON_FAN_HEIGHT GLCD_SIZE_Y/5
#define BUTTON_FAN_LABEL "Fan"
#define BUTTON_FAN_NAVIGATION 0
#define BUTTON_FAN_PIN 2
#define BUTTON_FAN_STATE 0

/*---------------------- CAMERA Button Properties ---------------*/
#define BUTTON_CAMERA_POS_X ((GLCD_SIZE_X/4) * 2) + 80
#define BUTTON_CAMERA_POS_Y (GLCD_SIZE_Y/5 * 3) + 40
#define BUTTON_CAMERA_WIDTH GLCD_SIZE_X/4
#define BUTTON_CAMERA_HEIGHT GLCD_SIZE_Y/5
#define BUTTON_CAMERA_LABEL "Camera"
#define BUTTON_CAMERA_NAVIGATION 0
#define BUTTON_CAMERA_PIN 8
#define BUTTON_CAMERA_STATE 0

/*---------------------- HOME Button Properties ---------------*/
#define BUTTON_HOME_POS_X GLCD_SIZE_X/2 - ((GLCD_SIZE_X/4)/2)
#define BUTTON_HOME_POS_Y (GLCD_SIZE_Y/5 * 3) + 40
#define BUTTON_HOME_WIDTH GLCD_SIZE_X/4
#define BUTTON_HOME_HEIGHT GLCD_SIZE_Y/5
#define BUTTON_HOME_LABEL "Home"
#define BUTTON_HOME_NAVIGATION 1

/*---------------------- CLOCK Properties ---------------*/
#define CLOCK_POS_X GLCD_SIZE_X/4 + 20
#define CLOCK_POS_Y 20
#define CLOCK_SEC 30
#define CLOCK_MIN 20
#define CLOCK_HOUR 11

/*---------------------- WATER Bargraph Properties ---------------*/
#define WATER_BARGRAPH_POS_X GLCD_SIZE_X/4 - 20
#define WATER_BARGRAPH_POS_Y GLCD_SIZE_Y/5 * 4 - 10
#define WATER_BARGRAPH_WIDTH 40
#define WATER_BARGRAPH_HEIGHT 10
#define WATER_BARGRAPH_LABEL "Water"

/*---------------------- FOOD Bargraph Properties ---------------*/
#define FOOD_BARGRAPH_POS_X GLCD_SIZE_X/4 - 20
#define FOOD_BARGRAPH_POS_Y GLCD_SIZE_Y/5 * 4 + 10
#define FOOD_BARGRAPH_WIDTH GLCD_SIZE_X/2 + 40
#define FOOD_BARGRAPH_HEIGHT 10
#define FOOD_BARGRAPH_LABEL "Food"

/* Mutex definitions */
osMutexId stdio_mutex;
osMutexDef(stdio_mutex);

/* Task id for threading */
osThreadId tid_clock;

/* Button Functionality definition */
typedef struct
{
	unsigned char pin;
	
	GPIO_TypeDef *base;
	
	unsigned char state;
	
	unsigned char *type;
	
}Functionality;

/* Button definition */
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

/* Clock & Program definition */
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

/* Screen Label definition */
typedef struct
{
	unsigned short posX;
	
	unsigned short posY;
	
	char *name;
	
}ScreenLabel;

/* Bargraph definition */
typedef struct
{
	unsigned short posX;
	
	unsigned short posY; 
	
	unsigned short width; 
	
	unsigned short height; 
	
	unsigned short background;
	
	char *label;
	
}Bargraph;


/* Program definition */
typedef struct
{
	unsigned short hour;
	
	unsigned short minute;
	
	unsigned char programRunning;
	
	GPIO_InitTypeDef **pin;
	
}Program;

/**
  \fn          void initializePins(void)
  \brief       Initializes all used pins.
*/
void initializePins(void);

/**
  \fn          void drawHomePage(char **page)
  \brief       Draws the home page GUI.
  \param[in]   page		The name of the page.
*/
void drawHomePage(char **page);

/**
  \fn          void drawManualPage(char **page)
  \brief       Draws the manual page GUI.
  \param[in]   page		The name of the page.
*/
void drawManualPage(char **page);

/**
  \fn          void app_drawButton(Button *btn)
  \brief       Draws a button on the GLCD screen.
  \param[in]   btn   A button struct to be drawn.
*/
void app_drawButton(Button *btn);

/**
  \fn          void milDelay(int dl)
  \brief       Function for having milisecond delays.
  \param[in]   dl   Number of miliseconds for delay
*/
void milDelay(int dl);

/**
  \fn          void turnOnWheel(void)
  \brief       Function for turning on the wheel for the hamster.
*/
void turnOnWheel(void);

/**
  \fn          void turnOffWheel(void)
  \brief       Function for turning off the wheel for the hamster.
*/
void turnOffWheel(void);

/**
  \fn          void buzz(void)
  \brief       Function for setting a quick buzz sound indicating a program change.
*/
void buzz(void);

/**
  \fn          void ConfigureADC(void)
  \brief       Function for configuring the Analog to Digital Converter.
*/
void ConfigureADC(void);

/**
  \fn          void app_drawClock(void)
  \brief       Function for drawing the clock on the GLCD screen.
*/
void app_drawClock(void);

/**
  \fn          void app_drawScreenLabel(ScreenLabel *scrLbl)
  \brief       Function for drawing a screen label on the GLCD screen.
  \param[in]   scrLbl   A screen label sctruct to be drawn on the screen.
*/
void app_drawScreenLabel(ScreenLabel *scrLbl);

/**
  \fn          void app_drawBargraph(Bargraph *bargraph)
  \brief       Function for drawing a bargraph on the GLCD screen.
  \param[in]   bargraph   A bargraph sctruct to be drawn on the screen.
*/
void app_drawBargraph(Bargraph *bargraph);

/**
  \fn          void app_clockTicToc(void const *argument)
  \brief       Functionality of the clock (Threaded)
  \param[in]   argument   Event for this threaded task.
*/
void app_clockTicToc(void const *argument);

/**
  \fn          void app_userInputHandle(char **page, short numOfButtons, Button **buttons)
  \brief       Function for handling user input as touch on a touch screen.
  \param[in]   page   The current page that is rendered.
	\param[in]   numOfButtons   The number of buttons rendered on the page.
	\param[in]   buttons   An array of buttons on the current page.
*/
void app_userInputHandle(char **page, short numOfButtons, Button **buttons);

/**
  \fn          void app_homePageSpecific()
  \brief       Function for handling home page specific functionality (tempreture, food, water level)
*/
void app_homePageSpecific();

/**
  \fn          void app_handleSensor(Button *button,  short pin)
  \brief       Function for handling the logic of each type of sensor (digital, pwm, etc.)
  \param[in]   button   The button that has been touched.
	\param[in]   pin   The pin associated with that button
*/
void app_handleSensor(Button *button,  short pin);

/**
  \fn          void turnOnFan(void)
  \brief       Function for turning on the fan for the hamster
*/
void turnOnFan(void);

/**
  \fn          void turnOffFan(void)
  \brief       Function for turning off the fan for the hamster
*/
void turnOffFan(void);

/**
  \fn          void app_stopTreat(void)
  \brief       Function for setting back the treat platform to its original position
*/
void app_stopTreat(void);

/**
  \fn          void app_openDoor(Button *button, short pin)
  \brief       Function for opening the door of the cage and treating the hamster
  \param[in]   button   The button that has been touched.
	\param[in]   pin   The pin associated with that button
*/
void app_openDoor(Button *button, short pin);

/**
  \fn          void app_closeDoor(void)
  \brief       Function for closing the door of the cage (Uses mutex to lock the source if hamster is in the way of the door)
*/
void app_closeDoor(void);

/**
  \fn          void app_updateWaterLevel(Bargraph *bargraph)
  \brief       Function for the water bargraph
  \param[in]   bargraph   The water bargraph struct
*/
void app_updateWaterLevel(Bargraph *bargraph);

/**
  \fn          void app_updateFoodLevel(Bargraph *bargraph)
  \brief       Function for the food bargraph
  \param[in]   bargraph   The food bargraph struct
*/
void app_updateFoodLevel(Bargraph *bargraph);

/**
  \fn          void DHT11Start(GPIO_InitTypeDef* pin)
  \brief       Function for sending a request to tempreture sensor to get data.
  \param[in]   pin   The pin for the tempreture sensor
*/
void DHT11Start(GPIO_InitTypeDef* pin);	

/**
  \fn          void checkResponse(GPIO_InitTypeDef* pin)
  \brief       Function for checking the response of the tempreture sensor
  \param[in]   pin   The pin for the tempreture sensor
*/
void checkResponse(GPIO_InitTypeDef* pin);

/**
  \fn          void readData(GPIO_InitTypeDef* pin)
  \brief       Function for reading the data of the tempreture sensor
  \param[in]   pin   The pin for the tempreture sensor
*/
int readData(GPIO_InitTypeDef* pin);

/**
  \fn          void app_updateTempreture(void)
  \brief       Function for updating the tempreture sensor and acting as a thermostat for fan and heating
*/
void app_updateTempreture(void);

/* Define Threads for clock functionality */
osThreadDef(app_clockTicToc, osPriorityAboveNormal, 1, 0);

