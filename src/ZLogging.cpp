//
// Created by paul on 30/11/2020.
//

#include "ZLogging.h"

namespace ZLogging {

#if DEBUG_OUTPUT == true

    void beginLogger(unsigned long baud) {
        Serial.begin(baud);
    }

    void log(const char *str) {
        div_t d = div(millis(), 1000);
        Serial.print(d.quot), Serial.write('.'), Serial.print(d.rem);
        Serial.print(" >>> ");
        Serial.println(str);
    }

    void log(const String& str) {
        div_t d = div(millis(), 1000);
        Serial.print(d.quot), Serial.write('.'), Serial.print(d.rem);
        Serial.print(" >>> ");
        Serial.println(str);
    }
#else
    void setupLogger(unsigned long baud) {}
    void log(const char *str) {}
    void log(String str) {}
#endif
}