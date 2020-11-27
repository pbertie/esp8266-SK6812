//
// Created by paul on 21/11/2020.
//

#ifndef LEDSTRIP_ZINC_H
#define LEDSTRIP_ZINC_H

#include "ZButtons.h"
#include "ZAnimate.h"
#include "ZNetwork.h"
#include "ZLogging.h"

namespace Zinc {

    void process();

    uint16_t
    addButtonEvent(uint8_t pin, void (*cb)(), uint8_t trigger, uint16_t throttle = 200, uint16_t debounce = 20);

    void removeButtonEvent(uint16_t id);

    void pauseButtonEvent(uint16_t id);

    void resumeButtonEvent(uint16_t id);

    uint16_t addAnimateEvent(ZAnimate::frameCallback cb, uint32_t frameLength, uint16_t frameCount = 1,
                             unsigned long initDelay = 0, ZAnimate::frameCallback cb_start = nullptr,
                             ZAnimate::frameCallback cb_end = nullptr);

    void removeAnimateEvent(uint16_t id);

    void pauseAnimateEvent(uint16_t id);

    void resumeAnimateEvent(uint16_t id);

    void beginNetwork(ZNetwork::NetworkCredentials ap = {"ZINC-SETUP", nullptr});

    void addNetwork(ZNetwork::NetworkCredentials network);

    void beginLogger(unsigned long baud);

    void log(const char *str);

    void log(const String& str);
};

#endif //LEDSTRIP_ZINC_H
