#include "GUI_Utility.h"
#include "Board_GLCD.h"
#include "GLCD_Config.h"
#include <stdio.h>

extern GLCD_FONT GLCD_Font_6x8;
extern GLCD_FONT GLCD_Font_16x24;

// Draws a button with a label on top of it
void app_drawButton(Button *btn)
{
		GLCD_DrawBargraph(btn->posX,btn->posY,btn->width,btn->height,(uint32_t)btn->bitmap);
		GLCD_SetForegroundColor (GLCD_COLOR_WHITE);
		GLCD_SetFont (&GLCD_Font_16x24);
		GLCD_DrawString ((btn->posX + 10), (btn->posY + (btn->height/4)), btn->label);
}

// Draws a clock
void app_drawClock(Clock *clk)
{
	
		char buffer[128];
	
		GLCD_SetForegroundColor (GLCD_COLOR_WHITE);
		GLCD_SetFont (&GLCD_Font_16x24);
		sprintf(buffer, "%d : %d : %d", clk->hour,clk->minute, clk->second);
		GLCD_DrawString (clk->posX, clk->posY, " ");
		GLCD_DrawString (clk->posX, clk->posY, buffer);
}

// Draws the screen label
void app_drawScreenLabel(ScreenLabel *scrLbl)
{
	GLCD_SetFont (&GLCD_Font_16x24);
	GLCD_SetBackgroundColor (GLCD_COLOR_LIGHT_GREY);
	GLCD_SetForegroundColor (GLCD_COLOR_WHITE);
	GLCD_DrawString (scrLbl->posX, scrLbl->posY, scrLbl->name);
}

// Draws the bargraph
void app_drawBargraph(Bargraph *bargraph)
{
		GLCD_SetBackgroundColor (GLCD_COLOR_GREEN);
		GLCD_DrawBargraph(bargraph->posX,bargraph->posY,bargraph->width,bargraph->height,(uint32_t)bargraph->bitmap);
		GLCD_SetForegroundColor (GLCD_COLOR_WHITE);
		GLCD_SetFont (&GLCD_Font_6x8);
		GLCD_SetBackgroundColor (GLCD_COLOR_LIGHT_GREY);
		GLCD_DrawString (bargraph->posX - 50, bargraph->posY, bargraph->label);
		GLCD_SetBackgroundColor (GLCD_COLOR_PURPLE);
}