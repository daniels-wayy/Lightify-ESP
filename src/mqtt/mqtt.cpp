#include "mqtt.h"

static mString<MAX_MQTT_BUFFER_SIZE> inputBuffer;
static mString<MAX_MQTT_BUFFER_SIZE> outputBuffer;

void callback(char *topic, byte *payload, uint16_t len)
{
    payload[len] = '\0';
    char *str = (char *)payload;

    // not our packet
    if (strncmp(str, MQTT_HEADER, hLen))
        return;

    str += hLen; // header shift

    inputBuffer.clear();
    inputBuffer.add(str);

    parsePacket();
}

void parsePacket()
{
    if (inputBuffer.startsWith("GET"))
    {
        sendCurrentState();
    }
    else if (inputBuffer.startsWith("PWR"))
    {
        uint8_t powerState = inputBuffer.toUint(3);
        data.power = powerState;
    }
    else if (inputBuffer.startsWith("BRI"))
    {
        uint8_t brightness = inputBuffer.toUint(3);
        uint8_t constrainedBrightness = constrain(brightness, 0, 255);
        data.brightness = constrainedBrightness;
        if (data.breathFactor)
            data.breathFactor = 0.0;
        data.breathDir = -1;
        data.breathVal = constrainedBrightness;
    }
    else if (inputBuffer.startsWith("CLR"))
    {
        // CLRhue,sat,val
        int colorData[10];
        inputBuffer.remove(0, 3);
        inputBuffer.parseInts(colorData, 10);

        uint8_t colorHue = constrain(colorData[0], 0, 255);
        uint8_t colorSat = constrain(colorData[1], 0, 255);
        uint8_t colorVal = constrain(colorData[2], 0, 255);

        data.colorHue = colorHue;
        data.colorSaturation = colorSat;
        data.colorValue = colorVal;
    }
    else if (inputBuffer.startsWith("BRE"))
    {
        float breathFactor = inputBuffer.toFloat(3);
        data.breathFactor = breathFactor;
        data.breathDir = -1;
        data.breathVal = data.brightness;
    }
}

void sendCurrentState()
{
    outputBuffer.clear();
    outputBuffer = MQTT_HEADER;
    outputBuffer += mqttLocal;
    outputBuffer += ",";
    outputBuffer += DEVICE_NAME;
    outputBuffer += ",";
    outputBuffer += DEVICE_GROUP;
    outputBuffer += ",";
    outputBuffer += data.power;
    outputBuffer += ",";
    outputBuffer += data.brightness;
    outputBuffer += ",";
    outputBuffer += data.colorHue;
    outputBuffer += ",";
    outputBuffer += data.colorSaturation;
    outputBuffer += ",";
    outputBuffer += data.colorValue;
    outputBuffer += ",";
    outputBuffer += data.breathFactor;
    mqtt.publish(mqttRemote, outputBuffer.buf);
}

void mqttTick()
{
    if (WiFi.status() != WL_CONNECTED)
        return;

    if (!mqtt.connected())
        connectMQTT();

    mqtt.loop();
}

void connectMQTT()
{
    // random id
    String id("WebLightifier-");
    id += String(random(0xffffff), HEX);
    if (mqtt.connect(id.c_str()))
    {
        mqtt.subscribe(mqttLocal);
    }
    delay(1000);
}