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

// Delay Function
void wait(int delay)
{
	int i = 0;
	for(i = 0; i < delay; i++)
	{
	}
}
	
// Open Door
void app_openDoor(void)
{
	GPIO_InitTypeDef pinD0 = {GPIO_PIN_7, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_HIGH};
	int counter =0;
	while(counter<20)
	{
		

		HAL_GPIO_WritePin(GPIOC, pinD0.Pin, GPIO_PIN_SET);
		wait(1000);
		HAL_GPIO_WritePin(GPIOC, pinD0.Pin, GPIO_PIN_RESET);
		wait(1000000);
		counter +=1;
	}
}
	
// Close Door
void app_closeDoor(void)
{
	GPIO_InitTypeDef pinD0 = {GPIO_PIN_7, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_HIGH};
	
	int counter = 0;
	while(counter<20)
	{
	
		HAL_GPIO_WritePin(GPIOC, pinD0.Pin, GPIO_PIN_SET);
		wait(1000000);
		HAL_GPIO_WritePin(GPIOC, pinD0.Pin, GPIO_PIN_RESET);
		wait(1000);
		counter +=1;
	}
}
	
// Draws a button with a label on top of it
void app_drawButton(Button *btn)
{
		GLCD_DrawBargraph(btn->posX,btn->posY,btn->width,btn->height,0);
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
	sprintf(buffer, "%d", clock->hour);
	GLCD_DrawString (xPos, yPos, "   ");
	GLCD_DrawString (xPos, yPos, buffer);
	GLCD_DrawString (xPos + 40, yPos, "H");
	
	GLCD_SetBackgroundColor (GLCD_COLOR_BLUE);
	GLCD_DrawBargraph(xPos + 70,yPos,40,40, 0);
	GLCD_DrawString (xPos + 80, yPos, "+");
	
	GLCD_SetBackgroundColor (GLCD_COLOR_RED);
	GLCD_DrawBargraph(xPos + 120,yPos,40,40, 0);
	GLCD_DrawString (xPos + 130, yPos, "-");
	
	
	
	GLCD_SetBackgroundColor (GLCD_COLOR_LIGHT_GREY);
	sprintf(buffer, "%d", clock->minute);
	GLCD_DrawString (xPos + 200, yPos, "   ");
	GLCD_DrawString (xPos + 200, yPos, buffer);
	GLCD_DrawString (xPos + 220, yPos, "M");
	
	GLCD_SetBackgroundColor (GLCD_COLOR_BLUE);
	GLCD_DrawBargraph(xPos + 250,yPos,40,40, 0);
	GLCD_DrawString (xPos + 260, yPos, "+");
	
	GLCD_SetBackgroundColor (GLCD_COLOR_RED);
	GLCD_DrawBargraph(xPos + 300,yPos,40,40, 0);
	GLCD_DrawString (xPos + 310, yPos, "-");
	
}

// Draws the screen label
void app_drawScreenLabel(ScreenLabel *scrLbl)
{
	GLCD_SetBackgroundColor (GLCD_COLOR_LIGHT_GREY);
	GLCD_DrawString (scrLbl->posX, scrLbl->posY, scrLbl->name);
	GLCD_SetBackgroundColor (GLCD_COLOR_PURPLE);
}

// Draws the bargraph
void app_drawBargraph(Bargraph *bargraph)
{
		GLCD_SetBackgroundColor (GLCD_COLOR_GREEN);
		GLCD_DrawBargraph(bargraph->posX,bargraph->posY,bargraph->width,bargraph->height,0);
		GLCD_SetFont (&GLCD_Font_6x8);
		GLCD_SetBackgroundColor (GLCD_COLOR_LIGHT_GREY);
		GLCD_DrawString (bargraph->posX - 50, bargraph->posY, bargraph->label);
		GLCD_SetBackgroundColor (GLCD_COLOR_PURPLE);
		GLCD_SetFont (&GLCD_Font_16x24);
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
								//HAL_GPIO_WritePin(GPIOC, pins[buttons[i]->funtionality->pin]->Pin, GPIO_PIN_SET);
								app_openDoor();
								buttons[i]->funtionality->state = 1;
								//wait(50000000);
							} else {
								//HAL_GPIO_WritePin(GPIOC, pins[buttons[i]->funtionality->pin]->Pin, GPIO_PIN_RESET);
								app_closeDoor();
								buttons[i]->funtionality->state = 0;
								//wait(50000000);
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