#include <Arduino.h>
#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <WiFiManager.h>
#include <EEManager.h>
#include <FastLED.h>
#include <EncButton.h>
#include <mString.h>
#include "timer/timer.h"
#include "data/data.h"
#include "mqtt/mqtt.h"
#include "strip/strip.h"
#include "effects/effects.h"
#include "button/button.h"
#include "startup.h"

WiFiManager wifiManager;
DeviceData data;
EncButton<EB_TICK, BTN_PIN> btn;
CRGB leds[LED_AMOUNT];
WiFiClient espClient;
PubSubClient mqtt(espClient);
EEManager memory(data);
ModeType modes[MODE_AMOUNT];
boolean loadingFlag = true;

void setup()
{
  startup();
}

void loop()
{
  memory.tick();
  mqttTick();
  if (data.effectIndex > 0)
  {
    effectsTick();
  }
  else
  {
    stripTick();
  }

#ifdef USE_BUTTON
  buttonTick();
#endif

  yield();
}
