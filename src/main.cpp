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
#include "staticWhiteSpots.h"

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LED_STRIP_PIN, NEO_GRBW + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void initStrip();

void stripOff();

void stripOn();

void resetAnimation();

void initGPIO();

uint16_t animationId = 0;
uint16_t tIdWarmUp = 0;
uint16_t tIdShow = 0;
uint8_t colorCount = START_COLOR_COUNT;
uint8_t whiteCount = START_WHITE_COUNT;
uint32_t gap = START_SPEED;

void selectBtn();

void UpBtn();

void DownBtn();

#define MENU_DURATION 10000
uint8_t mode = 0;
uint8_t menu = 0;

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

    Zinc::addButtonEvent(STRIP_POWER, stripOff, TRIGGER_LOW);
    Zinc::addButtonEvent(STRIP_POWER, stripOn, TRIGGER_HIGH);

    Zinc::addButtonEvent(BTN_1, selectBtn, TRIGGER_LOW);
    Zinc::addButtonEvent(BTN_2, UpBtn, TRIGGER_LOW);
    Zinc::addButtonEvent(BTN_3, DownBtn, TRIGGER_LOW);

    Zinc::addButtonEvent(BTN_1, selectBtn, THROTTLE_LOW, 200, 500);
    Zinc::addButtonEvent(BTN_2, UpBtn, THROTTLE_LOW, 200, 500);
    Zinc::addButtonEvent(BTN_3, DownBtn, THROTTLE_LOW, 200, 500);
}

uint32_t menuTimeout = 0;
boolean menuSelected = false;

void displayMenu() {
    uint16_t flashCount_Show = 1; // Keep the led on constant
    uint16_t flashCount_Selected = MENU_DURATION / 200; // Flashing every 200ms

    switch (menu) {
        case 0:
            // Red - Off
            flashRGB(255, 0, 0, MENU_DURATION, flashCount_Show);
            break;
        case 1:
            // Green - Show Static White Spots
            flashRGB(0, 255, 0, MENU_DURATION, flashCount_Show);
            break;
        case 2:
            // Blue - Show Animated Spots
            flashRGB(0, 0, 255, MENU_DURATION, flashCount_Show);
            break;
        case 3:
            // Yellow - Speed
            flashRGB(255, 255, 0, MENU_DURATION, menuSelected ? flashCount_Selected : flashCount_Show);
            break;
        case 4:
            // Teal - Colour Count
            flashRGB(0, 255, 255, MENU_DURATION, menuSelected ? flashCount_Selected : flashCount_Show);
            break;
        case 5:
            // Purple - White Count
            flashRGB(255, 0, 255, MENU_DURATION, menuSelected ? flashCount_Selected : flashCount_Show);
            break;
        default:
            flashRGB(0, 0, 0, 1, 0);
            return;
    }
    menuTimeout = millis() + MENU_DURATION;
}

void changeMode(uint8_t newMode) {
    if (tIdWarmUp != 0) {
        Zinc::removeTimerEvent(tIdWarmUp);
        tIdWarmUp = 0;
    }
    if (animationId != 0) {
        Animations::remove(animationId);
        animationId = 0;
    }
    switch (newMode) {
        case 0:
            // Red - Off
            strip.fill(Adafruit_NeoPixel::Color(0, 0, 0, 0));
            strip.show();
            flashRGB(255, 0, 0, 400, 3);
            break;
        case 1:
            // Green - Show Static White Spots
            StaticWhiteSpots::draw(strip);
            flashRGB(0, 255, 0, 400, 3);
            break;
        case 2:
            // Blue - Show Animated Spots
            resetAnimation();
            flashRGB(0, 0, 255, 400, 3);
            break;
        default:
            return;
    }
    mode = newMode;
    menuTimeout = 0;
}

void initMenu() {
    menu = 0;
    menuSelected = false;
    displayMenu();
}

void selectBtn() {
    if (millis() < menuTimeout) {
        // Do Action...
        switch (menu) {
            case 0:
            case 1:
            case 2:
                changeMode(menu);
                break;
            case 3:
            case 4:
            case 5:
                menuSelected = !menuSelected;
                displayMenu();
                break;
            default:
                return;
        }
    } else {
        initMenu();
    }
}

void UpBtn() {
    if (millis() < menuTimeout) {
        if (menuSelected) {
            switch (menu) {
                case 3: // Speed
                    if (gap > 5) {
                        gap -= 5;
                        if (animationId != 0) {
                            resetAnimation();
                        }
                    }
                    break;
                case 4: // Colour Count
                    if (colorCount < 255) {
                        colorCount++;
                        if (animationId != 0) {
                            resetAnimation();
                        }
                    }
                    break;
                case 5: // White Count
                    if (whiteCount < 255) {
                        whiteCount++;
                        if (animationId != 0) {
                            resetAnimation();
                        }
                    }
                    break;
                default:
                    return;
            }
        } else {
            if (menu == 5) {
                menu = 0;
            } else {
                menu++;
            }
        }
        displayMenu();
    } else {
        initMenu();
    }
}

void DownBtn() {
    if (millis() < menuTimeout) {
        if (menuSelected) {
            switch (menu) {
                case 3: // Speed
                    if (gap < 120000) {
                        gap += 5;
                        if (animationId != 0) {
                            resetAnimation();
                        }
                    }
                    break;
                case 4: // Colour Count
                    if (colorCount > 0) {
                        colorCount--;
                        if (animationId != 0) {
                            resetAnimation();
                        }
                    }
                    break;
                case 5: // White Count
                    if (whiteCount > 0) {
                        whiteCount--;
                        if (animationId != 0) {
                            resetAnimation();
                        }
                    }
                    break;
                default:
                    return;
            }
        } else {
            if (menu == 0) {
                menu = 5;
            } else {
                menu--;
            }
        }
        displayMenu();
    } else {
        initMenu();
    }
}

void initStrip() {
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

    tIdWarmUp = Zinc::addTimerEvent([](uint16_t id, uint16_t frame) -> void {
        StaticWhiteSpots::draw(strip);
    }, 0, 1, 180); // 000

}

void stopShow() {
    if (tIdShow != 0) {
        Zinc::removeTimerEvent(tIdShow);
        tIdShow = 0;
    }
}

void show(uint32_t frameLength, uint16_t frameCount, unsigned long initDelay) {
    stopShow();
    tIdShow = Zinc::addTimerEvent([](uint16_t id, uint16_t frame) -> void { strip.show(); }, frameLength, frameCount,
                                  initDelay, nullptr,
                                  [](uint16_t id, uint16_t frame) -> void {
                                      strip.show();
                                      tIdShow = 0;
                                  });
}

void stripOff() {
    // Flash builtin LED slow to show it detected the LED Strip power going off...
    flashBuiltIn(1000, 10);
}

void stripOn() {
    // Flash builtin LED fast to show it detected the LED Strip power coming back on...
    flashBuiltIn(1000, 30);
    // The strip has only just got power back so we need to tell it what to display again
    // Here we are delaying that and repeating as if we do it too quick it doesn't draw properly...
    show(50, 10);
}

void resume() {
    if (animationId == 0) {
        resetAnimation();
    } else {
        Animations::resume(animationId);
    }
}

void pause() {
    if (animationId > 0) {
        Animations::pause(animationId);
    }
}

void resetAnimation() {
    if (animationId != 0) {
        Animations::remove(animationId);
    }
    stopShow();
    strip.fill(Adafruit_NeoPixel::Color(0, 0, 0, 0));
    animationId = Animations::runningSpots(strip, colorCount, whiteCount, true, gap);
}

void loop() {
    Zinc::process();
}

