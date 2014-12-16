#include "digitdisplay.h"

extern volatile uint32_t msTicks;

// For initial clock display.
uint32_t fifthDigitX = 7;
uint32_t sixthDigitX = 13;
uint32_t middleDotsX = 11;

uint32_t digitYTopRow = 0;
uint32_t digitYBottomRow = 9;

// For stopwatch display.

uint32_t digitYMiddle = 5;

// For both displays.

uint32_t firstDigitX = 1;
uint32_t secondDigitX = 6;
uint32_t thirdDigitX = 14;
uint32_t fourthDigitX = 19;

uint32_t digitWidthOutside = 4;
uint32_t digitWidthInside = 2;
	
uint32_t digitHeightOutside = 7;
uint32_t digitHeightInside = 5;

// Set the time at which the stopwatch

uint32_t alarmMinutes = 0;
uint32_t alarmSeconds = 10;

// Initialize LED Pins. 

void InitLEDPins(void) 
{
	// This strucct sets options for pin.
	GPIO_InitTypeDef GPIO_InitDef;
	// Enable pin clock which is set inside Reset and Clock Control
	// All GPIO on AHB1 bus.
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
 
	// Pins 12, 13, 14 and 15 correspond to the four LEDs
	GPIO_InitDef.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT; 			// Output mode
  GPIO_InitDef.GPIO_OType = GPIO_OType_PP;			// Output type - push-pull
  GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_NOPULL;		// Without pull resistors
  GPIO_InitDef.GPIO_Speed = GPIO_Speed_100MHz;	// 100 Hz pin
  //Initialize pins to port GPIOD
  GPIO_Init(GPIOD, &GPIO_InitDef);
}

// Initialize the display.
void InitButton()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void drawSixthDigit(HT1632LEDMatrix matrix, uint32_t *seconds)
{
	// Initially clear the fourth digit.
	//matrix.fillRect(sixthDigitX, digitYBottomRow, digitWidthOutside, digitHeightOutside, 0);
	//matrix.writeScreen();
	
	uint32_t lastSecondsDigit = *seconds % 10;
	
	switch(lastSecondsDigit)
	{
		case 0:
			drawZero(matrix, sixthDigitX, digitYBottomRow);
			break;
		case 1:
			drawOne(matrix, sixthDigitX, digitYBottomRow);
			break;
		case 2:
			drawTwo(matrix, sixthDigitX, digitYBottomRow);
			break;
		case 3:
			drawThree(matrix, sixthDigitX, digitYBottomRow);
			break;
		case 4:
			drawFour(matrix, sixthDigitX, digitYBottomRow);
			break;
		case 5:
			drawFive(matrix, sixthDigitX, digitYBottomRow);
			break;
		case 6:
			drawSix(matrix, sixthDigitX, digitYBottomRow);
			break;
		case 7:
			drawSeven(matrix, sixthDigitX, digitYBottomRow);
			break;
		case 8:
			drawEight(matrix, sixthDigitX, digitYBottomRow);
			break;
		case 9:
			drawNine(matrix, sixthDigitX, digitYBottomRow);
			break;
	}
	matrix.writeScreen();
}

void drawFifthDigit(HT1632LEDMatrix matrix, uint32_t *seconds)
{
	// Initially clear the fourth digit.
	//matrix.fillRect(fifthDigitX, digitYBottomRow, digitWidthOutside, digitHeightOutside, 0);
	//matrix.writeScreen();
	
	uint32_t firstSecondsDigit = *seconds / 10;
	
	switch(firstSecondsDigit)
	{
		case 0:
			drawZero(matrix, fifthDigitX, digitYBottomRow);
			break;
		case 1:
			drawOne(matrix, fifthDigitX, digitYBottomRow);
			break;
		case 2:
			drawTwo(matrix, fifthDigitX, digitYBottomRow);
			break;
		case 3:
			drawThree(matrix, fifthDigitX, digitYBottomRow);
			break;
		case 4:
			drawFour(matrix, fifthDigitX, digitYBottomRow);
			break;
		case 5:
			drawFive(matrix, fifthDigitX, digitYBottomRow);
			break;
	}
	matrix.writeScreen();
}

void drawFourthDigit(HT1632LEDMatrix matrix, uint32_t *minutes)
{
	// Initially clear the fourth digit.
	//matrix.fillRect(fourthDigitX, digitYTopRow, digitWidthOutside, digitHeightOutside, 0);
	//matrix.writeScreen();
	
	uint32_t lastMinutesDigit = *minutes % 10;
	
	switch(lastMinutesDigit)
	{
		case 0:
			drawZero(matrix, fourthDigitX, digitYTopRow);
			break;
		case 1:
			drawOne(matrix, fourthDigitX, digitYTopRow);
			break;
		case 2:
			drawTwo(matrix, fourthDigitX, digitYTopRow);
			break;
		case 3:
			drawThree(matrix, fourthDigitX, digitYTopRow);
			break;
		case 4:
			drawFour(matrix, fourthDigitX, digitYTopRow);
			break;
		case 5:
			drawFive(matrix, fourthDigitX, digitYTopRow);
			break;
		case 6:
			drawSix(matrix, fourthDigitX, digitYTopRow);
			break;
		case 7:
			drawSeven(matrix, fourthDigitX, digitYTopRow);
			break;
		case 8:
			drawEight(matrix, fourthDigitX, digitYTopRow);
			break;
		case 9:
			drawNine(matrix, fourthDigitX, digitYTopRow);
			break;
	}
	matrix.writeScreen();
}

void drawThirdDigit(HT1632LEDMatrix matrix, uint32_t *minutes)
{
	// Initially clear the fourth digit.
	//matrix.fillRect(thirdDigitX, digitYTopRow, digitWidthOutside, digitHeightOutside, 0);
	//matrix.writeScreen();
	
	uint32_t firstMinutesDigit = *minutes / 10;
	
	switch(firstMinutesDigit)
	{
		case 0:
			drawZero(matrix, thirdDigitX, digitYTopRow);
			break;
		case 1:
			drawOne(matrix, thirdDigitX, digitYTopRow);
			break;
		case 2:
			drawTwo(matrix, thirdDigitX, digitYTopRow);
			break;
		case 3:
			drawThree(matrix, thirdDigitX, digitYTopRow);
			break;
		case 4:
			drawFour(matrix, thirdDigitX, digitYTopRow);
			break;
		case 5:
			drawFive(matrix, thirdDigitX, digitYTopRow);
			break;
	}
	matrix.writeScreen();
}

void drawSecondDigit(HT1632LEDMatrix matrix, uint32_t *hours)
{
	// Initially clear the fourth digit.
	//matrix.fillRect(secondDigitX, digitYTopRow, digitWidthOutside, digitHeightOutside, 0);
	//matrix.writeScreen();
	
	uint32_t lastHoursDigit = *hours % 10;
	
	switch(lastHoursDigit)
	{
		case 0:
			drawZero(matrix, secondDigitX, digitYTopRow);
			break;
		case 1:
			drawOne(matrix, secondDigitX, digitYTopRow);
			break;
		case 2:
			drawTwo(matrix, secondDigitX, digitYTopRow);
			break;
		case 3:
			drawThree(matrix, secondDigitX, digitYTopRow);
			break;
		case 4:
			drawFour(matrix, secondDigitX, digitYTopRow);
			break;
		case 5:
			drawFive(matrix, secondDigitX, digitYTopRow);
			break;
		case 6:
			drawSix(matrix, secondDigitX, digitYTopRow);
			break;
		case 7:
			drawSeven(matrix, secondDigitX, digitYTopRow);
			break;
		case 8:
			drawEight(matrix, secondDigitX, digitYTopRow);
			break;
		case 9:
			drawNine(matrix, secondDigitX, digitYTopRow);
			break;
	}
	matrix.writeScreen();
}


void drawFirstDigit(HT1632LEDMatrix matrix, uint32_t *hours)
{
	// Initially clear the fourth digit.
	//matrix.fillRect(firstDigitX, digitYTopRow, digitWidthOutside, digitHeightOutside, 0);
	//matrix.writeScreen();
	
	uint32_t firstHoursDigit = *hours / 10;
	
	switch(firstHoursDigit)
	{
		case 0:
			drawZero(matrix, firstDigitX, digitYTopRow);
			break;
		case 1:
			drawOne(matrix, firstDigitX, digitYTopRow);
			break;
		case 2:
			drawTwo(matrix, firstDigitX, digitYTopRow);
			break;
	}
	matrix.writeScreen();
}

void drawZero(HT1632LEDMatrix matrix, uint32_t digitNumberX, uint32_t digitNumberY)
{
	matrix.fillRect(digitNumberX, digitNumberY, digitWidthOutside, digitHeightOutside, 1);
	matrix.fillRect(digitNumberX + 1, digitNumberY + 1, digitWidthInside, digitHeightInside, 0);
}

void drawOne(HT1632LEDMatrix matrix, uint32_t digitNumberX, uint32_t digitNumberY)
{
	matrix.fillRect(digitNumberX, digitNumberY, digitWidthOutside, digitHeightOutside, 1);
	matrix.fillRect(digitNumberX, digitNumberY, digitWidthInside + 1, digitHeightInside + 2, 0);
}

void drawTwo(HT1632LEDMatrix matrix, uint32_t digitNumberX, uint32_t digitNumberY)
{
	matrix.fillRect(digitNumberX, digitNumberY, digitWidthOutside, digitHeightOutside, 1);
	matrix.fillRect(digitNumberX, digitNumberY + 1, digitWidthInside + 1, digitHeightInside - 3, 0);
	matrix.fillRect(digitNumberX + 1, digitNumberY + 4, digitWidthInside + 1, digitHeightInside - 3, 0);
}

void drawThree(HT1632LEDMatrix matrix, uint32_t digitNumberX, uint32_t digitNumberY)
{
	matrix.fillRect(digitNumberX, digitNumberY, digitWidthOutside, digitHeightOutside, 1);
	matrix.fillRect(digitNumberX, digitNumberY + 1, digitWidthInside + 1, digitHeightInside - 3, 0);
	matrix.fillRect(digitNumberX, digitNumberY + 4, digitWidthInside + 1, digitHeightInside - 3, 0);
}

void drawFour(HT1632LEDMatrix matrix, uint32_t digitNumberX, uint32_t digitNumberY)
{
	matrix.fillRect(digitNumberX, digitNumberY, digitWidthOutside, digitHeightOutside, 1);
	matrix.fillRect(digitNumberX + 1, digitNumberY, digitWidthInside, digitHeightInside - 2, 0);
	matrix.fillRect(digitNumberX, digitNumberY + 4, digitWidthInside + 1, digitHeightInside - 2, 0);
}

void drawFive(HT1632LEDMatrix matrix, uint32_t digitNumberX, uint32_t digitNumberY)
{
	matrix.fillRect(digitNumberX, digitNumberY, digitWidthOutside, digitHeightOutside, 1);
	matrix.fillRect(digitNumberX + 1, digitNumberY + 1, digitWidthInside + 1, digitHeightInside - 3, 0);
	matrix.fillRect(digitNumberX, digitNumberY + 4, digitWidthInside + 1, digitHeightInside - 3, 0);
}

void drawSix(HT1632LEDMatrix matrix, uint32_t digitNumberX, uint32_t digitNumberY)
{
	matrix.fillRect(digitNumberX, digitNumberY, digitWidthOutside, digitHeightOutside, 1);
	matrix.fillRect(digitNumberX + 1, digitNumberY + 1, digitWidthInside + 1, digitHeightInside - 3, 0);
	matrix.fillRect(digitNumberX + 1, digitNumberY + 4, digitWidthInside, digitHeightInside - 3, 0);
}

void drawSeven(HT1632LEDMatrix matrix, uint32_t digitNumberX, uint32_t digitNumberY)
{
	matrix.fillRect(digitNumberX, digitNumberY, digitWidthOutside, digitHeightOutside, 1);
	matrix.fillRect(digitNumberX, digitNumberY + 1, digitWidthInside + 1, digitHeightInside + 1, 0);
}

void drawEight(HT1632LEDMatrix matrix, uint32_t digitNumberX, uint32_t digitNumberY)
{
	matrix.fillRect(digitNumberX, digitNumberY, digitWidthOutside, digitHeightOutside, 1);
	matrix.fillRect(digitNumberX + 1, digitNumberY + 1, digitWidthInside, digitHeightInside - 3, 0);
	matrix.fillRect(digitNumberX + 1, digitNumberY + 4, digitWidthInside, digitHeightInside - 3, 0);
}

void drawNine(HT1632LEDMatrix matrix, uint32_t digitNumberX, uint32_t digitNumberY)
{
	matrix.fillRect(digitNumberX, digitNumberY, digitWidthOutside, digitHeightOutside, 1);
	matrix.fillRect(digitNumberX + 1, digitNumberY + 1, digitWidthInside, digitHeightInside - 3, 0);
	matrix.fillRect(digitNumberX, digitNumberY + 4, digitWidthInside + 1, digitHeightInside - 3, 0);
}

void drawMiddleTwoDots(HT1632LEDMatrix matrix)
{
	// Draw the middle two dots by clearing...
	matrix.fillRect(middleDotsX, digitYTopRow + 1, 2, 2, 1);
	matrix.fillRect(middleDotsX, digitYTopRow + 4, 2, 2, 1);
			
	matrix.writeScreen();
}

void eraseMiddleTwoDots(HT1632LEDMatrix matrix)
{
	// Draw the middle two dots by clearing...
	matrix.fillRect(middleDotsX, digitYTopRow + 5, 2, 2, 0);
	matrix.fillRect(middleDotsX, digitYTopRow + 8, 2, 2, 0);
			
	matrix.writeScreen();
}

void calculateTime(uint32_t elapsedTime, uint32_t *hours, uint32_t *minutes, uint32_t *seconds)
{
	*seconds = *seconds + 1;
	
	// Set the minutes.
	if(*seconds == 60)
	{
		*minutes = *minutes + 1;
		*seconds = 0;
	}
	// Set the hours.
	if(*minutes == 60)
	{
		*hours = *hours + 1;
		*minutes = 0;
	}
	// Reset the hours.
	// Since the maximum time allowed is 23:59:59, this is placed last.
	if(*hours == 24)
	{
		*hours = 0;
	}
	
	//printf("%d:%d:%d\n", *hours, *minutes, *seconds);
	//*hours = elapsedTime / 3600000;
	//*minutes = elapsedTime / 60000;
	//*seconds = elapsedTime / 1000;
}

void initStopwatchDisplay(HT1632LEDMatrix matrix)
{
	// First Digit
	// Zero...
	matrix.fillRect(firstDigitX, digitYMiddle, digitWidthOutside, digitHeightOutside, 1);
	matrix.fillRect(firstDigitX + 1, digitYMiddle + 1, digitWidthInside, digitHeightInside, 0);
	
	// Second Digit
	// Zero...
	matrix.fillRect(secondDigitX, digitYMiddle, digitWidthOutside, digitHeightOutside, 1);
	matrix.fillRect(secondDigitX + 1, digitYMiddle + 1, digitWidthInside, digitHeightInside, 0);
	
	// Third Digit
	// Zero...
	matrix.fillRect(thirdDigitX, digitYMiddle, digitWidthOutside, digitHeightOutside, 1);
	matrix.fillRect(thirdDigitX + 1, digitYMiddle + 1, digitWidthInside, digitHeightInside, 0);
	
	// Fourth Digit
	// Zero...
	matrix.fillRect(fourthDigitX, digitYMiddle, digitWidthOutside, digitHeightOutside, 1);
	matrix.fillRect(fourthDigitX + 1, digitYMiddle + 1, digitWidthInside, digitHeightInside, 0);
	
	matrix.writeScreen();
}

void drawStopwatchFirstDigit(HT1632LEDMatrix matrix, uint32_t *minutes)
{
	uint32_t firstHoursDigit = *minutes / 10;
	
	switch(firstHoursDigit)
	{
		case 0:
			drawZero(matrix, firstDigitX, digitYMiddle);
			break;
		case 1:
			drawOne(matrix, firstDigitX, digitYMiddle);
			break;
		case 2:
			drawTwo(matrix, firstDigitX, digitYMiddle);
			break;
		case 3:
			drawThree(matrix, firstDigitX, digitYMiddle);
			break;
		case 4:
			drawFour(matrix, firstDigitX, digitYMiddle);
			break;
		case 5:
			drawFive(matrix, firstDigitX, digitYMiddle);
			break;
	}
	matrix.writeScreen();
}

void drawStopwatchSecondDigit(HT1632LEDMatrix matrix, uint32_t *minutes)
{
	uint32_t lastMinutesDigit = *minutes % 10;
	
	switch(lastMinutesDigit)
	{
		case 0:
			drawZero(matrix, secondDigitX, digitYMiddle);
			break;
		case 1:
			drawOne(matrix, secondDigitX, digitYMiddle);
			break;
		case 2:
			drawTwo(matrix, secondDigitX, digitYMiddle);
			break;
		case 3:
			drawThree(matrix, secondDigitX, digitYMiddle);
			break;
		case 4:
			drawFour(matrix, secondDigitX, digitYMiddle);
			break;
		case 5:
			drawFive(matrix, secondDigitX, digitYMiddle);
			break;
		case 6:
			drawSix(matrix, secondDigitX, digitYMiddle);
			break;
		case 7:
			drawSeven(matrix, secondDigitX, digitYMiddle);
			break;
		case 8:
			drawEight(matrix, secondDigitX, digitYMiddle);
			break;
		case 9:
			drawNine(matrix, secondDigitX, digitYMiddle);
			break;
	}
	matrix.writeScreen();
}

void drawStopwatchThirdDigit(HT1632LEDMatrix matrix, uint32_t *seconds)
{
	uint32_t firstSecondsDigit = *seconds / 10;
	
	switch(firstSecondsDigit)
	{
		case 0:
			drawZero(matrix, thirdDigitX, digitYMiddle);
			break;
		case 1:
			drawOne(matrix, thirdDigitX, digitYMiddle);
			break;
		case 2:
			drawTwo(matrix, thirdDigitX, digitYMiddle);
			break;
		case 3:
			drawThree(matrix, thirdDigitX, digitYMiddle);
			break;
		case 4:
			drawFour(matrix, thirdDigitX, digitYMiddle);
			break;
		case 5:
			drawFive(matrix, thirdDigitX, digitYMiddle);
			break;
	}
	matrix.writeScreen();
}

void drawStopwatchFourthDigit(HT1632LEDMatrix matrix, uint32_t *seconds)
{
	uint32_t lastSecondsDigit = *seconds % 10;
	
	switch(lastSecondsDigit)
	{
		case 0:
			drawZero(matrix, fourthDigitX, digitYMiddle);
			break;
		case 1:
			drawOne(matrix, fourthDigitX, digitYMiddle);
			break;
		case 2:
			drawTwo(matrix, fourthDigitX, digitYMiddle);
			break;
		case 3:
			drawThree(matrix, fourthDigitX, digitYMiddle);
			break;
		case 4:
			drawFour(matrix, fourthDigitX, digitYMiddle);
			break;
		case 5:
			drawFive(matrix, fourthDigitX, digitYMiddle);
			break;
		case 6:
			drawSix(matrix, fourthDigitX, digitYMiddle);
			break;
		case 7:
			drawSeven(matrix, fourthDigitX, digitYMiddle);
			break;
		case 8:
			drawEight(matrix, fourthDigitX, digitYMiddle);
			break;
		case 9:
			drawNine(matrix, fourthDigitX, digitYMiddle);
			break;
	}
	matrix.writeScreen();
}

void calculateStopwatchTime(uint32_t elapsedTime, uint32_t *minutes, uint32_t *seconds)
{
	*seconds = *seconds + 1;
	
	// Set the minutes.
	if(*seconds == 60)
	{
		*minutes = *minutes + 1;
		*seconds = 0;
	}
	// Set the hours.
	if(*minutes == 60)
	{
		*minutes = 0;
	}
	//printf("%d:%d:%d\n", *hours, *minutes, *seconds);
	//*hours = elapsedTime / 3600000;
	//*minutes = elapsedTime / 60000;
	//*seconds = elapsedTime / 1000;
}

void drawStopwatchMiddleTwoDots(HT1632LEDMatrix matrix)
{
	// Draw the middle two dots by clearing...
	matrix.fillRect(middleDotsX, digitYMiddle + 1, 2, 2, 1);
	matrix.fillRect(middleDotsX, digitYMiddle + 4, 2, 2, 1);
			
	matrix.writeScreen();
}

void erasestopWatchMiddleTwoDots(HT1632LEDMatrix matrix)
{
	// Draw the middle two dots by clearing...
	matrix.fillRect(middleDotsX, digitYMiddle + 5, 2, 2, 0);
	matrix.fillRect(middleDotsX, digitYMiddle + 8, 2, 2, 0);
			
	matrix.writeScreen();
}

// Helper function to perform blinking of STM32F4 LEDs
void Delay (uint32_t dlyTicks) 
{                                              
  uint32_t curTicks;

  curTicks = msTicks;
  while ((msTicks - curTicks) < dlyTicks);
}

void timeAlert(uint32_t *minutes, uint32_t *seconds)
{
	// Only ten seconds into the stopwatch counting.
	//if(alarmMinutes == *minutes && alarmSeconds == *seconds)
	// This implementation is for every 10 seconds.
	if(*seconds % alarmSeconds == 0)
	{
		GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
		Delay(50);
		GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
		Delay(200);
		GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
	}
	else
	{
		GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
	}
}

void initialDisplay(HT1632LEDMatrix matrix, uint32_t *hours, uint32_t *minutes, uint32_t *seconds)
{
	drawSixthDigit(matrix, seconds);
	drawFifthDigit(matrix, seconds);
		
	// Fourth and Third Digits for Minutes.
	drawFourthDigit(matrix, minutes);
	drawThirdDigit(matrix, minutes);
		
	// Second and Firsth Digits for Hours.
	drawSecondDigit(matrix, hours);
	drawFirstDigit(matrix, hours);
	
	matrix.writeScreen();
}
