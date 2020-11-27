//
// Created by paul on 19/11/2020.
//

#include "SpotLeds.h"

static const uint8_t SPOT_BRIGHT_7[7] = {0, 40, 128, 255, 128, 40, 0};

void drawSpot_7(Adafruit_NeoPixel &strip, uint16_t pos, uint16_t hue, uint8_t sat, uint8_t val, bool looped) {
    uint16_t ledCount = strip.numPixels();

    for (int16_t i = (int16_t)pos - 3; i <= (int16_t)pos + 3; i++) {
        uint16_t drawPos = i;
        if (i < 0 && looped) {
            drawPos = i + ledCount;
        } else if (i >= ledCount && looped) {
            drawPos = i - ledCount;
        }
        if (drawPos >= 0 && drawPos < ledCount) {
            if (sat == 0) {
                strip.setPixelColor(drawPos, ((uint32_t) Adafruit_NeoPixel::gamma8(
                        SPOT_BRIGHT_7[i - pos + 3] * (float(val) / 255)) << 24) | ((strip.getPixelColor(drawPos) << 8) >> 8));
            } else {
                strip.setPixelColor(drawPos, Adafruit_NeoPixel::ColorHSV(hue, sat, Adafruit_NeoPixel::gamma8(
                        SPOT_BRIGHT_7[i - pos + 3] * (float(val) / 255))));
            }
        }
    }
}

static const uint8_t SPOT_BRIGHT_11[11] = {0, 40, 100, 128, 200, 255, 200, 128, 100, 40, 0};
void drawSpot_11(Adafruit_NeoPixel &strip, uint16_t pos, uint16_t hue, uint8_t sat, uint8_t val, bool looped) {
    uint16_t ledCount = strip.numPixels();

    for (int16_t i = (int16_t)pos - 5; i <= (int16_t)pos + 5; i++) {
        uint16_t drawPos = i;
        if (i < 0 && looped) {
            drawPos = i + ledCount;
        } else if (i >= ledCount && looped) {
            drawPos = i - ledCount;
        }
        if (drawPos >= 0 && drawPos < ledCount) {
            if (sat == 0) {
                strip.setPixelColor(drawPos, ((uint32_t) Adafruit_NeoPixel::gamma8(
                        SPOT_BRIGHT_11[i - pos + 5] * (float(val) / 255)) << 24) | ((strip.getPixelColor(drawPos) << 8) >> 8));
            } else {
                strip.setPixelColor(drawPos, Adafruit_NeoPixel::ColorHSV(hue, sat, Adafruit_NeoPixel::gamma8(
                        SPOT_BRIGHT_11[i - pos + 5] * (float(val) / 255))));
            }
        }
    }
}