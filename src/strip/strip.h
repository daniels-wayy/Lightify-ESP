#ifndef STRIP_H
#define STRIP_H

#include <FastLED.h>
#include "data/data.h"
#include "timer/timer.h"

extern CRGB leds[LED_AMOUNT];
extern DeviceData data;

void animation();
void loadAnimation(CRGB color);
void pulse();

#endif