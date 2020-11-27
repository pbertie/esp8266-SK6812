//
// Created by paul on 20/11/2020.
//

#include "ZButtons.h"

namespace ZButtons {

    class ButtonEventDef {
    public:
        ButtonEventDef(uint16_t id, uint8_t pin, uint8_t trigger, unsigned long now, uint16_t throttle, uint16_t debounce,
                       uint8_t lastState, void (*cb)());

        uint16_t id;
        uint8_t pin;
        uint8_t trigger;
        unsigned long lastChange;
        unsigned long lastThrottle;
        uint16_t throttle;
        uint16_t debounce;
        uint8_t lastState;
        bool active;

        void (*cb)();
    };

    ButtonEventDef::ButtonEventDef(uint16_t id, uint8_t pin, uint8_t trigger, unsigned long now, uint16_t throttle,
                                   uint16_t debounce, uint8_t lastState, void (*cb)()) : id(id), pin(pin),
                                                                                         trigger(trigger),
                                                                                         lastChange(now),
                                                                                         lastThrottle(now),
                                                                                         throttle(throttle),
                                                                                         debounce(debounce),
                                                                                         lastState(lastState),
                                                                                         active(true),
                                                                                         cb(cb) {}

    LinkedList<ButtonEventDef *> eventList;
    uint16_t nextId = 1;

    void process() {
        uint16_t listSize = eventList.size();
        for (uint16_t i = 0; i < listSize; i++) {
            ButtonEventDef *e = eventList.get(i);
            if (e->active) {
                uint8_t currentState = digitalRead(e->pin);
                unsigned long now = millis();

                if (now - e->lastChange > e->debounce) {
                    if (currentState != e->lastState) {
                        e->lastState = currentState;
                        e->lastChange = now;
                        e->lastThrottle = now;
                        if (currentState == LOW && (e->trigger & TRIGGER_LOW)) {
                            (*e->cb)();
                        }
                        if (currentState == HIGH && (e->trigger & TRIGGER_HIGH)) {
                            (*e->cb)();
                        }
                    } else {
                        if (currentState == LOW && (e->trigger & THROTTLE_LOW) && now - e->lastThrottle > e->throttle) {
                            e->lastThrottle = now;
                            (*e->cb)();
                        }
                        if (currentState == HIGH && (e->trigger & THROTTLE_HIGH) &&
                            now - e->lastThrottle > e->throttle) {
                            e->lastThrottle = now;
                            (*e->cb)();
                        }
                    }
                }
            }
        }
    }

    uint16_t add(uint8_t pin, void (*cb)(), uint8_t trigger, uint16_t throttle, uint16_t debounce) {
        unsigned long now = millis();
        auto *e = new ButtonEventDef(nextId, pin, trigger, now, throttle, debounce, (uint8_t) digitalRead(pin), cb);
        eventList.add(e);
        e->active = true;
        return nextId++;
    }

    void remove(uint16_t id) {
        uint16_t listSize = eventList.size();
        for (uint16_t i = listSize; i > 0; i--) {
            ButtonEventDef *e = eventList.get(i - 1);
            if (e->id == id) {
                delete e;
                eventList.remove(i - 1);
                break;
            }
        }
    }

    void setActive(uint16_t id, bool active) {
        uint16_t listSize = eventList.size();
        for (uint16_t i = 0; i < listSize; i++) {
            ButtonEventDef *e = eventList.get(i);
            if (e->id == id) {
                e->active = active;
                break;
            }
        }
    }
}