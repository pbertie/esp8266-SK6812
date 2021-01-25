//
// Created by paul on 06/12/2020.
//

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include "ZNetwork.h"
#include "ZTimer.h"
#include "ZLogging.h"
#include "ZWebServer.h"

namespace ZNetwork {

    ESP8266WebServer setupServer(8080);

    void startWifiMonitorLoop(uint16_t id, uint16_t frame);

    void handleAddNetwork();

    uint16_t wifiConnectLoopId;
    uint16_t wifiMonitorLoopId;

    IPAddress local_IP(192,168,20,20);

    IPAddress gateway(192,168,20,20);

    IPAddress subnet(255,255,255,0);

    ESP8266WiFiMulti wifiMulti;

    const char* ap_ssid;
    const char* ap_pass;

    bool networkConnected = false;
    const char* _hostname;

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
            setupServer.close();
            apOff();
            ZTimer::setActive(wifiMonitorLoopId, true);
            ZTimer::setActive(wifiConnectLoopId, false);
            ZLogging::log("Connected to " + WiFi.SSID());
            ZLogging::log("IP address:\t" + WiFi.localIP().toString());
            ZWebServer::begin();
            if (MDNS.begin(_hostname)) {
                ZLogging::log("mDNS responder started");
                MDNS.addService("http", "tcp", 80);
            } else {
                ZLogging::log("Error setting up mDNS responder!");
            }
            networkConnected = true;
        }
    }

    void wifiMonitorLoop(uint16_t id, uint16_t frame) {
        if (!WiFi.isConnected()) {
            networkConnected = false;
            MDNS.close();
            ZWebServer::close();
            apOn();
            ZTimer::setActive(wifiMonitorLoopId, false);
            ZTimer::setActive(wifiConnectLoopId, true);
            ZLogging::log("Disconnected, AP Enabled");
            setupServer.begin();
        }
    }

    void startWifiConnectLoop(uint16_t id, uint16_t frame) {
        wifiConnectLoopId = ZTimer::add(wifiConnectLoop, 1000, 10000, 0, nullptr, startWifiConnectLoop, true);
    }

    void startWifiMonitorLoop(uint16_t id, uint16_t frame) {
        wifiMonitorLoopId = ZTimer::add(wifiMonitorLoop, 1000, 10000, 0, nullptr, startWifiMonitorLoop, true);
    }

    void beginNetwork(NetworkCredentials ap, const char* hostname) {

        ap_ssid = ap.ssid;
        ap_pass = ap.pass;
        _hostname = hostname;

        setupServer.on("/", [](){
            setupServer.send(200, "text/html", R"(<form action="/add" method="POST"><input type="text" name="ssid" placeholder="SSID"></br><input type="password" name="password" placeholder="Password"></br><input type="password" name="vcode" placeholder="VCode"></br><input type="submit" value="Login"></form><p>Add network credentials</p>)");
        });
        setupServer.on("/add", HTTP_POST, handleAddNetwork);

        // Create temporary network so we can send new credentials if needed...
        apOn(true);
        setupServer.begin();

        ZLogging::log("Looking for known connection ...");
        startWifiConnectLoop(0, 0);
        startWifiMonitorLoop(0, 0);
        ZTimer::setActive(wifiMonitorLoopId, false);
    }

    void addNetwork(NetworkCredentials network) {
        wifiMulti.addAP(network.ssid, network.pass);
    }

    void handleAddNetwork() {
        if( !setupServer.hasArg("ssid") || !setupServer.hasArg("password") || !setupServer.hasArg("vcode")
            || setupServer.arg("ssid") == nullptr || setupServer.arg("password") == nullptr || setupServer.arg("vcode") != WIFI_ADD_VCODE) {
            setupServer.send(400, "text/plain", "Invalid Request</br><a href=\"/\">Home</a>");
            return;
        }
        const String &ssid = setupServer.arg("ssid");
        const String &password = setupServer.arg("password");
        if (ssid.length() == 0 || ssid.length() > 32) {
            setupServer.send(400, "text/plain", "Invalid SSID</br><a href=\"/\">Home</a>");
            return;
        }
        // TODO: Consider storing this in permanent storage so it's available on restart...
        wifiMulti.addAP(ssid.c_str(), password.c_str());
        setupServer.send(200, "text/html", "<h1>Complete</h1><p>Network Added</br><a href=\"/\">Home</a></p>");
    }

    void process() {
        if (networkConnected) {
            MDNS.update();
        }
    }
}