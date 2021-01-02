//
// Created by paul on 07/12/2020.
//

#include "statusLeds.h"
#include "Zinc.h"
#include "config.h"

uint16_t tIdRGB = 0;
uint16_t tIdBuiltIn = 0;

uint16_t flashBuiltIn(uint32_t duration, uint16_t count, unsigned long initDelay) {
    // Remove any existing animation...
    if (tIdBuiltIn != 0) {
        Zinc::removeTimerEvent(tIdBuiltIn);
    }
    // Turn off leds...
    digitalWrite(LED_BUILTIN, HIGH);

    // Count is zero so no need to animate...
    if (count == 0) {
        return 0;
    }
    uint16_t frameCount = count * 2;
    uint32_t frameLength = duration / frameCount;
    tIdBuiltIn = Zinc::addTimerEvent(
            [](uint16_t id, uint16_t frame) -> void { digitalWrite(LED_BUILTIN, frame % 2 == 0 ? HIGH : LOW); },
            frameLength, frameCount, initDelay, nullptr, [](uint16_t id, uint16_t frame) -> void {
                digitalWrite(LED_BUILTIN, frame % 2 == 0 ? HIGH : LOW);
                tIdBuiltIn = 0;
            });
    return tIdBuiltIn;
}

uint16_t flashR(uint32_t duration, uint16_t count, unsigned long initDelay) {
    return flashRGB(255, 0, 0, duration, count, initDelay);
}

uint16_t flashG(uint32_t duration, uint16_t count, unsigned long initDelay) {
    return flashRGB(0, 255, 0, duration, count, initDelay);
}

uint16_t flashB(uint32_t duration, uint16_t count, unsigned long initDelay) {
    return flashRGB(0, 0, 255, duration, count, initDelay);
}

uint16_t r_value = 0;
uint16_t g_value = 0;
uint16_t b_value = 0;

void setPWM(uint8_t pin, uint8_t value) {
    if (value == 0) {
        digitalWrite(pin, LOW);
    } else if (value == 255) {
        digitalWrite(pin, HIGH);
    } else {
        analogWrite(pin, (value * PWMRANGE) / 255);
    }
}

void flashRGBFrame(uint16_t id, uint16_t frame) {
    if (frame % 2 == 0) {
        digitalWrite(LED_R, LOW);
        digitalWrite(LED_G, LOW);
        digitalWrite(LED_B, LOW);
    } else {
        setPWM(LED_R, r_value);
        setPWM(LED_G, g_value);
        setPWM(LED_B, b_value);
    }
}

uint16_t flashRGB(uint8_t r, uint8_t g, uint8_t b, uint32_t duration, uint16_t count, unsigned long initDelay) {
    // Remove any existing animation...
    if (tIdRGB != 0) {
        Zinc::removeTimerEvent(tIdRGB);
    }
    // Turn off leds...
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, LOW);

    // Store the colour...
    r_value = r;
    g_value = g;
    b_value = b;

    // Count is zero or colour is off so no need to animate...
    if (count == 0 || (r == 0 && g == 0 && b == 0)) {
        return 0;
    }

    uint16_t frameCount = count * 2;
    uint32_t frameLength = duration / (frameCount - 1);

    tIdRGB = Zinc::addTimerEvent(flashRGBFrame, frameLength, frameCount, initDelay, nullptr,
                                 [](uint16_t id, uint16_t frame) -> void {
                                     flashRGBFrame(id, frame);
                                     tIdRGB = 0;
                                 });
    return tIdRGB;
}