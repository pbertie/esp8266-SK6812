//
// Created by paul on 20/11/2020.
//

#include "Animations.h"

namespace Animations {

    class RunningSpotData {
    public:
        RunningSpotData(uint16_t id, uint16_t animId, Adafruit_NeoPixel* strip, uint8_t colorCount, uint8_t whiteCount,
                        bool looped, uint32_t gap)
                : id(id), animId(animId), strip(strip), colorCount(colorCount), whiteCount(whiteCount), looped(looped), gap(gap) {}

        uint16_t id;
        uint16_t animId;
        Adafruit_NeoPixel* strip;
        uint8_t colorCount;
        uint8_t whiteCount;
        bool looped;
        uint32_t gap;
    };

    LinkedList<RunningSpotData *> animationData;

    void runningSpots_frame(uint16_t animId, uint16_t frame);

    void runningSpots_end(uint16_t animId, uint16_t frame);

    RunningSpotData *getData(uint16_t id);

    RunningSpotData *getDataByAnimId(uint16_t animId);

    void removeData(uint16_t id);

    void processRunningSpotsFrame(Adafruit_NeoPixel &strip, uint32_t frame, uint8_t colorCount, uint8_t whiteCount, bool looped);

    uint16_t nextId = 1;
    
    uint16_t runningSpots(Adafruit_NeoPixel &strip, uint8_t colorCount, uint8_t whiteCount, bool looped, uint32_t gap) {
        uint16_t ledCount = strip.numPixels();

        uint16_t animId = Zinc::addAnimateEvent(runningSpots_frame, gap, ledCount, 0, nullptr,
                                                runningSpots_end);
        auto *data = new RunningSpotData(nextId, animId, &strip, colorCount, whiteCount, looped, gap);
        animationData.add(data);
        return nextId++;
    }

    void runningSpots_frame(uint16_t animId, uint16_t frame) {
        RunningSpotData *data = getDataByAnimId(animId);
        if (data != nullptr) {
            processRunningSpotsFrame(*data->strip, frame, data->colorCount, data->whiteCount, data->looped);
        }
    }

    void runningSpots_end(uint16_t animId, uint16_t frame) {
        runningSpots_frame(animId, frame);
        RunningSpotData *data = getDataByAnimId(animId);
//        removeData(data->id);
        data->animId = Zinc::addAnimateEvent(runningSpots_frame, data->gap, data->strip->numPixels(), data->gap, nullptr,
                                                runningSpots_end);
    }

    RunningSpotData *getDataByAnimId(uint16_t animId) {
        uint16_t listSize = animationData.size();
        for (uint16_t i = 0; i < listSize; i++) {
            RunningSpotData *data = animationData.get(i);
            if (data->animId == animId) {
                return data;
            }
        }
        return nullptr;
    }

    RunningSpotData *getData(uint16_t id) {
        uint16_t listSize = animationData.size();
        for (uint16_t i = 0; i < listSize; i++) {
            RunningSpotData *data = animationData.get(i);
            if (data->id == id) {
                return data;
            }
        }
        return nullptr;
    }

    void removeData(uint16_t id) {
        uint16_t listSize = animationData.size();
        // i is 1 higher that index to avoid overflows on unsigned...
        for (uint16_t i = listSize; i > 0; i++) {
            RunningSpotData *data = animationData.get(i - 1);
            if (data->id == id) {
                delete data;
                animationData.remove(i - 1);
                break;
            }
        }
    }

    void remove(uint16_t id) {
        RunningSpotData *data = getData(id);
        Zinc::removeAnimateEvent(data->animId);
        removeData(id);
    }

    void pause(uint16_t id) {
        RunningSpotData *data = getData(id);
        if (data != nullptr) {
            Zinc::pauseAnimateEvent(data->animId);
        }
    }

    void resume(uint16_t id) {
        RunningSpotData *data = getData(id);
        if (data != nullptr) {
            Zinc::resumeAnimateEvent(data->animId);
        }
    }

    void processRunningSpotsFrame(Adafruit_NeoPixel &strip, uint32_t frame, uint8_t colorCount, uint8_t whiteCount, bool looped) {
        uint16_t ledCount = strip.numPixels();

        uint16_t i, hue;
        uint8_t colorGroup;

        uint8_t colorSpacing = ledCount / colorCount;
        uint8_t whiteSpacing = ledCount / whiteCount;


        if (!looped) {
            for (i = 0; i < 11; i++) {
                strip.setPixelColor(i, 0);
            }
            for (i = ledCount - 11; i < ledCount; i++) {
                strip.setPixelColor(i, 0);
            }
        }

        for (i = 0; i < colorCount; i++) {
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
            drawSpot_7(strip, pos, hue, 255, 255, looped);
        }

        for (i = 0; i < whiteCount; i++) {

            uint16_t pos = (ledCount + ( i * whiteSpacing) - (frame % ledCount)) % ledCount;
            drawSpot_11(strip, pos, 0, 0, 200, looped);
        }
        strip.show();
    }
}
