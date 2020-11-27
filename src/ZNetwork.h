//
// Created by paul on 06/12/2020.
//

#ifndef ESPSTRIP_ZNETWORK_H
#define ESPSTRIP_ZNETWORK_H

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include "config.h"

namespace ZNetwork {

    struct NetworkCredentials {
        const char* ssid;
        const char* pass;
    };

    void beginNetwork(NetworkCredentials ap = {"ZINC-SETUP", nullptr});
    void addNetwork(NetworkCredentials network);
}

#endif //ESPSTRIP_ZNETWORK_H
