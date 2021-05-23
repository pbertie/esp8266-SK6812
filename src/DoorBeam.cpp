//
// Created by paul on 23/03/2021.
//

#include "DoorBeam.h"
#include "config.h"
#include "Strip.h"
#include <Adafruit_NeoPixel.h>
#include <cmath>

namespace DoorBeam {

    uint16_t spacing = 20;
    uint16_t size = 150;

    void draw() {
        double endSpacing = (LED_COUNT - size);

        uint16_t pos = spacing + floor(endSpacing / 2);
        Strip::clear();
        uint8_t i = 0;
        for (int16_t drawPos = (int16_t) pos; drawPos <= (int16_t)pos + size; drawPos++) {
            switch (i) {
                case 0:
                case 3:
                    Strip::setPixelColor(drawPos, Adafruit_NeoPixel::Color(0, 0, 255));
                    break;
                case 1:
                case 2:
                    Strip::setPixelColor(drawPos, ((uint32_t) Adafruit_NeoPixel::gamma8(255) << 24));
                    break;
            }

            i++;
            if (i > 5) {
                i = 0;
            }
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

    uint16_t getSpacing() {
        return spacing;
    }


    void sizeUp() {
        if (size < 300) {
            size+=2;
            draw();
        }
    }

    void sizeDown() {
        if (size > 9) {
            size-=2;
            draw();
        }
    }

    uint16_t getSize() {
        return size;
    }
}