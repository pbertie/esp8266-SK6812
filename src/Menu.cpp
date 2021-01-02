//
// Created by paul on 02/01/2021.
//

#include "Menu.h"
#include "StaticWhiteSpots.h"
#include "RunningSpots.h"
#include "config.h"
#include "Zinc.h"
#include "statusLeds.h"
#include "main.h"
#include "Strip.h"

namespace Menu {

#define MENU_DURATION 10000
    uint8_t mode = 0;
    uint8_t menu = 0;

    uint32_t menuTimeout = 0;
    boolean menuSelected = false;

    void selectBtn();

    void UpBtn();

    void DownBtn();

    void init() {
        Zinc::addButtonEvent(BTN_1, selectBtn, TRIGGER_LOW);
        Zinc::addButtonEvent(BTN_2, UpBtn, TRIGGER_LOW);
        Zinc::addButtonEvent(BTN_3, DownBtn, TRIGGER_LOW);

        Zinc::addButtonEvent(BTN_1, selectBtn, THROTTLE_LOW, 200, 500);
        Zinc::addButtonEvent(BTN_2, UpBtn, THROTTLE_LOW, 200, 500);
        Zinc::addButtonEvent(BTN_3, DownBtn, THROTTLE_LOW, 200, 500);
    }

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
        cancelWarmUp();
        RunningSpots::stop();
        switch (newMode) {
            case 0:
                // Red - Off
                Strip::clear();
                Strip::show();
                flashRGB(255, 0, 0, 400, 3);
                break;
            case 1:
                // Green - Show Static White Spots
                StaticWhiteSpots::draw();
                flashRGB(0, 255, 0, 400, 3);
                break;
            case 2:
                // Blue - Show Animated Spots
                RunningSpots::resume();
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
                        RunningSpots::speedUp();
                        break;
                    case 4: // Colour Count
                        RunningSpots::colourCountUp();
                        break;
                    case 5: // White Count
                        RunningSpots::whiteCountUp();
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
                        RunningSpots::speedDown();
                        break;
                    case 4: // Colour Count
                        RunningSpots::colourCountDown();
                        break;
                    case 5: // White Count
                        RunningSpots::whiteCountDown();
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

}