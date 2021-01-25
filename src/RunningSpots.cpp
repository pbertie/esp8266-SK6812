//
// Created by paul on 02/01/2021.
//

#include "RunningSpots.h"
#include "config.h"
#include "Zinc.h"
#include "SpotLeds.h"
#include "Strip.h"

namespace RunningSpots {

    uint16_t timerId;
    uint8_t _colorCount = START_COLOR_COUNT;
    uint8_t _whiteCount = START_WHITE_COUNT;
    bool _looped;
    uint32_t _gap = START_SPEED;

    void doFrame(uint16_t id, uint16_t frame);
    void doLastFrame(uint16_t id, uint16_t frame);

    void createTimer(unsigned long initDelay) {
        timerId = Zinc::addTimerEvent(doFrame, _gap, 65535, initDelay, nullptr, doLastFrame);
    }

    void start() {
        stop();
        createTimer(0);
    }

    void start(uint8_t colorCount, uint8_t whiteCount, bool looped, uint32_t gap) {
        _colorCount = colorCount;
        _whiteCount = whiteCount;
        _looped = looped;
        _gap = gap;
        start();
    }

    void stop() {
        if (timerId != 0) {
            Zinc::removeTimerEvent(timerId);
            timerId = 0;
        }
    }

    void pause() {
        if (timerId != 0) {
            Zinc::pauseTimerEvent(timerId);
        }
    }

    void resume() {
        if (timerId != 0) {
            Zinc::resumeTimerEvent(timerId);
        } else {
            start();
        }
    }

    void doFrame(uint16_t id, uint16_t frame) {
        uint16_t ledCount = Strip::numPixels();

        uint16_t i, hue;
        uint8_t colorGroup;

        uint8_t colorSpacing = _colorCount > 0 ? ledCount / _colorCount : 1;
        uint8_t whiteSpacing =  _whiteCount > 0 ? ledCount / _whiteCount : 1;

        Strip::clear();

        for (i = 0; i < _colorCount; i++) {
            colorGroup = i % 6;

            switch (colorGroup) {
                case 0:
                    hue = 0;
                    break;
                case 1:
                    hue = 65535 * 0.33;
                    break;
                case 2:
                    hue = 65535 * 0.50;
                    break;
                case 3:
                    hue = 65535 * 0.16;
                    break;
                case 4:
                    hue = 65535 * 0.83;
                    break;
                default:
                    hue = 65535 * 0.66;
            }
            uint16_t pos = ((i * colorSpacing) + frame) % ledCount;
            drawSpot_7(pos, hue, 255, 255, _looped);
        }

        for (i = 0; i < _whiteCount; i++) {

            uint16_t pos = (ledCount + ( i * whiteSpacing) - (frame % ledCount)) % ledCount;
            drawSpot_11(pos, 0, 0, 200, _looped);
        }
        Strip::show();
    }

    void doLastFrame(uint16_t id, uint16_t frame) {
        doFrame(id, frame);
        createTimer(_gap);
    }

    void speedUp() {
        if (_gap > 5) {
            _gap -= 5;
            if (timerId != 0) {
                start();
            }
        }
    }
    void speedDown() {
        if (_gap < 120000) {
            _gap += 5;
            if (timerId != 0) {
                start();
            }
        }
    }

    void whiteCountUp() {
        if (_whiteCount < 255) {
            _whiteCount++;
        }
    }
    void whiteCountDown() {
        if (_whiteCount > 0) {
            _whiteCount--;
        }
    }

    void colourCountUp() {
        if (_colorCount < 255) {
            _colorCount++;
        }
    }
    void colourCountDown() {
        if (_colorCount > 0) {
            _colorCount--;
        }
    }

    uint8_t getColorCount() {
        return _colorCount;
    }

    uint8_t getWhiteCount() {
        return _whiteCount;
    }
}