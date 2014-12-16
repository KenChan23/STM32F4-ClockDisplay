#ifndef DIGITDISPLAY
#define DIGITDISPLAY

#include "HT1632.h"

void InitLEDPins(void);
void InitButton(void);

// Clock Functions

void initialDisplay(HT1632LEDMatrix matrix, uint32_t *hours, uint32_t *minutes, uint32_t *seconds);

void drawFirstDigit(HT1632LEDMatrix matrix, uint32_t *hours);
void drawSecondDigit(HT1632LEDMatrix matrix, uint32_t *hours);
void drawThirdDigit(HT1632LEDMatrix matrix, uint32_t *minutes);
void drawFourthDigit(HT1632LEDMatrix matrix, uint32_t *minutes);
void drawFifthDigit(HT1632LEDMatrix matrix, uint32_t *seconds);
void drawSixthDigit(HT1632LEDMatrix matrix, uint32_t *seconds);

void drawZero(HT1632LEDMatrix matrix, uint32_t digitNumberX, uint32_t digitNumberY);
void drawOne(HT1632LEDMatrix matrix, uint32_t digitNumberX, uint32_t digitNumberY);
void drawTwo(HT1632LEDMatrix matrix, uint32_t digitNumberX, uint32_t digitNumberY);
void drawThree(HT1632LEDMatrix matrix, uint32_t digitNumberX, uint32_t digitNumberY);
void drawFour(HT1632LEDMatrix matrix, uint32_t digitNumberX, uint32_t digitNumberY);
void drawFive(HT1632LEDMatrix matrix, uint32_t digitNumberX, uint32_t digitNumberY);
void drawSix(HT1632LEDMatrix matrix, uint32_t digitNumberX, uint32_t digitNumberY);
void drawSeven(HT1632LEDMatrix matrix, uint32_t digitNumberX, uint32_t digitNumberY);
void drawEight(HT1632LEDMatrix matrix, uint32_t digitNumberX, uint32_t digitNumberY);
void drawNine(HT1632LEDMatrix matrix, uint32_t digitNumberX, uint32_t digitNumberY);

void drawMiddleTwoDots(HT1632LEDMatrix matrix);
void eraseMiddleTwoDots(HT1632LEDMatrix matrix);

void calculateTime(uint32_t elapsedTime, uint32_t *hours, uint32_t *minutes, uint32_t *seconds);

// Stopwatch Functions

void initStopwatchDisplay(HT1632LEDMatrix matrix);

void drawStopwatchFirstDigit(HT1632LEDMatrix matrix, uint32_t *minutes);
void drawStopwatchSecondDigit(HT1632LEDMatrix matrix, uint32_t *minutes);
void drawStopwatchThirdDigit(HT1632LEDMatrix matrix, uint32_t *seconds);
void drawStopwatchFourthDigit(HT1632LEDMatrix matrix, uint32_t *seconds);

void drawStopwatchMiddleTwoDots(HT1632LEDMatrix matrix);
void eraseStopwatchMiddleTwoDots(HT1632LEDMatrix matrix);

void calculateStopwatchTime(uint32_t elapsedTime, uint32_t *minutes, uint32_t *seconds);

// Blink LEDs if the stopwatch reaches a particular time.

void timeAlert(uint32_t *minutes, uint32_t *seconds);

#endif