//
// Created by paul on 02/01/2021.
//

#ifndef ESPSTRIP_STRIP_H
#define ESPSTRIP_STRIP_H

#include <cstdint>
#include <Adafruit_NeoPixel.h>

namespace Strip {

    void init();

    void enableUpdate();

    void disableUpdate();

    void show(uint32_t frameLength, uint16_t frameCount, unsigned long initDelay = 0);

    void show();

    void stopShow();

    void clear();

    uint16_t numPixels();

    Adafruit_NeoPixel* getStrip();
}

#endif //ESPSTRIP_STRIP_H
