//
// Created by paul on 28/12/2020.
//

#include "StaticWhiteSpots.h"
#include "config.h"
#include "SpotLeds.h"
#include "Strip.h"

namespace StaticWhiteSpots {

    uint16_t spacing = 44;

    void draw() {
        double endSpacing = (LED_COUNT - 9) % (spacing);

        uint16_t pos = 4 + floor(endSpacing / 2);
        Strip::clear();
        while (pos < LED_COUNT - 3) {
            drawSpot_9(Strip::getStrip(), pos, 0, 1, 255, true);
            drawSpot_9(Strip::getStrip(), pos, 0, 0, 255, true);
            pos += spacing;
        }
        // Resend the signal every minute for 2 hours. This shouldn't be needed but I
        // see interference for the first few minutes after powering on the strip.
        Strip::show(60000, 120);
    }

    void spacingUp() {
        if (spacing < 300) {
            spacing++;
            draw();
        }
    }

    void spacingDown() {
        if (spacing > 9) {
            spacing--;
            draw();
        }
    }
}