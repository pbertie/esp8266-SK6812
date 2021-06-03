//
// Created by paul on 28/12/2020.
//

#include "StaticWhiteSpots.h"
#include "config.h"
#include "SpotLeds.h"
#include "Strip.h"
#include <cmath>

namespace StaticWhiteSpots {

    uint16_t spacing = START_WHITE_SPACE;
    uint8_t style = STYLE_WHITE;

    void draw() {
        double endSpacing = (LED_COUNT - 9) % (spacing);

        uint16_t pos = 4 + floor(endSpacing / 2);
        Strip::clear();
        while (pos < LED_COUNT - 3) {

            if ((style & STYLE_RGB) == STYLE_RGB) {
                drawSpot_9(pos, 0, 1, 255, true);
            }
            if ((style & STYLE_WHITE) == STYLE_WHITE) {
                drawSpot_9(pos, 0, 0, 255, true);
            }
            pos += spacing;
        }
        // Resend the signal every minute for 2 hours. This shouldn't be needed but I
        // see interference for the first few minutes after powering on the strip.
        // A shorter signal wire to the first LED would also solve this.
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

    uint16_t getSpacing() {
        return spacing;
    }

    void setStyle(uint8_t newStyle) {
        style = newStyle;
        draw();
    }

    uint8_t getStyle() {
        return style;
    }
}