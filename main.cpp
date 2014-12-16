/*
	Clock Display / Stopwatch Implementation Using Adafruit 16x24 LED Display Board
	Interfaced with STM32F4 Discovery Board

	Ken Chan
*/

#include "HT1632.h"
#include "stm32f4xx.h"
#include "digitdisplay.h"

#define DATA 2
#define WR   3
#define CS   4
#define CS2  5

extern "C"
{
	volatile uint32_t msTicks = 0;                      /* counts 1ms timeTicks       */

	// SysTick Handler (Interrupt Service Routine for the System Tick interrupt)
	void SysTick_Handler(void)
	{
		msTicks++;
	}

	// Initialize the system tick 
	void InitSystick(void)
	{
		SystemCoreClockUpdate();                      /* Get Core Clock Frequency   */
		if (SysTick_Config(SystemCoreClock / 1000)) { /* SysTick 1 msec interrupts  */
			while (1);                                  /* Capture error              */
		}
	}
}

// Bit-bashing: technique for serial communications using software instead of dedicated hardware
// Consumes processor resources.
int main(void)
{
	// Initializations
	InitSystick();
	InitButton();
	InitLEDPins();
	
	uint8_t buttonPress = 0;
	
	uint32_t msPrev = 0;
	uint32_t msDiff = 0;
	
	uint32_t timeButtonPrev = 0;
	uint32_t timeButtonDiff = 0;
	
	uint32_t hours = 0;
	uint32_t minutes = 0;
	uint32_t seconds = 0;
	
	uint32_t stopwatchMinutes = 0;
	uint32_t stopwatchSeconds = 0;
	
	// use this line for single matrix
	HT1632LEDMatrix matrix = HT1632LEDMatrix(DATA, WR, CS);
	// use this line for two matrices!
	//HT1632LEDMatrix matrix = HT1632LEDMatrix(DATA, WR, CS, CS2);
	
	matrix.begin(HT1632_COMMON_16NMOS);
	matrix.clearScreen(); 
	
	initialDisplay(matrix, &hours, &minutes, &seconds);
	
	// Bottom Left Rectangle
	matrix.fillRect(0, 9, 6, 7, 1);
	// Bottom Right Rectangle
	matrix.fillRect(18, 9, 6, 7, 1);
	// Draw middle two dots.
	drawMiddleTwoDots(matrix);

	//printf("\n\n");
			
	//printf("MSTicks: %d\n", msTicks);
	//printf("msPrev: %d\n", msPrev);
	while(1)
	{
		if(msTicks - msPrev >= 1000 && buttonPress == 0)
		{	
			calculateTime(msTicks, &hours, &minutes, &seconds);
			//eraseMiddleTwoDots(matrix);
			// Sixth and Fifth Digits for Seconds.
			drawSixthDigit(matrix, &seconds);
			drawFifthDigit(matrix, &seconds);
			if(seconds == 0)
			{
				// Fourth and Third Digits for Minutes.
				drawFourthDigit(matrix, &minutes);
				drawThirdDigit(matrix, &minutes);
			}
			if(minutes == 0)
			{
				// Second and Firsth Digits for Hours.
				drawSecondDigit(matrix, &hours);
				drawFirstDigit(matrix, &hours);
			}
			//printf("\n\n");
			msPrev = msTicks;
		}
				
		if(msTicks - msPrev >= 1000 && buttonPress == 1)
		{
			calculateTime(msTicks, &hours, &minutes, &seconds);
			msPrev = msTicks;
		}
		
		if(GPIOA->IDR & 0x0001)
		{
			// If the button was not pressed previously.
			if(buttonPress == 0)
			{
				matrix.clearScreen();
				initStopwatchDisplay(matrix);
						
				// Top Lines
				matrix.fillRect(0, 0, matrix.width(), 2, 1);
				// Bottom Lines
				matrix.fillRect(0, matrix.height() - 2, matrix.width(), 2, 1);
				drawStopwatchMiddleTwoDots(matrix);
						
				buttonPress = 1;
				timeButtonPrev = msTicks;
			}
			
			// If the button is pressed.
			if(buttonPress == 1)
			{
				if(msTicks - timeButtonPrev >= 1000)
				{
					calculateStopwatchTime(msTicks, &stopwatchMinutes, &stopwatchSeconds);
								
					timeAlert(&stopwatchMinutes, &stopwatchSeconds);
								
					drawStopwatchFourthDigit(matrix, &stopwatchSeconds);
					drawStopwatchThirdDigit(matrix, &stopwatchSeconds);
					
					if(stopwatchSeconds == 0)
					{
						drawStopwatchSecondDigit(matrix, &stopwatchMinutes);
						drawStopwatchFirstDigit(matrix, &stopwatchMinutes);
					}
								
					timeButtonPrev = msTicks;
				}
			}			
		}
		
		// Stop pressing the button.
		if(!(GPIOA->IDR & 0x0001) && buttonPress == 1) 
		{
			buttonPress = 0;
			stopwatchSeconds = 0;
			stopwatchMinutes = 0;
			
			matrix.clearScreen();
			
			// Bottom Left Rectangle
			matrix.fillRect(0, 9, 6, 7, 1);
			// Bottom Right Rectangle
			matrix.fillRect(18, 9, 6, 7, 1);
			// Draw the middle two dots.
			drawMiddleTwoDots(matrix);
			//matrix.writeScreen();
					
			// Sixth and Fifth Digits for Seconds.
			drawSixthDigit(matrix, &seconds);
			drawFifthDigit(matrix, &seconds);
			// Fourth and Third Digits for Minutes.
			drawFourthDigit(matrix, &minutes);
			drawThirdDigit(matrix, &minutes);
			// Second and Firsth Digits for Hours.
			drawSecondDigit(matrix, &hours);
			drawFirstDigit(matrix, &hours);
					
		}
	}
}
