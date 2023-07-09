#include "startup.h"

void startup()
{
    delay(500);
#ifdef USE_SERIAL
    Serial.begin(115200);
#endif

    EEPROM.begin(sizeof(data) + 1);
    memory.begin(0, 'a');

    FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, LED_AMOUNT).setCorrection(TypicalLEDStrip);
    if (CURRENT_LIMIT > 0)
        FastLED.setMaxPowerInVoltsAndMilliamps(5, CURRENT_LIMIT);
    FastLED.setBrightness(50);
    FastLED.show();

#ifdef USE_BUTTON
    btn.setButtonLevel(BTN_LEVEL);
    btn.setStepTimeout(EB_STEP);
#endif

    if (WiFi.SSID().length())
    {
        DEBUGFP(PSTR("Connecting to WiFi network: %s\n"), WiFi.SSID().c_str());
    }
    else
    {
        wifiManager.setBreakAfterConfig(ESP_RESET_ON_CONNECTION);
    }

    fill_solid(leds, LED_AMOUNT, CRGB::Blue);
    FastLED.show();

    wifiManager.setConnectTimeout(ESP_CONN_TIMEOUT);
    wifiManager.setConfigPortalTimeout(ESP_CONF_TIMEOUT);
    wifiManager.autoConnect(AP_NAME, AP_PASS);

    FastLED.clear();
    FastLED.show();

    mqtt.setServer(mqttHost, mqttPort);
    mqtt.setCallback(callback);

    randomSeed(micros());

    FastLED.setBrightness(data.brightness);

    data.effectIndex = 0;
}
