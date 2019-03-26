#include <stdio.h>
#include "stm32f7xx_hal_gpio.h"
#include "GUI_Utility.h"
#include "Board_GLCD.h"
#include "GLCD_Config.h"
#include "Board_Touch.h"

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
		GLCD_SetBackgroundColor (GLCD_COLOR_LIGHT_GREY);
		GLCD_SetForegroundColor (GLCD_COLOR_WHITE);
		GLCD_SetFont (&GLCD_Font_16x24);
		sprintf(buffer, "%d : %d : %d", clk->hour,clk->minute, clk->second);
		GLCD_DrawString (clk->posX, clk->posY, "              ");
		GLCD_DrawString (clk->posX, clk->posY, buffer);
}

// Draw program time
void app_drawProgramClock(Clock *clk)
{
	char buffer[128];
	GLCD_SetBackgroundColor (GLCD_COLOR_LIGHT_GREY);
	GLCD_SetForegroundColor (GLCD_COLOR_GREEN);
	GLCD_SetFont (&GLCD_Font_16x24);
	sprintf(buffer, "%d : %d", clk->hour,clk->minute);
	GLCD_DrawString (clk->posX, clk->posY, "          ");
	GLCD_DrawString (clk->posX, clk->posY, buffer);
}

// Draw Program time edit
void app_drawProgramTimeEdit(short xPos, short yPos, Clock *clock)
{
	char buffer[128];
	
	GLCD_SetBackgroundColor (GLCD_COLOR_LIGHT_GREY);
	GLCD_SetForegroundColor (GLCD_COLOR_WHITE);
	GLCD_SetFont (&GLCD_Font_16x24);
	sprintf(buffer, "%d", clock->hour);
	GLCD_DrawString (xPos, yPos, "   ");
	GLCD_DrawString (xPos, yPos, buffer);
	GLCD_DrawString (xPos + 20, yPos, "H");
	
	GLCD_SetBackgroundColor (GLCD_COLOR_BLUE);
	GLCD_DrawBargraph(xPos + 50,yPos,40,40, 0);
	GLCD_SetForegroundColor (GLCD_COLOR_WHITE);
	GLCD_SetFont (&GLCD_Font_16x24);
	GLCD_DrawString (xPos + 60, yPos, "+");
	
	GLCD_SetBackgroundColor (GLCD_COLOR_RED);
	GLCD_DrawBargraph(xPos + 100,yPos,40,40, 0);
	GLCD_SetForegroundColor (GLCD_COLOR_WHITE);
	GLCD_SetFont (&GLCD_Font_16x24);
	GLCD_DrawString (xPos + 110, yPos, "-");
	
	
	
	GLCD_SetBackgroundColor (GLCD_COLOR_LIGHT_GREY);
	GLCD_SetForegroundColor (GLCD_COLOR_WHITE);
	GLCD_SetFont (&GLCD_Font_16x24);
	sprintf(buffer, "%d", clock->minute);
	GLCD_DrawString (xPos + 180, yPos, "   ");
	GLCD_DrawString (xPos + 180, yPos, buffer);
	GLCD_DrawString (xPos + 200, yPos, "M");
	
	GLCD_SetBackgroundColor (GLCD_COLOR_BLUE);
	GLCD_DrawBargraph(xPos + 230,yPos,40,40, 0);
	GLCD_SetForegroundColor (GLCD_COLOR_WHITE);
	GLCD_SetFont (&GLCD_Font_16x24);
	GLCD_DrawString (xPos + 240, yPos, "+");
	
	GLCD_SetBackgroundColor (GLCD_COLOR_RED);
	GLCD_DrawBargraph(xPos + 280,yPos,40,40, 0);
	GLCD_SetForegroundColor (GLCD_COLOR_WHITE);
	GLCD_SetFont (&GLCD_Font_16x24);
	GLCD_DrawString (xPos + 290, yPos, "-");
	
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
void app_clockTicToc(Clock *clock)
{
	char buffer[128];
	clock->tic = HAL_GetTick()/10;
		if (clock->tic != clock->toc) { /* 10 ms update */
			clock->toc = clock->tic;
			clock->second = (clock->elapsed_t/100)%60; /* update time */
			clock->minute = (clock->elapsed_t/6000)%60;
			clock->hour = (clock->elapsed_t/360000)%24;
			/* Update Display */
			app_drawClock(clock);
			clock->elapsed_t = (clock->elapsed_t+1) % DAY;
		}
}

// User input handler
void app_userInputHandle(char **page, short numOfButtons, Button **buttons, GPIO_InitTypeDef **pins, Clock *clock)
{
	unsigned short i = 0;
	char *currentPage = *page;
	TOUCH_STATE tscState;
	clock->elapsed_t = clock->second*100+clock->minute*60*100+clock->hour*60*60*100;
	
	while(1)
	{
		if (strcmp(*page, currentPage) == 0)
		{
			app_clockTicToc(clock);
			Touch_GetState(&tscState);
			if (tscState.pressed)
			{
				for (i = 0; i < numOfButtons; i++)
				{
					if (tscState.x > buttons[i]->posX && tscState.x < (buttons[i]->width + buttons[i]->posX)
					 && tscState.y > buttons[i]->posY && tscState.y < (buttons[i]->height + buttons[i]->posY))
					{
						if (buttons[i]->navigation)
						{
							*page = buttons[i]->label;
						} 
						else {
							if (buttons[i]->funtionality->state == 0)
							{
								HAL_GPIO_WritePin(GPIOC, pins[buttons[i]->funtionality->pin]->Pin, GPIO_PIN_SET);
								buttons[i]->backgroundColor = GLCD_COLOR_GREEN;
								app_drawButton(&*buttons[i]);
								buttons[i]->funtionality->state = 1;
								wait(50000000);
							} else {
								HAL_GPIO_WritePin(GPIOC, pins[buttons[i]->funtionality->pin]->Pin, GPIO_PIN_RESET);
								buttons[i]->backgroundColor = GLCD_COLOR_RED;
								app_drawButton(&*buttons[i]);
								buttons[i]->funtionality->state = 0;
								wait(50000000);
							}
						}
					}
				}
			}
		} else {
			break;
		}
	}
	
}