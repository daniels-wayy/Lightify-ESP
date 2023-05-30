#ifndef SETUP_H
#define SETUP_H

#include <Arduino.h>
#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <WiFiManager.h>
#include <EEManager.h>
#include <FastLED.h>
#include <EncButton.h>
#include "data/data.h"
#include "mqtt/mqtt.h"
#include "strip/strip.h"

extern DeviceData data;
extern EEManager memory;
extern CRGB leds[LED_AMOUNT];
extern EncButton<EB_TICK, BTN_PIN> btn;
extern WiFiManager wifiManager;
extern PubSubClient mqtt;

void startup();
void configModeCallback(WiFiManager *myWiFiManager);

#endif