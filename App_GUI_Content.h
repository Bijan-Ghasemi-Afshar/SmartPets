// DAY Button Properties
#define BUTTON_DAY_POS_X GLCD_SIZE_X/4 - 20
#define BUTTON_DAY_POS_Y GLCD_SIZE_Y/4
#define BUTTON_DAY_WIDTH GLCD_SIZE_X/4
#define BUTTON_DAY_HEIGHT GLCD_SIZE_Y/5
#define BUTTON_DAY_BITMAP 0
#define BUTTON_DAY_BACKGROUND_COLOR GLCD_COLOR_PURPLE
#define BUTTON_DAY_TEXT_COLOR GLCD_COLOR_WHITE
#define BUTTON_DAY_LABEL "Day"
#define BUTTON_DAY_NAVIGATION 1

// NIGHT Button Properties
#define BUTTON_NIGHT_POS_X ((GLCD_SIZE_X/4) * 2) + 20
#define BUTTON_NIGHT_POS_Y GLCD_SIZE_Y/4
#define BUTTON_NIGHT_WIDTH GLCD_SIZE_X/4
#define BUTTON_NIGHT_HEIGHT GLCD_SIZE_Y/5
#define BUTTON_NIGHT_BITMAP 0
#define BUTTON_NIGHT_BACKGROUND_COLOR GLCD_COLOR_PURPLE
#define BUTTON_NIGHT_TEXT_COLOR GLCD_COLOR_WHITE
#define BUTTON_NIGHT_LABEL "Night"
#define BUTTON_NIGHT_NAVIGATION 1

// PLAY Button Properties
#define BUTTON_PLAY_POS_X GLCD_SIZE_X/4 - 20
#define BUTTON_PLAY_POS_Y GLCD_SIZE_Y/4 * 2
#define BUTTON_PLAY_WIDTH GLCD_SIZE_X/4
#define BUTTON_PLAY_HEIGHT GLCD_SIZE_Y/5
#define BUTTON_PLAY_BITMAP 0
#define BUTTON_PLAY_BACKGROUND_COLOR GLCD_COLOR_PURPLE
#define BUTTON_PLAY_TEXT_COLOR GLCD_COLOR_WHITE
#define BUTTON_PLAY_LABEL "Play"
#define BUTTON_PLAY_NAVIGATION 1

// MANUAL Button Properties
#define BUTTON_MANUAL_POS_X ((GLCD_SIZE_X/4) * 2) + 20
#define BUTTON_MANUAL_POS_Y (GLCD_SIZE_Y/4) * 2
#define BUTTON_MANUAL_WIDTH GLCD_SIZE_X/4
#define BUTTON_MANUAL_HEIGHT GLCD_SIZE_Y/5
#define BUTTON_MANUAL_BITMAP 0
#define BUTTON_MANUAL_BACKGROUND_COLOR GLCD_COLOR_PURPLE
#define BUTTON_MANUAL_TEXT_COLOR GLCD_COLOR_WHITE
#define BUTTON_MANUAL_LABEL "Manual"
#define BUTTON_MANUAL_NAVIGATION 1

// DOOR Button Properties
#define BUTTON_DOOR_POS_X GLCD_SIZE_X/4 - 20
#define BUTTON_DOOR_POS_Y GLCD_SIZE_Y/2 - 20
#define BUTTON_DOOR_WIDTH GLCD_SIZE_X/4
#define BUTTON_DOOR_HEIGHT GLCD_SIZE_Y/5
#define BUTTON_DOOR_BITMAP 0
#define BUTTON_DOOR_BACKGROUND_COLOR GLCD_COLOR_RED
#define BUTTON_DOOR_TEXT_COLOR GLCD_COLOR_WHITE
#define BUTTON_DOOR_LABEL "Door"
#define BUTTON_DOOR_NAVIGATION 0
#define BUTTON_DOOR_PIN 2
#define BUTTON_DOOR_STATE 0

// LIGHTS Button Properties
#define BUTTON_LIGHTS_POS_X ((GLCD_SIZE_X/4) * 2) + 20
#define BUTTON_LIGHTS_POS_Y GLCD_SIZE_Y/2 - 20
#define BUTTON_LIGHTS_WIDTH GLCD_SIZE_X/4
#define BUTTON_LIGHTS_HEIGHT GLCD_SIZE_Y/5
#define BUTTON_LIGHTS_BITMAP 0
#define BUTTON_LIGHTS_BACKGROUND_COLOR GLCD_COLOR_RED
#define BUTTON_LIGHTS_TEXT_COLOR GLCD_COLOR_WHITE
#define BUTTON_LIGHTS_LABEL "Lights"
#define BUTTON_LIGHTS_NAVIGATION 0
#define BUTTON_LIGHTS_PIN 0
#define BUTTON_LIGHTS_STATE 0

// HOME Button Properties
#define BUTTON_HOME_POS_X GLCD_SIZE_X/2 - ((GLCD_SIZE_X/4)/2)
#define BUTTON_HOME_POS_Y (GLCD_SIZE_Y/5 * 3) + 40
#define BUTTON_HOME_WIDTH GLCD_SIZE_X/4
#define BUTTON_HOME_HEIGHT GLCD_SIZE_Y/5
#define BUTTON_HOME_BITMAP 0
#define BUTTON_HOME_BACKGROUND_COLOR GLCD_COLOR_YELLOW
#define BUTTON_HOME_TEXT_COLOR GLCD_COLOR_BLACK
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
#define WATER_BARGRAPH_WIDTH GLCD_SIZE_X/2 + 40
#define WATER_BARGRAPH_HEIGHT 10
#define WATER_BARGRAPH_BITMAP 0
#define WATER_BARGRAPH_LABEL "Water"

// FOOD Bargraph
#define FOOD_BARGRAPH_POS_X GLCD_SIZE_X/4 - 20
#define FOOD_BARGRAPH_POS_Y GLCD_SIZE_Y/5 * 4 + 10
#define FOOD_BARGRAPH_WIDTH GLCD_SIZE_X/2 + 40
#define FOOD_BARGRAPH_HEIGHT 10
#define FOOD_BARGRAPH_BITMAP 0
#define FOOD_BARGRAPH_LABEL "Food"


void wait(int delay);

void drawHomePage(void);

void drawManualPage(void);

void drawDayProgramPage(void);

void drawNightProgramPage(void);

void drawPlayProgramPage(void);

void homePageNavigation(char **page);

void manualPageNavigation(char **page);

void dayPageNavigation(char **page);

void nightPageNavigation(char **page);

void playPageNavigation(char **page);
