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
#define BUTTON_DOOR_PIN 2
#define BUTTON_DOOR_STATE 0

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

// DAY PROGRAM CLOCK Properties
#define DAY_PROGRAM_CLOCK_POS_X GLCD_SIZE_X/4 + 20
#define DAY_PROGRAM_CLOCK_POS_Y 70
#define DAY_PROGRAM_CLOCK_MIN 21
#define DAY_PROGRAM_CLOCK_HOUR 11

// NIGHT PROGRAM CLOCK Properties
#define NIGHT_PROGRAM_CLOCK_POS_X GLCD_SIZE_X/4 + 20
#define NIGHT_PROGRAM_CLOCK_POS_Y 70
#define NIGHT_PROGRAM_CLOCK_MIN 22
#define NIGHT_PROGRAM_CLOCK_HOUR 11


// WATER Bargraph
#define WATER_BARGRAPH_POS_X GLCD_SIZE_X/4 - 20
#define WATER_BARGRAPH_POS_Y GLCD_SIZE_Y/5 * 4 - 10
#define WATER_BARGRAPH_WIDTH GLCD_SIZE_X/2 + 40
#define WATER_BARGRAPH_HEIGHT 10
#define WATER_BARGRAPH_LABEL "Water"

// FOOD Bargraph
#define FOOD_BARGRAPH_POS_X GLCD_SIZE_X/4 - 20
#define FOOD_BARGRAPH_POS_Y GLCD_SIZE_Y/5 * 4 + 10
#define FOOD_BARGRAPH_WIDTH GLCD_SIZE_X/2 + 40
#define FOOD_BARGRAPH_HEIGHT 10
#define FOOD_BARGRAPH_LABEL "Food"

void drawHomePage(char **page);

void drawManualPage(char **page);

void drawDayProgramPage(char **page);

void drawNightProgramPage(char **page);

void drawPlayProgramPage(char **page);

