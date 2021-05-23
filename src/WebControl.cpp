//
// Created by paul on 07/01/2021.
//

#include "WebControl.h"
#include "Zinc.h"
#include "StaticWhiteSpots.h"
#include "DoorBeam.h"
#include "RunningSpots.h"
#include "Menu.h"

namespace WebControl {

    void redirect();
    void handleRoot();

    const char *pageMainStart = R"(<html><head><meta name="viewport" content="width=device-width, initial-scale=1.0"></head><body><div style="margin: 1em auto; text-align: center;">)";
    const char *pageMainEnd = R"(</div></body></html>)";
    const char *pageSpacingStart = R"(<h1>Spacing</h1><button onclick="window.location='/staticWhite/spacingUp'">Up</button></br>)";
    const char *pageSpacingEnd = R"(</br><button onclick="window.location='/staticWhite/spacingDown'">Down</button>)";

    const char *pageDoorBeamSpacingStart = R"(<h1>Spacing</h1><button onclick="window.location='/doorBeam/spacingUp'">Up</button></br>)";
    const char *pageDoorBeamSpacingEnd = R"(</br><button onclick="window.location='/doorBeam/spacingDown'">Down</button>)";
    const char *pageDoorBeamSizeStart = R"(<h1>Size</h1><button onclick="window.location='/doorBeam/sizeUp'">Up</button></br>)";
    const char *pageDoorBeamSizeEnd = R"(</br><button onclick="window.location='/doorBeam/sizeDown'">Down</button>)";

    const char *pageColourCountStart = R"(<h1>Colour Count</h1><button onclick="window.location='/runningSpots/colourUp'">Up</button></br>)";
    const char *pageColourCountEnd = R"(</br><button onclick="window.location='/runningSpots/colourDown'">Down</button>)";
    const char *pageWhiteCountStart = R"(<h1>White Count</h1><button onclick="window.location='/runningSpots/whiteUp'">Up</button></br>)";
    const char *pageWhiteCountEnd = R"(</br><button onclick="window.location='/runningSpots/whiteDown'">Down</button>)";

    const char *pageModeStart = R"(<h1>Mode</h1>)";
    const char *pageModeOff = R"(<button onclick="window.location='/mode/off'">Off</button></br></br>)";
    const char *pageModeStaticWhite = R"(<button onclick="window.location='/mode/staticWhite'">Static White</button></br></br>)";
    const char *pageModeRunningSpots = R"(<button onclick="window.location='/mode/runningSpots'">Running Spots</button></br></br>)";
    const char *pageModeDoorBeam = R"(<button onclick="window.location='/mode/doorBeam'">Door Beam</button></br></br>)";

    void setup() {

        ZWebServer::onNotFound(redirect);

        ZWebServer::on("/", HTTP_GET, handleRoot);

        ZWebServer::on("/mode/off", HTTP_GET, []() {
            Menu::changeMode(MENU_OFF);
            redirect();
        });

        ZWebServer::on("/mode/staticWhite", HTTP_GET, []() {
            Menu::changeMode(MENU_STATIC_WHITE);
            redirect();
        });

        ZWebServer::on("/mode/runningSpots", HTTP_GET, []() {
            Menu::changeMode(MENU_RUNNING_SPOTS);
            redirect();
        });

        ZWebServer::on("/mode/doorBeam", HTTP_GET, []() {
            Menu::changeMode(MENU_DOOR_BEAM);
            redirect();
        });

        ZWebServer::on("/doorBeam/sizeUp", HTTP_GET, []() {
            DoorBeam::sizeUp();
            redirect();
        });

        ZWebServer::on("/doorBeam/sizeDown", HTTP_GET, []() {
            DoorBeam::sizeDown();
            redirect();
        });

        ZWebServer::on("/doorBeam/spacingUp", HTTP_GET, []() {
            DoorBeam::spacingUp();
            redirect();
        });

        ZWebServer::on("/doorBeam/spacingDown", HTTP_GET, []() {
            DoorBeam::spacingDown();
            redirect();
        });

        ZWebServer::on("/staticWhite/spacingUp", HTTP_GET, []() {
            StaticWhiteSpots::spacingUp();
            redirect();
        });

        ZWebServer::on("/staticWhite/spacingDown", HTTP_GET, []() {
            StaticWhiteSpots::spacingDown();
            redirect();
        });

        ZWebServer::on("/runningSpots/whiteUp", HTTP_GET, []() {
            RunningSpots::whiteCountUp();
            redirect();
        });

        ZWebServer::on("/runningSpots/whiteDown", HTTP_GET, []() {
            RunningSpots::whiteCountDown();
            redirect();
        });

        ZWebServer::on("/runningSpots/colourUp", HTTP_GET, []() {
            RunningSpots::colourCountUp();
            redirect();
        });

        ZWebServer::on("/runningSpots/colourDown", HTTP_GET, []() {
            RunningSpots::colourCountDown();
            redirect();
        });
    }

    void redirect() {
        ZWebServer::sendHeader("Location", "/", true);
        ZWebServer::send(302, "text/plain","");
    }

    void handleRoot() {
        String s;
        uint8_t mode = Menu::getMode();
        s.concat(pageMainStart);
        if (mode == MENU_STATIC_WHITE) {
            s.concat(pageSpacingStart);
            s.concat(StaticWhiteSpots::getSpacing());
            s.concat(pageSpacingEnd);
        } else if (mode == MENU_RUNNING_SPOTS) {
            s.concat(pageColourCountStart);
            s.concat(RunningSpots::getColorCount());
            s.concat(pageColourCountEnd);
            s.concat(pageWhiteCountStart);
            s.concat(RunningSpots::getWhiteCount());
            s.concat(pageWhiteCountEnd);
        } else if (mode == MENU_DOOR_BEAM) {
            s.concat(pageDoorBeamSizeStart);
            s.concat(DoorBeam::getSize());
            s.concat(pageDoorBeamSizeEnd);
            s.concat(pageDoorBeamSpacingStart);
            s.concat(DoorBeam::getSpacing());
            s.concat(pageDoorBeamSpacingEnd);
        }
            s.concat(pageModeStart);
        if (mode != MENU_OFF) {
            s.concat(pageModeOff);
        }
        if (mode != MENU_STATIC_WHITE) {
            s.concat(pageModeStaticWhite);
        }
        if (mode != MENU_RUNNING_SPOTS) {
            s.concat(pageModeRunningSpots);
        }
        if (mode != MENU_DOOR_BEAM) {
            s.concat(pageModeDoorBeam);
        }
        s.concat(pageMainEnd);
        ZWebServer::send(200, "text/html", s);
    }

}