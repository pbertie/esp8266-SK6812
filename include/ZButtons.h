//
// Created by paul on 20/11/2020.
//

#ifndef LEDSTRIP_BUTTONS_H
#define LEDSTRIP_BUTTONS_H

#include <Arduino.h>
#include <LinkedList.h>
#include "ZLogging.h"

#define TRIGGER_LOW 1
#define TRIGGER_HIGH 2
#define THROTTLE_LOW 4
#define THROTTLE_HIGH 8

namespace ZButtons {

    void process ();

    uint16_t add (uint8_t pin, void (*cb)(), uint8_t trigger, uint16_t throttle = 200, uint16_t debounce = 20);
    void remove(uint16_t id);
    void setActive(uint16_t id, bool active);
}
#endif //LEDSTRIP_BUTTONS_H
