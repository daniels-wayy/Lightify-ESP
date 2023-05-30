#ifndef BUTTON_H
#define BUTTON_H

#include <EncButton.h>
#include <EEManager.h>
#include <FastLED.h>
#include "data/data.h"
#include "mqtt/mqtt.h"
#include "strip/strip.h"

extern EEManager memory;
extern DeviceData data;
extern EncButton<EB_TICK, BTN_PIN> btn;

void buttonTick();

#endif