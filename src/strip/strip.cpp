#include "strip.h"

void animation()
{
    static Timer tmr(20);

    if (tmr.period())
    {

        uint8_t colorVal = data.power ? data.colorValue : 0;

        // smooth strip changes
        CRGB ncol = CHSV(data.colorHue, data.colorSaturation, colorVal);
        CRGB ccol = leds[0];
        if (ccol != ncol)
            ccol = blend(ccol, ncol, 32);

        fill_solid(leds, LED_AMOUNT, ccol);

        if (data.power && data.breathFactor)
        {
            uint8_t lowerV = (uint8_t)(data.brightness - (data.brightness * data.breathFactor));
            data.breathVal += data.breathDir;
            if (data.breathVal >= data.brightness || data.breathVal <= lowerV)
                data.breathDir = -data.breathDir;
            FastLED.setBrightness(data.breathVal);
        }
        else
        {
            FastLED.setBrightness(data.brightness);
        }

        FastLED.show();
    }
}

void loadAnimation(CRGB color)
{
    static int8_t dir = 1;
    static uint8_t val = 0;
    static Timer tmr(20);
    if (tmr.period())
    {
        val += dir;
        if (val >= 100 || val <= 0)
            dir = -dir;
        fill_solid(leds, LED_AMOUNT, color);
        FastLED.setBrightness(val);
        FastLED.show();
    }
    yield();
}

void pulse()
{
    for (int i = data.brightness; i > data.brightness - 85; i -= 5)
    {
        FastLED.setBrightness(i);
        FastLED.show();
        delay(8);
    }
    for (int i = data.brightness - 85; i < data.brightness; i += 5)
    {
        FastLED.setBrightness(i);
        FastLED.show();
        delay(8);
    }
}