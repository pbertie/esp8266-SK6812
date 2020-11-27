//
// Created by paul on 19/11/2020.
//

#ifndef LEDSTRIP_SPOTLEDS_H
#define LEDSTRIP_SPOTLEDS_H

#include <cstdint>
#include <Adafruit_NeoPixel.h>

void drawSpot_7(Adafruit_NeoPixel &strip, uint16_t pos, uint16_t hue, uint8_t sat, uint8_t val, bool looped);
void drawSpot_11(Adafruit_NeoPixel &strip, uint16_t pos, uint16_t hue, uint8_t sat, uint8_t val, bool looped);

#endif //LEDSTRIP_SPOTLEDS_H
