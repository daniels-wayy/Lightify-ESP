#ifndef STRIP_H
#define STRIP_H

#include <FastLED.h>
#include "data/data.h"
#include "timer/timer.h"
#include "effects/effects.h"

extern CRGB leds[LED_AMOUNT];
extern DeviceData data;
extern ModeType modes[MODE_AMOUNT];

void stripTick();
void loadAnimation(CRGB color);

#endif