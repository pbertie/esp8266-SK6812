#include <Arduino.h>
#include <cstdint>

#ifdef __AVR__
#include <avr/power.h>
#endif

#include "config.h"
#include "Zinc.h"
#include "StaticWhiteSpots.h"
#include "Menu.h"
#include "Strip.h"

void initGPIO();

uint16_t tIdWarmUp = 0;

void setup() {
    Zinc::beginLogger(9600);
    Strip::init();
    initGPIO();
    tIdWarmUp = Zinc::addTimerEvent([](uint16_t id, uint16_t frame) -> void {
        StaticWhiteSpots::draw();
    }, 0, 1, 180000);
    Zinc::addNetwork({SSID_1, WIFI_PASS_1});
    Zinc::addNetwork({SSID_2, WIFI_PASS_2});
    Zinc::beginNetwork({SSID_AP, WIFI_PASS_AP});
    Zinc::log("Starting Loop");
}

void loop() {
    Zinc::process();
}

void initGPIO() {
    // Define Ouputs...
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(LED_R, OUTPUT);
    pinMode(LED_G, OUTPUT);
    pinMode(LED_B, OUTPUT);

    digitalWrite(LED_R, LOW); // OFF
    digitalWrite(LED_G, LOW); // OFF
    digitalWrite(LED_B, LOW); // OFF
    digitalWrite(LED_BUILTIN, HIGH); // OFF

    // Define Inputs...
    pinMode(BTN_1, INPUT_PULLUP);
    pinMode(BTN_2, INPUT_PULLUP);
    pinMode(BTN_3, INPUT_PULLUP);
    pinMode(STRIP_POWER, INPUT_PULLDOWN_16);

    Zinc::addButtonEvent(STRIP_POWER, Strip::disableUpdate, TRIGGER_LOW);
    Zinc::addButtonEvent(STRIP_POWER, Strip::enableUpdate, TRIGGER_HIGH);

    Menu::init();
}

void cancelWarmUp() {
    if (tIdWarmUp != 0) {
        Zinc::removeTimerEvent(tIdWarmUp);
        tIdWarmUp = 0;
    }
}
