//
// Created by paul on 21/11/2020.
//

#include "Zinc.h"

namespace Zinc {

    void process() {
        ZButtons::process();
        ZTimer::process();
        ZWebServer::handleClient();
        ZNetwork::process();
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
    addTimerEvent(ZTimer::frameCallback cb, uint32_t frameLength, uint16_t frameCount, unsigned long initDelay,
                  ZTimer::frameCallback cb_start, ZTimer::frameCallback cb_end) {
        return ZTimer::add(cb, frameLength, frameCount, initDelay, cb_start, cb_end);
    }

    void removeTimerEvent(uint16_t id) {
        ZTimer::remove(id);
    }

    void pauseTimerEvent(uint16_t id) {
        ZTimer::setActive(id, false);
    }

    void resumeTimerEvent(uint16_t id) {
        ZTimer::setActive(id, true);
    }

    void beginNetwork(ZNetwork::NetworkCredentials ap, const char* hostname) {
        ZNetwork::beginNetwork(ap, hostname);
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