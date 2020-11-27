//
// Created by paul on 20/11/2020.
//

#ifndef LEDSTRIP_ANIMATIONS_H
#define LEDSTRIP_ANIMATIONS_H

#include <cstdint>
#include <LinkedList.h>
#include "SpotLeds.h"
#include "Zinc.h"

namespace Animations {
    uint16_t runningSpots(Adafruit_NeoPixel &strip, uint8_t colorCount, uint8_t whiteCount, bool looped, uint32_t gap);
    void remove(uint16_t id);
    void pause(uint16_t id);
    void resume(uint16_t id);
}
#endif //LEDSTRIP_ANIMATIONS_H
