//
// Created by paul on 20/11/2020.
//

#ifndef LEDSTRIP_ANIMATE_H
#define LEDSTRIP_ANIMATE_H

#include <Arduino.h>
#include <LinkedList.h>
#include "ZLogging.h"

namespace ZAnimate {

    typedef void (*frameCallback)(uint16_t id, uint16_t frame);

    void process();

    uint16_t add(frameCallback cb, uint32_t frameLength, uint16_t frameCount = 1, unsigned long initDelay = 0,
                 frameCallback cb_start = nullptr, frameCallback cb_end = nullptr, bool skipMissedFrames = false);

    void remove(uint16_t id);

    void setActive(uint16_t id, bool active);
}
#endif //LEDSTRIP_ANIMATE_H
