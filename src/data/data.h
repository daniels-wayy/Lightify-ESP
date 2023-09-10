#ifndef __DATA_H
#define __DATA_H

#include <Arduino.h>

// ***** DEVICES SETUP *****


// mqttLocal, AP_NAME, DEVICE_NAME, DEVICE_GROUP, LED_AMOUNT


// ------ Bedroom Closet ------- DSLY_Bedroom_Closet, Lightify Bedroom Closet, Closet, Bedroom, 92


// ------ Bedroom Bed ------- DSLY_Bedroom_Bed, Lightify Bedroom Bed, Bed, Bedroom, 368 -- (!!!! Noise effects led HEIGHT (LED_AMOUNT / 4) + 5)
    

// ------ Living room TV ------- DSLY_Livingroom_TV, Lightify Livingroom TV, TV, Living Room, 78


// ------ Kitchen Workspace ------- DSLY_Kitchen_Workspace, Lightify Kitchen Workspace, Workspace, Kitchen, 156


// ------ Living Room Piano ------- DSLY_Livingroom_Piano, Lightify Livingroom Piano, Piano, Living Room, 77


// ------ Bedroom Monitor ------- DSLY_Bedroom_Monitor, Lightify Bedroom Monitor, Monitor, Bedroom, 95


// ****** NICK'S DEVICES ******


// ------ Kitchen Ceiling ------- DNLY_Kitchen_Ceiling, Lightify Kitchen Ceiling, Ceiling, Kitchen, 141

#define LED_PIN D7
#define BTN_PIN D5
#define LED_AMOUNT 141
#define BTN_LEVEL 1
#define EB_STEP 40
#define MODE_AMOUNT 5

#define DEVICE_NAME ("Ceiling")
#define DEVICE_GROUP ("Kitchen")

#define AP_NAME ("Lightify Kitchen Ceiling") // WiFi Hotspot name
#define AP_PASS ("550132550132")              // WiFi Hotspot pass
// const uint8_t AP_STATIC_IP[] = {192, 168, 4, 4}; // WiFi Hotspot static IP

#define MQTT_HEADER "DSLY:"                           // Packets header
#define MAX_MQTT_BUFFER_SIZE (255U)                   // MQTT max buffer size
const uint8_t hLen = strlen(MQTT_HEADER);             // length of header
const char mqttLocal[30] = "DNLY_Kitchen_Ceiling";   // local topic
const char mqttRemote[30] = "DSLY_App";               // remote topic
const char mqttHost[30] = "broker.mqttdashboard.com"; // broker
const uint16_t mqttPort = 1883;

#define ESP_CONN_TIMEOUT (60U)         // ESP connection to WiFi timeout (in seconds)
#define ESP_CONF_TIMEOUT (300U)        // ESP hotspot timeout. After timeout ESP will restart (in seconds)
#define ESP_RESET_ON_CONNECTION (true) // Reset ESP as soon as connected to WiFi
#define CURRENT_LIMIT 3000             // mAh
#define COLOR_ORDER GRB

struct DeviceData
{
    bool power = 0;
    uint8_t brightness = 50;
    uint8_t colorHue = 0;          // 0...255
    uint8_t colorSaturation = 255; // 0...255
    uint8_t colorValue = 255;      // 0...255
    float breathFactor = 0;        // 0...1.0
    int8_t breathDir = -1;
    uint8_t breathVal = brightness;
    uint8_t effectIndex = 0;
};

struct ModeType
{
    uint8_t Speed = 4;
    uint8_t Scale = 8U;
};

// #define USE_BUTTON

// #define USE_SERIAL
#ifdef USE_SERIAL
#define DEBUG(x) Serial.print(x)
#define DEBUGLN(x) Serial.println(x)
#define DEBUGFP(x, y) Serial.printf_P(x, y)
#else
#define DEBUG(x)
#define DEBUGLN(x)
#define DEBUGFP(x, y)
#endif

#endif
