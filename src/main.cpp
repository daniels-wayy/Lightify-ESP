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
#include "button/button.h"
#include "startup.h"

WiFiManager wifiManager;
DeviceData data;
EncButton<EB_TICK, BTN_PIN> btn;
CRGB leds[LED_AMOUNT];
WiFiClient espClient;
PubSubClient mqtt(espClient);
EEManager memory(data);

void setup()
{
  startup();
}

void loop()
{
  memory.tick();
  animation();
  buttonTick();
  mqttTick();
}
