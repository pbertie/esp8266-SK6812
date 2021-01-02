//
// Created by paul on 28/12/2020.
//

#include "StaticWhiteSpots.h"
#include "config.h"
#include "SpotLeds.h"
#include "Strip.h"

namespace StaticWhiteSpots {

    void draw() {
        uint16_t pos = 9;
        while (pos < LED_COUNT - 4) {
            drawSpot_11(Strip::getStrip(), pos, 0, 1, 255, true);
            drawSpot_11(Strip::getStrip(), pos, 0, 0, 255, true);
            pos += 44;
        }
        // Resend the signal every minute for 2 hours. This shouldn't be needed but I
        // see interference for the first few minutes after powering on the strip.
        Strip::show(60000, 120);
    }

}