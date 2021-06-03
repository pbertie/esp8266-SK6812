//
// Created by paul on 28/12/2020.
//

#ifndef ESPSTRIP_STATICWHITESPOTS_H
#define ESPSTRIP_STATICWHITESPOTS_H

#include <cstdint>

#define STYLE_WHITE 0x1
#define STYLE_RGB 0x2

namespace StaticWhiteSpots {

    void draw();

    void spacingUp();

    void spacingDown();

    uint16_t getSpacing();

    uint8_t getStyle();

    void setStyle(uint8_t newStyle);
}

#endif //ESPSTRIP_STATICWHITESPOTS_H
