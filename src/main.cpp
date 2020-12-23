#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <cstdint>

#ifdef __AVR__
#include <avr/power.h>
#endif

#include "config.h"
#include "Zinc.h"
#include "Animations.h"
#include "statusLeds.h"

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LED_STRIP_PIN, NEO_GRBW + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void startBtn();

void pauseBtn();

void stopBtn();

void addBtn();

void removeBtn();

void initStrip();

void stripOff();

void stripOn();

void showBtn();

void initGPIO();

void setup() {
    Zinc::beginLogger(9600);
    initStrip();
    initGPIO();
    Zinc::addNetwork({SSID_1, WIFI_PASS_1});
    Zinc::addNetwork({SSID_2, WIFI_PASS_2});
    Zinc::beginNetwork({SSID_AP, WIFI_PASS_AP});
    Zinc::log("Starting Loop");
}

void initGPIO() {
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(LED_R, OUTPUT);
    pinMode(LED_G, OUTPUT);
    pinMode(LED_B, OUTPUT);

    digitalWrite(LED_R, LOW); // OFF
    digitalWrite(LED_G, LOW); // OFF
    digitalWrite(LED_B, LOW); // OFF
    digitalWrite(LED_BUILTIN, HIGH); // OFF

    pinMode(BTN_1, INPUT_PULLUP);
    pinMode(BTN_2, INPUT_PULLUP);
    pinMode(BTN_3, INPUT_PULLUP);
    pinMode(STRIP_POWER, INPUT_PULLDOWN_16);

    Zinc::addButtonEvent(BTN_1, showBtn, TRIGGER_LOW);
    Zinc::addButtonEvent(BTN_2, addBtn, TRIGGER_LOW);
    Zinc::addButtonEvent(BTN_3, removeBtn, TRIGGER_LOW);

    Zinc::addButtonEvent(STRIP_POWER, stripOff, TRIGGER_LOW);
    Zinc::addButtonEvent(STRIP_POWER, stripOn, TRIGGER_HIGH);

    Zinc::addButtonEvent(BTN_1, startBtn, THROTTLE_LOW, 500);
    Zinc::addButtonEvent(BTN_2, pauseBtn, THROTTLE_LOW, 500);
    Zinc::addButtonEvent(BTN_3, stopBtn, THROTTLE_LOW, 500);
}

void initStrip() {
    strip.begin();
    strip.setBrightness(255);
//    These power readings include controller + 5m strip
//                                                      Power 1 End    Power Both Ends
//    strip.fill(Adafruit_NeoPixel::Color(0,0,0,0));        // 0.3A   0.3A
    strip.fill(Adafruit_NeoPixel::Color(0, 0, 0, 60));       // 1.5A   1.5A
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

uint16_t animId = 0;
uint8_t colorCount = 10;
uint8_t whiteCount = 5;

void stripOff() {
    // Flash builtin LED slow to show it detected the LED Strip power going off...
    flashBuiltIn(1000, 10);
}

void stripOn() {
    // Flash builtin LED fast to show it detected the LED Strip power coming back on...
    flashBuiltIn(1000, 30);
    // The strip has only just got power back so we need to tell it what to display again
    // Here we are delaying that and repeating as if we do it too quick it doesn't draw properly...
    Zinc::addAnimateEvent([](uint16_t id, uint16_t frame) -> void { strip.show(); }, 50, 10);
}

void showBtn() {
    flashG(1000, 10);
    strip.show();
}

void startBtn() {
    flashG(1000, 10);
    if (animId == 0) {
        strip.fill(Adafruit_NeoPixel::Color(0, 0, 0, 0));
        animId = Animations::runningSpots(strip, colorCount, whiteCount, true, 50);
    } else {
        Animations::resume(animId);
    }
}

void pauseBtn() {
    flashB(1000, 10);
    if (animId > 0) {
        Animations::pause(animId);
    }
}

void stopBtn() {
    flashR(1000, 10);
    if (animId > 0) {
        Animations::remove(animId);
        animId = 0;
    }
}

void addBtn() {
    if (whiteCount == 255) {
        return;
    }
    flashB(1000, 10);
    if (animId != 0) {
        Animations::remove(animId);
    }
    strip.fill(Adafruit_NeoPixel::Color(0, 0, 0, 0));
    animId = Animations::runningSpots(strip, ++colorCount, whiteCount, true, 50);
}

void removeBtn() {
    if (whiteCount == 0) {
        return;
    }
    flashR(1000, 10);
    if (animId != 0) {
        Animations::remove(animId);
    }
    strip.fill(Adafruit_NeoPixel::Color(0, 0, 0, 0));
    animId = Animations::runningSpots(strip, --colorCount, whiteCount, true, 50);
}

void loop() {
    Zinc::process();
}

