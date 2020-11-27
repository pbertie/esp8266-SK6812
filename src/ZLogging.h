//
// Created by paul on 21/11/2020.
//

#ifndef LEDSTRIP_LOGGING_H
#define LEDSTRIP_LOGGING_H

#define DEBUG_OUTPUT true

#include <Arduino.h>

namespace ZLogging {

    void beginLogger(unsigned long baud);

    void log(const char *str);

    void log(const String& str);
}

#endif //LEDSTRIP_LOGGING_H
