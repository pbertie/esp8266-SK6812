//
// Created by paul on 07/01/2021.
//

#include "ZWebServer.h"

namespace ZWebServer {

    ESP8266WebServer server(80);

    void begin() {
        server.begin();
    }

    void close() {
        server.close();
    }

    void handleClient() {
        server.handleClient();
    }

    void on(const Uri &uri, HTTPMethod method, handler fn) {
        server.on(uri, method, fn);
    }

    void onNotFound(handler fn) {
        server.onNotFound(fn);
    }

    void send(int code, const char *content_type, const char *content) {
        server.send(code, content_type, content);
    }

    void send(int code, const char *content_type, const String& content) {
        server.send(code, content_type, content);
    }

    void sendHeader(const String &name, const String &value, bool first) {
        server.sendHeader("Location", "/", first);
    }

}