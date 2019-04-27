#include "stm32f7xx_hal.h"
#include "GUI_Utility.h"
#include "Board_GLCD.h"
#include "GLCD_Config.h"
#include "Board_Touch.h"
#include "dwt_stm32_delay.h"

#ifdef __RTX
	extern uint32_t os_time;
	uint32_t HAL_GetTick(void) {
		return os_time;
	}
#endif

extern GLCD_FONT GLCD_Font_6x8;
extern GLCD_FONT GLCD_Font_16x24;

ADC_HandleTypeDef g_AdcHandleWater;
ADC_HandleTypeDef g_AdcHandleFood;
int check = 0;
	
// A milisecond delay function
void milDelay(int dl)
{
	int osTime = 0;
	int counter = 0;
	int initalTime = 0;
	while(1)
	{
		if(counter == 0)
		{
				initalTime = HAL_GetTick();
		}
		osTime = HAL_GetTick();
		if(osTime >= initalTime + dl)
		{
			break;
		}
		counter++;
	}
}
	
// Send a request signal to the tempreture sensor
void DHT11Start(GPIO_InitTypeDef* pin)
{
	// Set pin as output
	pin->Mode = GPIO_MODE_OUTPUT_PP;
	HAL_GPIO_Init(GPIOB, pin);
	
	// Send a 0 (LOW) to sensor
	HAL_GPIO_WritePin(GPIOB, pin->Pin, GPIO_PIN_RESET);
	
	// Wait for 18 (miliseconds)
	DWT_Delay_us(18000);
	
	// Set pin as input
	pin->Mode = GPIO_MODE_INPUT;
	HAL_GPIO_Init(GPIOB, pin);
}

// Check the response of the tempreture sensor
void checkResponse(GPIO_InitTypeDef* pin)
{
	int pinStatus = 0;
	
	// 40us (microsecond) delay
	DWT_Delay_us(40);
	
	if (!(HAL_GPIO_ReadPin (GPIOB, pin->Pin)))
	{
		// Wait for 80us (microsecond)
		DWT_Delay_us(80);
		if ((HAL_GPIO_ReadPin (GPIOB, pin->Pin)))
		{
			check = 1;
		}
	}
	while((HAL_GPIO_ReadPin (GPIOB, pin->Pin)));
}

// Read the data of the tempreture sensor
int readData(GPIO_InitTypeDef* pin)
{
	int i,j;
	for (j=0;j<8;j++)
	{
		while (!(HAL_GPIO_ReadPin (GPIOB, pin->Pin)));   // wait for the pin to go high
		DWT_Delay_us (40);   // wait for 40 us
		if ((HAL_GPIO_ReadPin (GPIOB, pin->Pin)) == 0)   // if the pin is low 
		{
			i&= ~(1<<(7-j));   // write 0
		}
		else {
			i|= (1<<(7-j));  // if the pin is high, write 1
		}
		while ((HAL_GPIO_ReadPin (GPIOB, pin->Pin)));  // wait for the pin to go low
	}
	return i;
}


// Configure the Analog to Digital Converter
void ConfigureADCWater()
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

	g_AdcHandleWater.Instance = ADC3;

	g_AdcHandleWater.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV2;
	g_AdcHandleWater.Init.Resolution = ADC_RESOLUTION_12B;
	g_AdcHandleWater.Init.ScanConvMode = DISABLE;
	g_AdcHandleWater.Init.ContinuousConvMode = ENABLE;
	g_AdcHandleWater.Init.DiscontinuousConvMode = DISABLE;
	g_AdcHandleWater.Init.NbrOfDiscConversion = 0;
	g_AdcHandleWater.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	g_AdcHandleWater.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T1_CC1;
	g_AdcHandleWater.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	g_AdcHandleWater.Init.NbrOfConversion = 1;
	g_AdcHandleWater.Init.DMAContinuousRequests = ENABLE;
	g_AdcHandleWater.Init.EOCSelection = DISABLE;

	HAL_ADC_Init(&g_AdcHandleWater);
	//HAL_ADC_MspInit(&g_AdcHandle);

	adcChannel.Channel = ADC_CHANNEL_0;
	adcChannel.Rank = 1;
	adcChannel.SamplingTime = ADC_SAMPLETIME_480CYCLES;
	adcChannel.Offset = 0;

	if (HAL_ADC_ConfigChannel(&g_AdcHandleWater, &adcChannel) != HAL_OK)
	{
		GLCD_DrawString (150, 150, "ADC is NOT OK");
	}

}

// Configure Analog to Digital Converter for FOOD Sensor
void ConfigureADCFood()
{
	GPIO_InitTypeDef gpioInit;
	ADC_ChannelConfTypeDef adcChannel;
	
	__GPIOF_CLK_ENABLE();
	__ADC3_CLK_ENABLE();

	gpioInit.Pin = GPIO_PIN_10;
	gpioInit.Mode = GPIO_MODE_ANALOG;
	gpioInit.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOF, &gpioInit);

	HAL_NVIC_SetPriority(ADC_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(ADC_IRQn);

	g_AdcHandleFood.Instance = ADC3;

	g_AdcHandleFood.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV2;
	g_AdcHandleFood.Init.Resolution = ADC_RESOLUTION_12B;
	g_AdcHandleFood.Init.ScanConvMode = DISABLE;
	g_AdcHandleFood.Init.ContinuousConvMode = ENABLE;
	g_AdcHandleFood.Init.DiscontinuousConvMode = DISABLE;
	g_AdcHandleFood.Init.NbrOfDiscConversion = 0;
	g_AdcHandleFood.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	g_AdcHandleFood.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T1_CC1;
	g_AdcHandleFood.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	g_AdcHandleFood.Init.NbrOfConversion = 1;
	g_AdcHandleFood.Init.DMAContinuousRequests = ENABLE;
	g_AdcHandleFood.Init.EOCSelection = DISABLE;

	HAL_ADC_Init(&g_AdcHandleFood);
	//HAL_ADC_MspInit(&g_AdcHandle);

	adcChannel.Channel = ADC_CHANNEL_8;
	adcChannel.Rank = 1;
	adcChannel.SamplingTime = ADC_SAMPLETIME_480CYCLES;
	adcChannel.Offset = 0;

	if (HAL_ADC_ConfigChannel(&g_AdcHandleFood, &adcChannel) != HAL_OK)
	{
		GLCD_DrawString (150, 150, "ADC is NOT OK");
	}

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
	GPIO_InitTypeDef pinD5 = {GPIO_PIN_0, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_HIGH};
	HAL_GPIO_WritePin(GPIOI, pinD5.Pin, GPIO_PIN_SET);
	wait(40000000);
	HAL_GPIO_WritePin(GPIOI, pinD5.Pin, GPIO_PIN_RESET);
}

// Turn Wheel ON
void turnOnWheel(void)
{
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_7, GPIO_PIN_SET);
}

// Turn Wheel OFF
void turnOffWheel(void)
{
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_7, GPIO_PIN_RESET);
}

// Check program time
void app_checkProgram(Clock *dayProgram, Clock *nightProgram, Clock *clk)
{
	
	
	// If it's day program
	if (dayProgram->hour <= clk->hour && dayProgram->minute <= clk->minute && nightProgram->hour >= clk->hour && nightProgram->minute > clk->minute)
	{
		if (dayProgram->programRunning == 0){
			dayProgram->programRunning = 1;
			nightProgram->programRunning = 0;
			GLCD_DrawString (50, 120, "Day Program");
			buzz();
		} else {}
	} else if (nightProgram->hour <= clk->hour && nightProgram->minute <= clk->minute){
		if (nightProgram->programRunning == 0){
			dayProgram->programRunning = 0;
			nightProgram->programRunning = 1;
			GLCD_DrawString (50, 120, "Night Program");
			buzz();
		} else {}
	}
	else {
		//GLCD_DrawString (50, 120, "FUUCK");
	}
}

// Open Door
void app_openDoor(Button *button, short pin)
{
	int counter = 0;
	while(counter < 10)
	{
		HAL_GPIO_WritePin(button->funtionality->base, pin, GPIO_PIN_SET);
		milDelay(2);
		HAL_GPIO_WritePin(button->funtionality->base, pin, GPIO_PIN_RESET);
		milDelay(22);
		counter++;
	}
}
	
// Close Door
void app_closeDoor(Button *button, short pin)
{
	int counter = 0;
	while(counter < 10)
	{
		HAL_GPIO_WritePin(button->funtionality->base, pin, GPIO_PIN_SET);
		milDelay(1);
		HAL_GPIO_WritePin(button->funtionality->base, pin, GPIO_PIN_RESET);
		milDelay(22);
		counter++;
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
void app_drawProgramTimeEdit(Button *editIncHour, Button *editDecHour, Button *editIncMin, Button *editDecMin, Clock *clock)
{
	char buffer[128];
//	// ====================== Edit Program Buttons ======================
//	Button editIncHour = {(GLCD_SIZE_X/4 + 60), 140, 40, 40};
//	Button editDecHour = {(GLCD_SIZE_X/4 + 120), 140, 40, 40};
//	Button editIncMin = {(GLCD_SIZE_X/4 + 250), 140, 40, 40};
//	Button editDecMin = {(GLCD_SIZE_X/4 + 300), 140, 40, 40};
	
	GLCD_SetBackgroundColor (GLCD_COLOR_LIGHT_GREY);
	sprintf(buffer, "%d", clock->hour);
	GLCD_DrawString (editIncHour->posX - 50, editIncHour->posY, "   ");
	GLCD_DrawString (editIncHour->posX - 50, editIncHour->posY, buffer);
	GLCD_DrawString (editIncHour->posX - 18, editIncHour->posY, "H");
	
	GLCD_SetBackgroundColor (GLCD_COLOR_BLUE);
	GLCD_DrawBargraph(editIncHour->posX,editIncHour->posY,editIncHour->height,editIncHour->width, 0);
	GLCD_DrawString (editIncHour->posX + 10, editIncHour->posY, "+");
	
	GLCD_SetBackgroundColor (GLCD_COLOR_RED);
	GLCD_DrawBargraph(editDecHour->posX,editDecHour->posY,editDecHour->height,editDecHour->width, 0);
	GLCD_DrawString (editDecHour->posX + 10, editDecHour->posY, "-");
	
	
	
	GLCD_SetBackgroundColor (GLCD_COLOR_LIGHT_GREY);
	sprintf(buffer, "%d", clock->minute);
	GLCD_DrawString (editIncMin->posX - 50, editIncMin->posY, "   ");
	GLCD_DrawString (editIncMin->posX - 50, editIncMin->posY, buffer);
	GLCD_DrawString (editIncMin->posX - 20, editIncMin->posY, "M");
	
	GLCD_SetBackgroundColor (GLCD_COLOR_BLUE);
	GLCD_DrawBargraph(editIncMin->posX,editIncMin->posY,editIncMin->height,editIncMin->width, 0);
	GLCD_DrawString (editIncMin->posX + 10, editIncMin->posY, "+");
	
	GLCD_SetBackgroundColor (GLCD_COLOR_RED);
	GLCD_DrawBargraph(editDecMin->posX,editDecMin->posY,editDecMin->height,editDecMin->width, 0);
	GLCD_DrawString (editDecMin->posX + 10, editDecMin->posY, "-");
	
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

// Edit Program Time
void app_editProgramTime()
{
	
}

// Update water level
void app_updateWaterLevel(Bargraph *bargraph)
{
	int g_ADCValueWater = 0;
	char buffer[128];
	//GLCD_DrawString (20, 120, " Get Water Level");
	
	ConfigureADCWater();
	HAL_ADC_Start(&g_AdcHandleWater);
	g_ADCValueWater = HAL_ADC_GetValue(&g_AdcHandleWater);
//	sprintf(buffer, "%d", g_ADCValueWater);
//	GLCD_DrawString (150, 100, "           ");
//	GLCD_DrawString (150, 100, buffer);
	if (g_ADCValueWater >= 0 && g_ADCValueWater < 2500)
	{
		bargraph->width = 40;
		bargraph->background = GLCD_COLOR_RED;
		app_drawBargraph(bargraph);
	} else if (g_ADCValueWater >= 3100 && g_ADCValueWater < 3500)
	{
		bargraph->width = GLCD_SIZE_X/3;
		bargraph->background = GLCD_COLOR_GREEN;
		app_drawBargraph(bargraph);
	} else if (g_ADCValueWater >= 3500)
	{
		bargraph->width = GLCD_SIZE_X/2 + 40;
		bargraph->background = GLCD_COLOR_GREEN;
		app_drawBargraph(bargraph);
	} else {}
}

// Update food level
void app_updateFoodLevel(Bargraph *bargraph)
{
	int g_ADCValueFood = 0;
	char buffer[128];
	
	ConfigureADCFood();
	HAL_ADC_Start(&g_AdcHandleFood);
	g_ADCValueFood = HAL_ADC_GetValue(&g_AdcHandleFood);
	
	if (g_ADCValueFood >= 0 && g_ADCValueFood < 2500)
	{
		bargraph->width = 40;
		bargraph->background = GLCD_COLOR_RED;
		app_drawBargraph(bargraph);
	} else if (g_ADCValueFood >= 3100 && g_ADCValueFood < 3500)
	{
		bargraph->width = GLCD_SIZE_X/3;
		bargraph->background = GLCD_COLOR_GREEN;
		app_drawBargraph(bargraph);
	} else if (g_ADCValueFood >= 3500)
	{
		bargraph->width = GLCD_SIZE_X/2 + 40;
		bargraph->background = GLCD_COLOR_GREEN;
		app_drawBargraph(bargraph);
	} else {}
	
}

// Update Tempreture
void app_updateTempreture()
{
	uint8_t rhByte1 = 0, rhByte2 = 0, tempByte1 = 0, tempByte2 = 0, sum = 0;
	GPIO_InitTypeDef pinD3 = {GPIO_PIN_4, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_LOW};
	char buffer[128];
	check = 0;
	
	DWT_Delay_Init();
	
	HAL_GPIO_Init(GPIOB, &pinD3);
	// Send a 1 (HIGH) to sensor
	HAL_GPIO_WritePin(GPIOB, pinD3.Pin, GPIO_PIN_SET);
	DWT_Delay_us(2000);
	
	DHT11Start(&pinD3);
	checkResponse(&pinD3);
	if (check)
	{
		//GLCD_DrawString (20, 20, "Tempreture sensor is OK");
		rhByte1 = readData(&pinD3);
		rhByte2 = readData(&pinD3);
		tempByte1 = readData(&pinD3);
		tempByte2 = readData(&pinD3);
		sum = readData(&pinD3);
	}
	
	sprintf(buffer, "%d", rhByte1);
	GLCD_DrawString (20, 50, buffer);
	sprintf(buffer, "%d", tempByte1);
	GLCD_DrawString (20, 90, buffer);
}


// Page specific logic
void app_homePageSpecific()
{
	Bargraph foodBargraph = { GLCD_SIZE_X/4 - 20, GLCD_SIZE_Y/5 * 4 - 10, GLCD_SIZE_X/2 + 40, 10, GLCD_COLOR_GREEN, "Food " };
	Bargraph waterBargraph = { GLCD_SIZE_X/4 - 20, GLCD_SIZE_Y/5 * 4 + 10, GLCD_SIZE_X/2 + 40, 10, GLCD_COLOR_GREEN, "Water" };
	app_updateFoodLevel(&waterBargraph);
	app_updateWaterLevel(&foodBargraph);
	if (HAL_GetTick()%5 == 0 )
	{
		
		//app_updateTempreture();
	}
}

// Handle sensor type
void app_handleSensor(Button *button, short pin, Clock *program)
{
	if (button->funtionality->state == 0)
	{
		if (strcmp(button->funtionality->type, "pwm") == 0)
		{
			app_openDoor(button, pin);
			button->funtionality->state = 1;
		} else if (strcmp(button->funtionality->type, "digital") == 0){
			HAL_GPIO_WritePin(button->funtionality->base, pin, GPIO_PIN_SET);
			button->funtionality->state = 1;
		} else if (strcmp(button->funtionality->type, "edit") == 0){		// Edit buttons state is always 0
			
			if (strcmp(button->label, "+h") == 0)
			{
				
				program->hour++;
			} else if (strcmp(button->label, "-h") == 0)
			{
				program->hour--;
			} else if (strcmp(button->label, "+m") == 0)
			{
				program->minute++;
			} else if (strcmp(button->label, "-m") == 0)
			{
				program->minute--;
			} else {}
				
		} else {}
	} else {
		if (strcmp(button->funtionality->type, "pwm") == 0)
		{
			app_closeDoor(button, pin);
			button->funtionality->state = 0;
		} else if (strcmp(button->funtionality->type, "digital") == 0){
			HAL_GPIO_WritePin(button->funtionality->base, pin, GPIO_PIN_RESET);
			button->funtionality->state = 0;
		} else {}
	}
}

// User input handler
void app_userInputHandle(char **page, short numOfButtons, Button **buttons, GPIO_InitTypeDef **pins, Clock *clock, Clock **programs)
{
	unsigned short i = 0;
	Clock *program;
	char *currentPage = *page;
	TOUCH_STATE tscState;
	clock->elapsed_t = clock->second*100+clock->minute*60*100+clock->hour*60*60*100;
	
	if (strcmp(*page, "Day") == 0){
		program = programs[0];
	} else if (strcmp(*page, "Night") == 0){
		program = programs[1];
	} else if (strcmp(*page, "Play") == 0){
		program = programs[2];
	} else {}
	
	
	while(1)
	{
		if (strcmp(*page, currentPage) == 0)
		{
			app_clockTicToc(clock);
			//app_checkProgram(programs[0], programs[1], clock);
			
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
							app_handleSensor(buttons[i], pins[buttons[i]->funtionality->pin]->Pin, program);
							wait(10000000);
						}
					}
				}
			}
		} else {
			break;
		}
	}
	
}