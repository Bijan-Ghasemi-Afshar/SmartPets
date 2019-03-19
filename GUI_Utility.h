/**
* This struct contains properties related to a button ( concept level button )
*/
typedef struct
{
	unsigned short posX;
	
	unsigned short posY; 
	
	unsigned short width; 
	
	unsigned short height; 
	
	const short *bitmap;
	
	unsigned int backgroundColor;
	
	unsigned int color;
	
	char *label;
	
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
	
	const short *bitmap;
	
	char *label;
	
}Bargraph;


// Draws a button with a label on top of it
void app_drawButton(Button *btn);

// Draws a clock
void app_drawClock(Clock *clk);

// Draws the screen label
void app_drawScreenLabel(ScreenLabel *scrLbl);

// Draws the bargraph
void app_drawBargraph(Bargraph *bargraph);