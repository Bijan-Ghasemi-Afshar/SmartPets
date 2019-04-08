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

ADC_HandleTypeDef g_AdcHandle;

void ConfigureADC()
{
	GPIO_InitTypeDef gpioInit;
	ADC_ChannelConfTypeDef adcChannel;
	
	__GPIOA_CLK_ENABLE();
	__ADC3_CLK_ENABLE();

	gpioInit.Pin = GPIO_PIN_0;
	gpioInit.Mode = GPIO_MODE_ANALOG;
	gpioInit.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &gpioInit);

	HAL_NVIC_SetPriority(ADC_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(ADC_IRQn);

	g_AdcHandle.Instance = ADC3;

	g_AdcHandle.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV2;
	g_AdcHandle.Init.Resolution = ADC_RESOLUTION_12B;
	g_AdcHandle.Init.ScanConvMode = DISABLE;
	g_AdcHandle.Init.ContinuousConvMode = ENABLE;
	g_AdcHandle.Init.DiscontinuousConvMode = DISABLE;
	g_AdcHandle.Init.NbrOfDiscConversion = 0;
	g_AdcHandle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	g_AdcHandle.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T1_CC1;
	g_AdcHandle.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	g_AdcHandle.Init.NbrOfConversion = 1;
	g_AdcHandle.Init.DMAContinuousRequests = ENABLE;
	g_AdcHandle.Init.EOCSelection = DISABLE;

	HAL_ADC_Init(&g_AdcHandle);
	//HAL_ADC_MspInit(&g_AdcHandle);

	adcChannel.Channel = ADC_CHANNEL_0;
	adcChannel.Rank = 1;
	adcChannel.SamplingTime = ADC_SAMPLETIME_480CYCLES;
	adcChannel.Offset = 0;

}

	
// Delay Function
void wait(int delay)
{
	int i = 0;
	for(i = 0; i < delay; i++)
	{
	}
}
	
// Buzz
void buzz(void)
{
	GPIO_InitTypeDef pinD0 = {GPIO_PIN_7, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_HIGH};
	HAL_GPIO_WritePin(GPIOC, pinD0.Pin, GPIO_PIN_SET);
	wait(40000000);
	HAL_GPIO_WritePin(GPIOC, pinD0.Pin, GPIO_PIN_RESET);
}

// Check program time
Program dayProgram = { 11, 21, 0 };
Program nightProgram = { 11, 22, 0 };
void app_checkProgram(Clock *clk)
{
	
	
	// If it's day program
	if (dayProgram.hour <= clk->hour && dayProgram.minute <= clk->minute && nightProgram.hour >= clk->hour && nightProgram.minute > clk->minute)
	{
		if (dayProgram.programRunning == 0){
			dayProgram.programRunning = 1;
			nightProgram.programRunning = 0;
			GLCD_DrawString (50, 120, "Day Program");
			buzz();
		} else {}
	} else if (nightProgram.hour <= clk->hour && nightProgram.minute <= clk->minute){
		if (nightProgram.programRunning == 0){
			dayProgram.programRunning = 0;
			nightProgram.programRunning = 1;
			GLCD_DrawString (50, 120, "Night Program");
			buzz();
		} else {}
	}
	else {
		//GLCD_DrawString (50, 120, "FUUCK");
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
		GLCD_SetBackgroundColor (GLCD_COLOR_LIGHT_GREY);
		GLCD_DrawBargraph(bargraph->posX,bargraph->posY,GLCD_SIZE_X/2 + 40,bargraph->height,0);
		GLCD_SetBackgroundColor (bargraph->background);
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

// Update water level
void app_updateWaterLevel(Bargraph *bargraph)
{
	int g_ADCValue;
	char buffer[128];
	
	g_ADCValue = HAL_ADC_GetValue(&g_AdcHandle);
	
//	sprintf(buffer, "%d", g_ADCValue);
//	GLCD_DrawString (20, 150, "              ");
//	GLCD_DrawString (20, 150, buffer);
	
	if (g_ADCValue >= 0 && g_ADCValue < 3600)
	{
		bargraph->width = 40;
		bargraph->background = GLCD_COLOR_RED;
		app_drawBargraph(bargraph);
	} else if (g_ADCValue >= 3600 && g_ADCValue < 4090)
	{
		bargraph->width = GLCD_SIZE_X/3;
		bargraph->background = GLCD_COLOR_GREEN;
		app_drawBargraph(bargraph);
	} else if (g_ADCValue >= 4090)
	{
		bargraph->width = GLCD_SIZE_X/2 + 40;
		bargraph->background = GLCD_COLOR_GREEN;
		app_drawBargraph(bargraph);
	} else {}
}

// Page specific logic
void app_homePageSpecific()
{
	Bargraph waterBargraph = { GLCD_SIZE_X/4 - 20, GLCD_SIZE_Y/5 * 4 - 10, GLCD_SIZE_X/2 + 40, 10, GLCD_COLOR_GREEN, "Water" };
	
	app_updateWaterLevel(&waterBargraph);
}

// Handle sensor type
void app_handleSensor(Button *button, short pin)
{
	if (button->funtionality->state == 0)
	{
		if (strcmp(button->funtionality->type, "pwm") == 0)
		{
			app_openDoor();
			button->funtionality->state = 1;
		} else if (strcmp(button->funtionality->type, "digital") == 0){
			//HAL_GPIO_WritePin(GPIOC, pin, GPIO_PIN_SET);
			buzz();
			button->funtionality->state = 1;
		} else {}
	} else {
		if (strcmp(button->funtionality->type, "pwm") == 0)
		{
			app_closeDoor();
			button->funtionality->state = 0;
		} else if (strcmp(button->funtionality->type, "digital") == 0){
			//HAL_GPIO_WritePin(GPIOC, pin, GPIO_PIN_RESET);
			buzz();
			button->funtionality->state = 0;
		} else {}
	}
}

// User input handler
void app_userInputHandle(char **page, short numOfButtons, Button **buttons, GPIO_InitTypeDef **pins, Clock *clock)
{
	unsigned short i = 0;
	char *currentPage = *page;
	TOUCH_STATE tscState;
	clock->elapsed_t = clock->second*100+clock->minute*60*100+clock->hour*60*60*100;
	HAL_ADC_Start(&g_AdcHandle);
	
	
	while(1)
	{
		if (strcmp(*page, currentPage) == 0)
		{
			app_clockTicToc(clock);
			app_checkProgram(clock);
			
			if (strcmp(*page, "Home") == 0)
			{
				app_homePageSpecific();
			} else if (strcmp(*page, "Day") == 0){
			} else if (strcmp(*page, "Night") == 0){
			} else if (strcmp(*page, "Play") == 0){
			} else if (strcmp(*page, "Manual") == 0){
			} else {
			}
			
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
							app_handleSensor(buttons[i], pins[buttons[i]->funtionality->pin]->Pin);
							wait(50000000);
						}
					}
				}
			}
		} else {
			break;
		}
	}
	
}