#ifndef MQTT_H
#define MQTT_H

#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <mString.h>
#include "data/data.h"

extern PubSubClient mqtt;
extern DeviceData data;
extern ModeType modes[MODE_AMOUNT];
extern boolean loadingFlag;

void mqttTick();
void connectMQTT();
void callback(char *topic, byte *payload, uint16_t len);
void parsePacket();
void sendCurrentState();

#endif