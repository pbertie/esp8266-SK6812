//
// Created by paul on 21/11/2020.
//

#include "Zinc.h"

namespace Zinc {

    void process() {
        ZButtons::process();
        ZAnimate::process();
    }

    uint16_t addButtonEvent(uint8_t pin, void (*cb)(), uint8_t trigger, uint16_t throttle, uint16_t debounce) {
        return ZButtons::add(pin, cb, trigger, throttle, debounce);
    }

    void removeButtonEvent(uint16_t id) {
        ZButtons::remove(id);
    }

    void pauseButtonEvent(uint16_t id) {
        ZButtons::setActive(id, false);
    }

    void resumeButtonEvent(uint16_t id) {
        ZButtons::setActive(id, true);
    }

    /**
     *
     * @param cb
     * @param frameLength
     * @param frameCount
     * @param initDelay
     * @param cb_start
     * @param cb_end
     * @return
     */
    uint16_t
    addAnimateEvent(ZAnimate::frameCallback cb, uint32_t frameLength, uint16_t frameCount, unsigned long initDelay,
                    ZAnimate::frameCallback cb_start, ZAnimate::frameCallback cb_end) {
        return ZAnimate::add(cb, frameLength, frameCount, initDelay, cb_start, cb_end);
    }

    void removeAnimateEvent(uint16_t id) {
        ZAnimate::remove(id);
    }

    void pauseAnimateEvent(uint16_t id) {
        ZAnimate::setActive(id, false);
    }

    void resumeAnimateEvent(uint16_t id) {
        ZAnimate::setActive(id, true);
    }

    void beginNetwork(ZNetwork::NetworkCredentials ap) {
        ZNetwork::beginNetwork(ap);
    }

    void addNetwork(ZNetwork::NetworkCredentials network) {
        ZNetwork::addNetwork(network);
    }

    void beginLogger(unsigned long baud) {
        ZLogging::beginLogger(baud);
    }

    void log(const char *str) {
        ZLogging::log(str);
    }

    void log(const String& str) {
        ZLogging::log(str);
    }
}