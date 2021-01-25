//
// Created by paul on 06/12/2020.
//

#ifndef ESPSTRIP_ZNETWORK_H
#define ESPSTRIP_ZNETWORK_H

namespace ZNetwork {

    struct NetworkCredentials {
        const char* ssid;
        const char* pass;
    };

    void beginNetwork(NetworkCredentials ap, const char* hostname);
    void addNetwork(NetworkCredentials network);

    void process();
}

#endif //ESPSTRIP_ZNETWORK_H
