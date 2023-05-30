#include "button.h"

void buttonTick()
{
    btn.tick();

    // clicks
    switch (btn.hasClicks())
    {
    case 1: // turn off/on
        data.power = !data.power;
        sendCurrentState();
        memory.update();
        break;
    case 2: // change color forward
        data.colorHue += 32;
        sendCurrentState();
        memory.update();
        break;
    case 3: // change color backward
        data.colorHue -= 32;
        sendCurrentState();
        memory.update();
        break;
    }

    static int8_t dir = 5;
    if (btn.step())
    {
        if (data.breathFactor)
            data.breathFactor = 0.0;

        data.brightness = constrain(data.brightness + dir, 8, 255);
    }
    if (btn.releaseStep())
    {
        dir = -dir;
        sendCurrentState();

        data.breathDir = -1;
        data.breathVal = data.brightness;

        memory.update();
    }
}