//
// Created by paul on 20/11/2020.
//

#include "ZTimer.h"

namespace ZTimer {
    class TimerEventDef {
    public:
        TimerEventDef(uint16_t id, unsigned long nextTrigger, uint16_t frame, uint32_t frameLength,
                      uint16_t frameCount, bool skipMissedFrames, frameCallback cb, frameCallback cbStart,
                      frameCallback cbEnd);

        uint16_t id;
        unsigned long nextTrigger;
        unsigned long pauseDelay;
        uint16_t frame;
        uint32_t frameLength;
        uint16_t frameCount;
        bool skipMissedFrames;
        bool active;

        frameCallback cb;

        frameCallback cb_start;

        frameCallback cb_end;
    };

    TimerEventDef::TimerEventDef(uint16_t id, unsigned long nextTrigger, uint16_t frame, uint32_t frameLength,
                                 uint16_t frameCount, bool skipMissedFrames, frameCallback cb,
                                 frameCallback cbStart, frameCallback cbEnd)
            : id(id), nextTrigger(nextTrigger), pauseDelay(0), frame(frame), frameLength(frameLength),
              frameCount(frameCount), skipMissedFrames(skipMissedFrames), active(true), cb(cb), cb_start(cbStart),
              cb_end(cbEnd) {}

    LinkedList<TimerEventDef *> eventList;
    uint16_t nextId = 1;

    void process() {
        unsigned long now;

        uint16_t listSize = eventList.size();
        for (uint16_t i = 0; i < listSize; i++) {
            TimerEventDef *e = eventList.get(i);
            if (e->active && e->frame < e->frameCount) {
                now = millis();

                if (now > e->nextTrigger) {
                    // Execute the callback, the first or last will take place of the standard cb if provided...
                    if (e->cb_start != nullptr && e->frame == 0) {
                        (*e->cb_start)(e->id, ++e->frame);
                    } else if (e->cb_end != nullptr && e->frame == e->frameCount - 1) {
                        (*e->cb_end)(e->id, ++e->frame);
                    } else if (e->cb != nullptr) {
                        (*e->cb)(e->id, ++e->frame);
                    }

                    e->nextTrigger += e->frameLength;
                    if (e->skipMissedFrames) {
                        now = millis();
                        // Skip frames if they're overdue, ensure the last frame is never skipped...
                        while (now > e->nextTrigger && e->frame < e->frameCount - 1) {
                            e->nextTrigger += e->frameLength;
                            e->frame++;
                        }
                    }
                }
            }
        }

        // Iterate backwards removing any expired events...
        if (listSize > 0) {
            // i is 1 higher that index to avoid overflows on unsigned...
            for (uint16_t i = listSize; i > 0; i--) {
                TimerEventDef *e = eventList.get(i - 1);
                if (e->frame >= e->frameCount) {
                    eventList.remove(i - 1);
                }
            }
        }
    }

    uint16_t
    add(frameCallback cb, uint32_t frameLength, uint16_t frameCount, unsigned long initDelay, frameCallback cb_start,
        frameCallback cb_end, bool skipMissedFrames) {
        unsigned long now = millis();
        auto *e = new TimerEventDef(nextId, now + initDelay, 0, frameLength, frameCount, skipMissedFrames, cb,
                                    cb_start, cb_end);
        eventList.add(e);
        return nextId++;
    }

    void remove(uint16_t id) {
        uint16_t listSize = eventList.size();
        // i is 1 higher that index to avoid overflows on unsigned...
        for (uint16_t i = listSize; i > 0; i--) {
            TimerEventDef *e = eventList.get(i - 1);
            if (e->id == id) {
                delete e;
                eventList.remove(i - 1);
                break;
            }
        }
    }

    void setActive(uint16_t id, bool active) {
        uint16_t listSize = eventList.size();
        for (uint16_t i = 0; i < listSize; i++) {
            TimerEventDef *e = eventList.get(i);
            if (e->id == id) {
                e->active = active;
                unsigned long now = millis();

                if (active) {
                    // Resume with as much on the clock as there was when we paused...
                    e->nextTrigger = now + e->pauseDelay;
                } else if (now > e->nextTrigger) {
                    // Pause but next frame is already due so when resumed will be immediate...
                    // Note the amount it was behind is removed as we are using unsigned variables.
                    e->pauseDelay = 0;
                } else {
                    // Pause and record how long is left before the next frame is due...
                    e->pauseDelay = e->nextTrigger - now;
                }
                break;
            }
        }
    }
}