//
// Created by paul on 02/01/2021.
//

#include "Strip.h"
#include "config.h"
#include "Zinc.h"
#include "statusLeds.h"
#include <Adafruit_NeoPixel.h>

namespace Strip {

    Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LED_STRIP_PIN, NEO_GRBW + NEO_KHZ800);
    // IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
    // pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
    // and minimize distance between Arduino and first pixel.  Avoid connecting
    // on a live circuit...if you must, connect GND first.

    uint16_t tIdShow = 0;

    void init() {
        strip.begin();
        strip.setBrightness(255);
//    These power readings include controller + 5m strip
//                                                      Power 1 End    Power Both Ends
        strip.fill(Adafruit_NeoPixel::Color(0, 0, 0, 0));        // 0.3A   0.3A
//    strip.fill(Adafruit_NeoPixel::Color(0, 0, 0, 60));       // 1.5A   1.5A
//    strip.fill(Adafruit_NeoPixel::Color(60,60,60,0));     // 2.0A   2.0A
//    strip.fill(Adafruit_NeoPixel::Color(0,0,0,150));      // 2.7A   3.3A
//    strip.fill(Adafruit_NeoPixel::Color(60,60,60,60));    // 2.8A   3.2A
//    strip.fill(Adafruit_NeoPixel::Color(0,0,0,230));      // 3.3A   4.6A
//    strip.fill(Adafruit_NeoPixel::Color(0,0,0,255));      // 3.5A   5.0A
//    strip.fill(Adafruit_NeoPixel::Color(0,0,120,255));    // 3.7A  >5.0A
//    strip.fill(Adafruit_NeoPixel::Color(0,0,255,255));    // 4.1A  >5.0A
//    strip.fill(Adafruit_NeoPixel::Color(150,0,255,255));  // 4.4A  >5.0A
        strip.show(); // Initialize all pixels
    }

    void enableUpdate() {
        // Flash builtin LED fast to show it detected the LED Strip power coming back on...
        flashBuiltIn(1000, 30);
        // The strip has only just got power back so we need to tell it what to display again
        // Here we are delaying that and repeating as if we do it too quick it doesn't draw properly...
        show(50, 10);
    }

    void disableUpdate() {
        // Flash builtin LED slow to show it detected the LED Strip power going off...
        flashBuiltIn(1000, 10);
    }

    void stopShow() {
        if (tIdShow != 0) {
            Zinc::removeTimerEvent(tIdShow);
            tIdShow = 0;
        }
    }

    void show() {
        show(0,0);
    }

    void show(uint32_t frameLength, uint16_t frameCount, unsigned long initDelay) {
        stopShow();
        if (frameCount == 0) {
            strip.show();
        } else {
            tIdShow = Zinc::addTimerEvent([](uint16_t id, uint16_t frame) -> void { strip.show(); }, frameLength,
                                          frameCount,
                                          initDelay, nullptr,
                                          [](uint16_t id, uint16_t frame) -> void {
                                              strip.show();
                                              tIdShow = 0;
                                          });
        }
    }

    void clear() {
        strip.fill(Adafruit_NeoPixel::Color(0, 0, 0, 0));
    }

    uint16_t numPixels() {
        return strip.numPixels();
    }

    void setPixelColor(uint16_t n, uint32_t c) {
        strip.setPixelColor(n, c);
    }

    uint32_t getPixelColor(uint16_t n) {
        return strip.getPixelColor(n);
    }
}