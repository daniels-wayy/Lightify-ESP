#ifndef EFFECTS_H
#define EFFECTS_H

#include <Arduino.h>
#include <FastLED.h>
#include "data/data.h"
#include "timer/timer.h"

extern CRGB leds[LED_AMOUNT];
extern DeviceData data;
extern ModeType modes[MODE_AMOUNT];
extern boolean loadingFlag;

void effectsTick();

//
//
//
// EFFECTS

void lavaNoise();
void cloudsNoiseRoutine();
void forestNoiseRoutine();
void oceanNoiseRoutine();
void fireRoutine();

//
//
//
// HELPERS
void fillNoiseLED();
void drawPixelXY(int8_t x, int8_t y, CRGB color);
uint16_t getPixelNumber(int8_t x, int8_t y);
uint16_t XY(uint8_t x, uint8_t y);
void fillAll(CRGB color);
uint32_t getPixColor(int thisSegm);
uint32_t getPixColorXY(int8_t x, int8_t y);
void generateLine();
void shiftUp();
void drawFrame(int pcnt);

#endif