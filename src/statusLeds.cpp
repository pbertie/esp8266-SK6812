//
// Created by paul on 07/12/2020.
//

#include "statusLeds.h"
#include "Zinc.h"
#include "config.h"

void flashBuiltIn(uint32_t duration, uint16_t count, unsigned long initDelay) {
    if (count == 0) {
        return;
    }
    uint16_t frameCount = count * 2;
    uint32_t frameLength = duration / frameCount;
    Zinc::addAnimateEvent(
            [](uint16_t id, uint16_t frame) -> void { digitalWrite(LED_BUILTIN, frame % 2 == 0 ? HIGH : LOW); },
            frameLength, frameCount, initDelay);
}

void flashR(uint32_t duration, uint16_t count, unsigned long initDelay) {
    if (count == 0) {
        return;
    }
    uint16_t frameCount = count * 2;
    uint32_t frameLength = duration / frameCount;
    Zinc::addAnimateEvent([](uint16_t id, uint16_t frame) -> void { digitalWrite(LED_R, frame % 2 == 0 ? LOW : HIGH); },
                          frameLength, frameCount, initDelay);
}

void flashG(uint32_t duration, uint16_t count, unsigned long initDelay) {
    if (count == 0) {
        return;
    }
    uint16_t frameCount = count * 2;
    uint32_t frameLength = duration / frameCount;
    Zinc::addAnimateEvent([](uint16_t id, uint16_t frame) -> void { digitalWrite(LED_G, frame % 2 == 0 ? LOW : HIGH); },
                          frameLength, frameCount, initDelay);
}

void flashB(uint32_t duration, uint16_t count, unsigned long initDelay) {
    if (count == 0) {
        return;
    }
    uint16_t frameCount = count * 2;
    uint32_t frameLength = duration / frameCount;
    Zinc::addAnimateEvent([](uint16_t id, uint16_t frame) -> void { digitalWrite(LED_B, frame % 2 == 0 ? LOW : HIGH); },
                          frameLength, frameCount, initDelay);
}