#include "GUI_Utility.h"
#include "Board_GLCD.h"
#include "GLCD_Config.h"
#include <stdio.h>

#ifdef __RTX
	extern uint32_t os_time;
	uint32_t HAL_GetTick(void) {
		return os_time;
	}
#endif

extern GLCD_FONT GLCD_Font_6x8;
extern GLCD_FONT GLCD_Font_16x24;

// Draws a button with a label on top of it
void app_drawButton(Button *btn)
{
		GLCD_SetBackgroundColor (btn->backgroundColor);
		GLCD_DrawBargraph(btn->posX,btn->posY,btn->width,btn->height,(uint32_t)btn->bitmap);
		GLCD_SetForegroundColor (btn->color);
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
		GLCD_DrawString (clk->posX, clk->posY, "              ");
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

// Clock functionality
void app_clockTicToc(uint32_t *tic, uint32_t *toc, uint32_t *elapsed_t, Clock *clock)
{
	char buffer[128];
	*tic = HAL_GetTick()/10;
		if (*tic != *toc) { /* 10 ms update */
			*toc = *tic;
			clock->second = (*elapsed_t/100)%60; /* update time */
			clock->minute = (*elapsed_t/6000)%60;
			clock->hour = (*elapsed_t/360000)%24;
			/* Update Display */
			app_drawClock(clock);
			*elapsed_t = (*elapsed_t+1) % DAY;
		}
}
