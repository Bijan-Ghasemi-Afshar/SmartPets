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

	
// ====================== GPIO PINS ======================
GPIO_InitTypeDef pinD0 = {GPIO_PIN_7, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_HIGH};
GPIO_InitTypeDef pinD1 = {GPIO_PIN_6, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_HIGH};
GPIO_InitTypeDef pinD2 = {GPIO_PIN_6, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_HIGH};
GPIO_InitTypeDef pinD3 = {GPIO_PIN_4, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_HIGH};
GPIO_InitTypeDef pinD4 = {GPIO_PIN_7, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_HIGH};
GPIO_InitTypeDef pinD5 = {GPIO_PIN_0, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_HIGH};
GPIO_InitTypeDef pinD6 = {GPIO_PIN_6, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_HIGH};
GPIO_InitTypeDef pinD7 = {GPIO_PIN_3, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_HIGH};
GPIO_InitTypeDef raspberryPin = {GPIO_PIN_2, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_HIGH};
GPIO_InitTypeDef *CN4Pins[9] = {&pinD0, &pinD1, &pinD2, &pinD3, &pinD4, &pinD5, &pinD6, &pinD7, &raspberryPin};

// ====================== Screen Label ======================
ScreenLabel homeLabel = {20, 20, "Home"};
ScreenLabel manualLabel = {20, 20, "Manual"};

// ====================== Clock ======================
Clock clock = {CLOCK_POS_X, CLOCK_POS_Y, CLOCK_HOUR, CLOCK_MIN, CLOCK_SEC};

// ====================== Home Buttons ======================
Functionality dayButtonFunc = {BUTTON_DOOR_PIN, GPIOH, 0, "day"};
Functionality nightButtonFunc = {BUTTON_DOOR_PIN, GPIOH, 0, "night"};
Functionality playButtonFunc = {BUTTON_DOOR_PIN, GPIOH, 0, "play"};
Button dayButton = {GLCD_SIZE_X/4 - 20, GLCD_SIZE_Y/4, GLCD_SIZE_X/4, GLCD_SIZE_Y/5, "Day", 0, &dayButtonFunc};
Button nightButton = {((GLCD_SIZE_X/4) * 2) + 20, GLCD_SIZE_Y/4, GLCD_SIZE_X/4, GLCD_SIZE_Y/5, "Night", 0, &nightButtonFunc};
Button playButton = {BUTTON_PLAY_POS_X, BUTTON_PLAY_POS_Y, BUTTON_PLAY_WIDTH, BUTTON_PLAY_HEIGHT, BUTTON_PLAY_LABEL, 0, &playButtonFunc};
Button manButton = {BUTTON_MANUAL_POS_X, BUTTON_MANUAL_POS_Y, BUTTON_MANUAL_WIDTH, BUTTON_MANUAL_HEIGHT, BUTTON_MANUAL_LABEL, BUTTON_MANUAL_NAVIGATION};
Button *homeButtons[4] = {&dayButton, &nightButton, &playButton, &manButton};

// ====================== Manual Buttons ======================
Functionality doorButtonFunc = {BUTTON_DOOR_PIN, GPIOH, BUTTON_DOOR_STATE, "pwm"};
Functionality treatButtonFunc = {BUTTON_TREAT_PIN, GPIOI, BUTTON_TREAT_STATE, "pwm"};
Functionality lightsButtonFunc = {BUTTON_LIGHTS_PIN, GPIOC, BUTTON_LIGHTS_STATE, "digital"};
Functionality heatingButtonFunc = {BUTTON_HEATING_PIN, GPIOC, BUTTON_HEATING_STATE, "digital"};
Functionality fanButtonFunc = {BUTTON_FAN_PIN, GPIOG, BUTTON_FAN_STATE, "digital"};
Functionality alarmButtonFunc = {BUTTON_ALARM_PIN, GPIOI, BUTTON_ALARM_STATE, "digital"};
Functionality rasbpButtonFunc = {BUTTON_CAMERA_PIN, GPIOI, 0, "digital"};

Button doorButton = {BUTTON_DOOR_POS_X, BUTTON_DOOR_POS_Y, BUTTON_DOOR_WIDTH, BUTTON_DOOR_HEIGHT, BUTTON_DOOR_LABEL, BUTTON_DOOR_NAVIGATION, &doorButtonFunc};
Button treatButton = {BUTTON_TREAT_POS_X, BUTTON_TREAT_POS_Y, BUTTON_TREAT_WIDTH, BUTTON_TREAT_HEIGHT, BUTTON_TREAT_LABEL, BUTTON_TREAT_NAVIGATION, &treatButtonFunc};
Button lightsButton = {BUTTON_LIGHTS_POS_X, BUTTON_LIGHTS_POS_Y, BUTTON_LIGHTS_WIDTH, BUTTON_LIGHTS_HEIGHT, BUTTON_LIGHTS_LABEL, BUTTON_LIGHTS_NAVIGATION, &lightsButtonFunc};
Button HeatingButton = {BUTTON_HEATING_POS_X, BUTTON_HEATING_POS_Y, BUTTON_HEATING_WIDTH, BUTTON_HEATING_HEIGHT, BUTTON_HEATING_LABEL, BUTTON_HEATING_NAVIGATION, &heatingButtonFunc};
Button fanButton = {BUTTON_FAN_POS_X, BUTTON_FAN_POS_Y, BUTTON_FAN_WIDTH, BUTTON_FAN_HEIGHT, BUTTON_FAN_LABEL, BUTTON_FAN_NAVIGATION, &fanButtonFunc};
Button rasbButton = {BUTTON_CAMERA_POS_X, BUTTON_CAMERA_POS_Y, BUTTON_CAMERA_WIDTH, BUTTON_CAMERA_HEIGHT, BUTTON_CAMERA_LABEL, 0, &rasbpButtonFunc};
Button homeButton = {BUTTON_HOME_POS_X, BUTTON_HOME_POS_Y, BUTTON_HOME_WIDTH, BUTTON_HOME_HEIGHT, BUTTON_HOME_LABEL, BUTTON_HOME_NAVIGATION};
Button *manualButtons[7] = {&doorButton, &lightsButton, &homeButton, &HeatingButton, &fanButton, &treatButton, &rasbButton};

// ====================== Bargraph ======================
Bargraph waterBargraph = { WATER_BARGRAPH_POS_X, WATER_BARGRAPH_POS_Y, WATER_BARGRAPH_WIDTH, WATER_BARGRAPH_HEIGHT, GLCD_COLOR_GREEN, WATER_BARGRAPH_LABEL };
Bargraph foodBargraph = { FOOD_BARGRAPH_POS_X, FOOD_BARGRAPH_POS_Y, FOOD_BARGRAPH_WIDTH, FOOD_BARGRAPH_HEIGHT, GLCD_COLOR_GREEN, FOOD_BARGRAPH_LABEL };

// The ADC Handler
ADC_HandleTypeDef g_AdcHandle;
// The check flag for the tempreture sensor to indicate whether the sensor's response is correct
int check = 0;


// Initialize Pins
void initializePins()
{
	GPIO_InitTypeDef gpioInit;
	
	// Enable all bases
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOI_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__GPIOA_CLK_ENABLE();
	__GPIOF_CLK_ENABLE();
	
	// Initialize Pin D0
	HAL_GPIO_Init(GPIOC, &pinD0);
	HAL_GPIO_WritePin(GPIOC, pinD0.Pin, GPIO_PIN_RESET);
	
	// Initialize Pin D1
	HAL_GPIO_Init(GPIOC, &pinD1);
	HAL_GPIO_WritePin(GPIOC, pinD1.Pin, GPIO_PIN_RESET);
	
	// Initialize Pin D2
	HAL_GPIO_Init(GPIOG, &pinD2);
	HAL_GPIO_WritePin(GPIOG, pinD2.Pin, GPIO_PIN_RESET);
	
	// Initialize Pin D3
	HAL_GPIO_Init(GPIOB, &pinD3);
	HAL_GPIO_WritePin(GPIOB, pinD3.Pin, GPIO_PIN_RESET);
	
	// Initialize Pin D4
	HAL_GPIO_Init(GPIOG, &pinD4);
	HAL_GPIO_WritePin(GPIOG, pinD4.Pin, GPIO_PIN_RESET);
	
	// Initialize Pin D5
	HAL_GPIO_Init(GPIOI, &pinD5);
	HAL_GPIO_WritePin(GPIOI, pinD5.Pin, GPIO_PIN_RESET);
	
	// Initialize Pin D6
	HAL_GPIO_Init(GPIOH, &pinD6);
	HAL_GPIO_WritePin(GPIOH, pinD6.Pin, GPIO_PIN_RESET);
	
	// Initialize Pin D7
	HAL_GPIO_Init(GPIOI, &pinD7);
	HAL_GPIO_WritePin(GPIOI, pinD7.Pin, GPIO_PIN_RESET);
	
	// Initialize Pin D8
	HAL_GPIO_Init(GPIOI, &raspberryPin);
	HAL_GPIO_WritePin(GPIOI, raspberryPin.Pin, GPIO_PIN_RESET);
	
	gpioInit.Pin = GPIO_PIN_0;
	gpioInit.Mode = GPIO_MODE_ANALOG;
	gpioInit.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &gpioInit);
	
	gpioInit.Pin = GPIO_PIN_10;
	gpioInit.Mode = GPIO_MODE_ANALOG;
	gpioInit.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOF, &gpioInit);
	
	gpioInit.Pin = GPIO_PIN_9;
	gpioInit.Mode = GPIO_MODE_ANALOG;
	gpioInit.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOF, &gpioInit);
	
}


// Draws the home page
void drawHomePage(char **page)
{
	// Draw Screen Label
	app_drawScreenLabel(&homeLabel);
	
	// Draw Day Button
	app_drawButton(&dayButton);

	// Draw Night Button
	app_drawButton(&nightButton);
	
	// Draw Play Button
	app_drawButton(&playButton);
	
	// Draw Manual Button
	app_drawButton(&manButton);
	
	// Draw Water Level
	app_drawBargraph(&waterBargraph);
	
	// Draw Food Level
	app_drawBargraph(&foodBargraph);
	
	// Handle user input 
	app_userInputHandle(page, 4, homeButtons);
}

// Draws the manual page
void drawManualPage(char **page)
{
	
	// Draw Screen Label
	app_drawScreenLabel(&manualLabel);
	
	// Draw Door Button
	app_drawButton(&doorButton);
	
	// Draw Lights Button
	app_drawButton(&lightsButton);
	
	// Draw Heating Button
	app_drawButton(&HeatingButton);
	
	// Draw Fan Button
	app_drawButton(&fanButton);
	
	// Draw Treat Button
	app_drawButton(&treatButton);
	
	// Draw Alarm Button
	app_drawButton(&rasbButton);
	
	// Draw Home Button
	app_drawButton(&homeButton);
	
	// Handle user input
	app_userInputHandle(page, 7, manualButtons);
	
}

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
	int counter = 0;
	
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
	while((HAL_GPIO_ReadPin (GPIOB, pin->Pin)))
	{
		// Break out of loop if sensor is not responding
		counter++;
		if (counter > 300000)
		{
			break;
		}
	}
}

// Read the data of the tempreture sensor
int readData(GPIO_InitTypeDef* pin)
{
	int i,j;
	int counter = 0;
	
	for (j=0;j<8;j++)
	{
		// wait for the pin to go high
		while (!(HAL_GPIO_ReadPin (GPIOB, pin->Pin))) 
		{
			// Break out of loop if sensor is not responding
			counter++;
			if (counter > 300000)
			{
				break;
			}
		}
		DWT_Delay_us (40);   // wait for 40 us
		if ((HAL_GPIO_ReadPin (GPIOB, pin->Pin)) == 0)   // if the pin is low 
		{
			i&= ~(1<<(7-j));   // write 0
		}
		else {
			i|= (1<<(7-j));  // if the pin is high, write 1
		}
		// wait for the pin to go low
		counter = 0;
		while ((HAL_GPIO_ReadPin (GPIOB, pin->Pin)))
		{
			// Break out of loop if sensor is not responding
			counter++;
			if (counter > 300000)
			{
				break;
			}
		}
	}
	return i;
}


// Configure the Analog to Digital Converter
void ConfigureADC()
{
	__ADC3_CLK_ENABLE();

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
	
}
	
// Buzz
void buzz(void)
{
	GPIO_InitTypeDef pinD5 = {GPIO_PIN_0, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_HIGH};
	HAL_GPIO_WritePin(GPIOI, pinD5.Pin, GPIO_PIN_SET);
	osDelay(1000);
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

// Turn Fan ON
void turnOnFan(void)
{
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_6, GPIO_PIN_SET);
}

// Turn Fan OFF
void turnOffFan(void)
{
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_6, GPIO_PIN_RESET);
}


// Open Door (Used for both openning the door and starting the treat)
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
	
// Close Door (Uses Mutex to hold the resource to make sure the front of the door is clear before closing the door)
void app_closeDoor()
{
	int counter = 0;
	int g_ADCValueDoor = 0;
	ADC_ChannelConfTypeDef adcChannel;
	osMutexWait(stdio_mutex, osWaitForever);
	
	adcChannel.Channel = ADC_CHANNEL_7;
	adcChannel.Rank = 1;
	adcChannel.SamplingTime = ADC_SAMPLETIME_480CYCLES;
	adcChannel.Offset = 0;
	HAL_ADC_ConfigChannel(&g_AdcHandle, &adcChannel);
	HAL_ADC_Start(&g_AdcHandle);
	g_ADCValueDoor = HAL_ADC_GetValue(&g_AdcHandle);
		
	while (g_ADCValueDoor < 3300 || g_ADCValueDoor > 4095)
	{
		g_ADCValueDoor = HAL_ADC_GetValue(&g_AdcHandle);
	}
	
	while(counter < 10)
	{
		HAL_GPIO_WritePin(GPIOH, GPIO_PIN_6, GPIO_PIN_SET);
		milDelay(1);
		HAL_GPIO_WritePin(GPIOH, GPIO_PIN_6, GPIO_PIN_RESET);
		milDelay(22);
		counter++;
	}
	osMutexRelease(stdio_mutex);
}
	
// stop treat
void app_stopTreat(void)
{
	int counter = 0;
	while(counter < 10)
	{
		HAL_GPIO_WritePin(GPIOI, GPIO_PIN_3, GPIO_PIN_SET);
		milDelay(1);
		HAL_GPIO_WritePin(GPIOI, GPIO_PIN_3, GPIO_PIN_RESET);
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
void app_drawClock()
{
		char buffer[128];
		GLCD_SetBackgroundColor (GLCD_COLOR_LIGHT_GREY);
		GLCD_SetForegroundColor (GLCD_COLOR_WHITE);
		GLCD_SetFont (&GLCD_Font_16x24);
		sprintf(buffer, "%d : %d : %d", clock.hour,clock.minute, clock.second);
		GLCD_DrawString (clock.posX, clock.posY, "              ");
		GLCD_DrawString (clock.posX, clock.posY, buffer);
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
void app_clockTicToc(void const *argument)
{
		clock.tic = HAL_GetTick()/10;
		if (clock.tic != clock.toc) { /* 10 ms update */
			clock.toc = clock.tic;
			clock.second = (clock.elapsed_t/100)%60; /* update time */
			clock.minute = (clock.elapsed_t/6000)%60;
			clock.hour = (clock.elapsed_t/360000)%24;
			clock.elapsed_t = (clock.elapsed_t+1) % DAY;
		}
}

// Update water level
void app_updateWaterLevel(Bargraph *bargraph)
{
	ADC_ChannelConfTypeDef adcChannel;
	int g_ADCValueWater = 0;
	
	adcChannel.Channel = ADC_CHANNEL_0;
	adcChannel.Rank = 1;
	adcChannel.SamplingTime = ADC_SAMPLETIME_480CYCLES;
	adcChannel.Offset = 0;
	HAL_ADC_ConfigChannel(&g_AdcHandle, &adcChannel);
	HAL_ADC_Start(&g_AdcHandle);
	g_ADCValueWater = HAL_ADC_GetValue(&g_AdcHandle);

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
	ADC_ChannelConfTypeDef adcChannel;
	int g_ADCValueFood = 0;
	
	adcChannel.Channel = ADC_CHANNEL_8;
	adcChannel.Rank = 1;
	adcChannel.SamplingTime = ADC_SAMPLETIME_480CYCLES;
	adcChannel.Offset = 0;
	HAL_ADC_ConfigChannel(&g_AdcHandle, &adcChannel);
	HAL_ADC_Start(&g_AdcHandle);
	g_ADCValueFood = HAL_ADC_GetValue(&g_AdcHandle);
	
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
	uint8_t rhByte1 = 0, tempByte1 = 0;
	char buffer[128];
	GPIO_InitTypeDef pinD3 = {GPIO_PIN_4, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_LOW};
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
		rhByte1 = readData(&pinD3);
		readData(&pinD3);
		tempByte1 = readData(&pinD3);
		readData(&pinD3);
		readData(&pinD3);
	}
	
	if (rhByte1 != 0 && tempByte1 != 0)
	{
		GLCD_DrawString (20, 50, "H: ");
		sprintf(buffer, "%d", rhByte1);
		GLCD_DrawString (50, 50, "  ");
		GLCD_DrawString (50, 50, buffer);
		
		GLCD_DrawString (20, 90, "T: ");
		sprintf(buffer, "%d", tempByte1);
		GLCD_DrawString (50, 90, "  ");
		GLCD_DrawString (50, 90, buffer);
	}
	
	if (tempByte1 > 23 && tempByte1 < 25 && tempByte1 != 0)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
		turnOffFan();
	} else if (tempByte1 > 25 && tempByte1 != 0){
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);
		turnOnFan();
	} else if (tempByte1 < 23 && tempByte1 != 0){
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
		turnOffFan();
	} else{}
}


// Page specific logic
void app_homePageSpecific()
{
	app_updateFoodLevel(&waterBargraph);
	app_updateWaterLevel(&foodBargraph);
	
	if (HAL_GetTick()%200 == 0 )
	{
		app_updateTempreture();
	}
}

// Handle sensor type
void app_handleSensor(Button *button, short pin)
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
		} else if (strcmp(button->funtionality->type, "day") == 0){
			buzz();
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
			app_closeDoor();
			turnOffWheel();
		} else if (strcmp(button->funtionality->type, "night") == 0){
			buzz();
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
			app_closeDoor();
			turnOffWheel();
		} else if (strcmp(button->funtionality->type, "play") == 0){
			buzz();
			app_openDoor(&doorButton, GPIO_PIN_6);
			turnOnWheel();
		} else {}
	} else {
		if (strcmp(button->funtionality->type, "pwm") == 0)
		{
			//GLCD_DrawString (30, 100, button->label);
			if (strcmp(button->label, "Door") == 0)
			{
				//GLCD_DrawString (30, 70, "wowow");
				button->funtionality->state = 0;
				app_closeDoor();
			} else {
				app_stopTreat();
				button->funtionality->state = 0;
			}
			button->funtionality->state = 0;
		} else if (strcmp(button->funtionality->type, "digital") == 0){
			HAL_GPIO_WritePin(button->funtionality->base, pin, GPIO_PIN_RESET);
			button->funtionality->state = 0;
		} else {}
	}
}

// User input handler
void app_userInputHandle(char **page, short numOfButtons, Button **buttons)
{
	unsigned short i = 0;
	char *currentPage = *page;
	TOUCH_STATE tscState;
	clock.elapsed_t = clock.second*100+clock.minute*60*100+clock.hour*60*60*100;
	

	while(1)
	{
		if (strcmp(*page, currentPage) == 0)
		{
			
			// Create thread for the clock functionality
			tid_clock = osThreadCreate(osThread(app_clockTicToc), NULL);
			osSignalSet(tid_clock, 0x0001);
			app_drawClock();
			
			if (strcmp(*page, "Home") == 0)
			{
				app_homePageSpecific();
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
							app_handleSensor(buttons[i], CN4Pins[buttons[i]->funtionality->pin]->Pin);
							osDelay(600);
						}
					}
				}
			}
		} else {
			break;
		}
	}
	
}


