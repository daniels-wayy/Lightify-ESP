#include "effects.h"

void effectsTick()
{
    static uint32_t tmr;
    if (millis() - tmr >= 50)
    {
        tmr = millis();
        switch (data.effectIndex)
        {
        case 1:
            lavaNoise();
            break;
        case 2:
            cloudsNoiseRoutine();
            break;
        case 3:
            forestNoiseRoutine();
            break;
        case 4:
            oceanNoiseRoutine();
            break;
        default:
            break;
        }

        FastLED.setBrightness(!data.power ? 0 : data.brightness);
        FastLED.show();
    }
}

#define WIDTH 2
#define HEIGHT LED_AMOUNT
#define MATRIX_TYPE 0
#define SEGMENTS 1

// static uint8_t ihue = 0;
// static uint8_t colorLoop = 1;
static CRGBPalette16 currentPalette(PartyColors_p);
static uint8_t speed = 4; // speed is set dynamically once we've started up
static uint8_t scale = 8; // scale is set dynamically once we've started up
static uint16_t x;
static uint16_t y;
static uint16_t z;

#define MAX_DIMENSION (max(WIDTH, HEIGHT))
#if (WIDTH > HEIGHT)
uint8_t noise[WIDTH][WIDTH];
#else
uint8_t noise[HEIGHT][HEIGHT];
#endif

void lavaNoise()
{
    if (loadingFlag)
    {
        loadingFlag = false;
        currentPalette = LavaColors_p;
        scale = modes[1].Scale;
        speed = modes[1].Speed;
        // colorLoop = 0;
    }
    fillNoiseLED();
}

void cloudsNoiseRoutine()
{
    if (loadingFlag)
    {
        loadingFlag = false;
        currentPalette = CloudColors_p;
        scale = modes[2].Scale;
        speed = modes[2].Speed;
        // colorLoop = 0;
    }
    fillNoiseLED();
}

void forestNoiseRoutine()
{
    if (loadingFlag)
    {
        loadingFlag = false;
        currentPalette = ForestColors_p;
        scale = modes[3].Scale;
        speed = modes[3].Speed;
        // colorLoop = 0;
    }
    fillNoiseLED();
}

void oceanNoiseRoutine()
{
    if (loadingFlag)
    {
        loadingFlag = false;
        currentPalette = OceanColors_p;
        scale = modes[4].Scale;
        speed = modes[4].Speed;
        // colorLoop = 0;
    }
    fillNoiseLED();
}

//
//
//
//
//
//
//
//
//
//
//
//
//
// HELPERS
//
//
//

#if (CONNECTION_ANGLE == 0 && STRIP_DIRECTION == 0)
#define _WIDTH WIDTH
#define THIS_X x
#define THIS_Y y

#elif (CONNECTION_ANGLE == 0 && STRIP_DIRECTION == 1)
#define _WIDTH HEIGHT
#define THIS_X y
#define THIS_Y x

#elif (CONNECTION_ANGLE == 1 && STRIP_DIRECTION == 0)
#define _WIDTH WIDTH
#define THIS_X x
#define THIS_Y (HEIGHT - y - 1)

#elif (CONNECTION_ANGLE == 1 && STRIP_DIRECTION == 3)
#define _WIDTH HEIGHT
#define THIS_X (HEIGHT - y - 1)
#define THIS_Y x

#elif (CONNECTION_ANGLE == 2 && STRIP_DIRECTION == 2)
#define _WIDTH WIDTH
#define THIS_X (WIDTH - x - 1)
#define THIS_Y (HEIGHT - y - 1)

#elif (CONNECTION_ANGLE == 2 && STRIP_DIRECTION == 3)
#define _WIDTH HEIGHT
#define THIS_X (HEIGHT - y - 1)
#define THIS_Y (WIDTH - x - 1)

#elif (CONNECTION_ANGLE == 3 && STRIP_DIRECTION == 2)
#define _WIDTH WIDTH
#define THIS_X (WIDTH - x - 1)
#define THIS_Y y

#elif (CONNECTION_ANGLE == 3 && STRIP_DIRECTION == 1)
#define _WIDTH HEIGHT
#define THIS_X y
#define THIS_Y (WIDTH - x - 1)

#else
#define _WIDTH WIDTH
#define THIS_X x
#define THIS_Y y
#pragma message "Wrong matrix parameters! Set to default"

#endif

void fillAll(CRGB color)
{
    for (uint16_t i = 0; i < LED_AMOUNT; i++)
        leds[i] = color;
}

uint16_t XY(uint8_t x, uint8_t y)
{
    if (!(THIS_Y & 0x01) || MATRIX_TYPE) // Even rows run forwards
        return (THIS_Y * _WIDTH + THIS_X);
    else
        return (THIS_Y * _WIDTH + _WIDTH - THIS_X - 1); // Odd rows run backwards
}

uint16_t getPixelNumber(int8_t x, int8_t y)
{
    if ((THIS_Y % 2 == 0) || MATRIX_TYPE)
    {
        return (THIS_Y * _WIDTH + THIS_X);
    }
    else
    {
        return (THIS_Y * _WIDTH + _WIDTH - THIS_X - 1);
    }
}

void drawPixelXY(int8_t x, int8_t y, CRGB color)
{
    if (x < 0 || x > WIDTH - 1 || y < 0 || y > HEIGHT - 1)
        return;
    int thisPixel = getPixelNumber(x, y) * SEGMENTS;
    for (byte i = 0; i < SEGMENTS; i++)
    {
        leds[thisPixel + i] = color;
    }
}

void fillNoiseLED()
{
    uint8_t dataSmoothing = 0;
    if (speed < 50)
    {
        dataSmoothing = 200 - (speed * 4);
    }
    for (int i = 0; i < MAX_DIMENSION; i++)
    {
        int ioffset = scale * i;
        for (int j = 0; j < MAX_DIMENSION; j++)
        {
            int joffset = scale * j;

            uint8_t data = inoise8(x + ioffset, y + joffset, z);

            data = qsub8(data, 16);
            data = qadd8(data, scale8(data, 39));

            if (dataSmoothing)
            {
                uint8_t olddata = noise[i][j];
                uint8_t newdata = scale8(olddata, dataSmoothing) + scale8(data, 256 - dataSmoothing);
                data = newdata;
            }

            noise[i][j] = data;
        }
    }
    z += speed;

    // apply slow drift to X and Y, just for visual variation.
    x += speed / 8;
    y -= speed / 16;

    for (int i = 0; i < WIDTH; i++)
    {
        for (int j = 0; j < HEIGHT; j++)
        {
            uint8_t index = noise[j][i];
            uint8_t bri = noise[i][j];
            // if this palette is a 'loop', add a slowly-changing base value
            // if (colorLoop)
            // {
            //     index += ihue;
            // }
            // brighten up, as the color palette itself often contains the
            // light/dark dynamic range desired
            if (bri > 127)
            {
                bri = 255;
            }
            else
            {
                bri = dim8_raw(bri * 2);
            }
            CRGB color = ColorFromPalette(currentPalette, index, bri);
            drawPixelXY(i, j, color); // leds[getPixelNumber(i, j)] = color;
        }
    }
    // ihue += 1;
}

uint32_t getPixColor(int thisSegm)
{
    int thisPixel = thisSegm * SEGMENTS;
    if (thisPixel < 0 || thisPixel > LED_AMOUNT - 1)
        return 0;
    return (((uint32_t)leds[thisPixel].r << 16) | ((long)leds[thisPixel].g << 8) | (long)leds[thisPixel].b);
}

uint32_t getPixColorXY(int8_t x, int8_t y)
{
    return getPixColor(getPixelNumber(x, y));
}