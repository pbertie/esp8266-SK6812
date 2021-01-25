//
// Created by paul on 02/01/2021.
//

#ifndef ESPSTRIP_RUNNINGSPOTS_H
#define ESPSTRIP_RUNNINGSPOTS_H

#include <cstdint>

namespace RunningSpots {

    void start(uint8_t colorCount, uint8_t whiteCount, bool looped, uint32_t gap);

    void stop();

    void pause();

    void resume();

    void speedUp();
    void speedDown();

    void whiteCountUp();
    void whiteCountDown();

    void colourCountUp();
    void colourCountDown();

    uint8_t getColorCount();
    uint8_t getWhiteCount();
}

#endif //ESPSTRIP_RUNNINGSPOTS_H
