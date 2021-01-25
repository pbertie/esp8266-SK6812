//
// Created by paul on 02/01/2021.
//

#ifndef ESPSTRIP_STRIP_H
#define ESPSTRIP_STRIP_H

#include <cstdint>

namespace Strip {

    void init();

    void enableUpdate();

    void disableUpdate();

    void show(uint32_t frameLength, uint16_t frameCount, unsigned long initDelay = 0);

    void show();

    void stopShow();

    void clear();

    uint16_t numPixels();

    void setPixelColor(uint16_t n, uint32_t c);

    uint32_t getPixelColor(uint16_t n);
}

#endif //ESPSTRIP_STRIP_H
