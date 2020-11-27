//
// Created by paul on 06/12/2020.
//

#include "ZNetwork.h"
#include "ZAnimate.h"
#include "ZLogging.h"

/*
 * TODO: When in AP Mode I'd like to allow it to take in new credentials so new networks can be added
 */

namespace ZNetwork {

    void startWifiMonitorLoop(uint16_t id, uint16_t frame);

    uint16_t wifiConnectLoopId;
    uint16_t wifiMonitorLoopId;

    IPAddress local_IP(192,168,20,20);

    IPAddress gateway(192,168,20,9);

    IPAddress subnet(255,255,255,0);

    ESP8266WiFiMulti wifiMulti;

    const char* ap_ssid;
    const char* ap_pass;

    bool apOn(bool force = false) {
        bool isEnabled = ((WiFi.getMode() & WIFI_AP) != 0);
        if (!isEnabled || force) {
            if (WiFi.softAPConfig(local_IP, gateway, subnet)) {
                return WiFi.softAP(ap_ssid, ap_pass, 1);
            }
        }
        return false;
    }

    bool apOff() {
        return WiFi.softAPdisconnect (true);
    }

    void wifiConnectLoop(uint16_t id, uint16_t frame) {
        if (wifiMulti.run() == WL_CONNECTED) {
            apOff();
            ZAnimate::setActive(wifiMonitorLoopId, true);
            ZAnimate::setActive(wifiConnectLoopId, false);
            ZLogging::log("Connected to " + WiFi.SSID());
            ZLogging::log("IP address:\t" + WiFi.localIP().toString());
        }
    }

    void wifiMonitorLoop(uint16_t id, uint16_t frame) {
        if (!WiFi.isConnected()) {
            apOn();
            ZAnimate::setActive(wifiMonitorLoopId, false);
            ZAnimate::setActive(wifiConnectLoopId, true);
            ZLogging::log("Disconnected, AP Enabled");
        }
    }

    void startWifiConnectLoop(uint16_t id, uint16_t frame) {
        wifiConnectLoopId = ZAnimate::add(wifiConnectLoop, 1000, 10000, 0, nullptr, startWifiConnectLoop, true);
    }

    void startWifiMonitorLoop(uint16_t id, uint16_t frame) {
        wifiMonitorLoopId = ZAnimate::add(wifiMonitorLoop, 1000, 10000, 0, nullptr, startWifiMonitorLoop, true);
    }

    void beginNetwork(NetworkCredentials ap) {

        ap_ssid = ap.ssid;
        ap_pass = ap.pass;

        // Create temporary network so we can send new credentials if needed...
        apOn(true);

        ZLogging::log("Looking for known connection ...");
        startWifiConnectLoop(0, 0);
        startWifiMonitorLoop(0, 0);
        ZAnimate::setActive(wifiMonitorLoopId, false);
    }

    void addNetwork(NetworkCredentials network) {
        wifiMulti.addAP(network.ssid, network.pass);
    }
}