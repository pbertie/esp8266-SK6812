//
// Created by paul on 07/01/2021.
//

#ifndef ESPSTRIP_ZWEBSERVER_H
#define ESPSTRIP_ZWEBSERVER_H

#include <ESP8266WebServer.h>

namespace ZWebServer {

    typedef void (*handler)();

    void begin();

    void close();

    void handleClient();

    void on(const Uri &uri, HTTPMethod method, handler fn);

    void onNotFound(handler fn);

    void send(int code, const char *content_type, const char *content);

    void send(int code, const char *content_type, const String& content);

    void sendHeader(const String &name, const String &value, bool first = false);

}

#endif //ESPSTRIP_ZWEBSERVER_H
