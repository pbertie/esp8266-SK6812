//
// Created by paul on 02/01/2021.
//

#ifndef ESPSTRIP_MENU_H
#define ESPSTRIP_MENU_H

#include <cstdint>

#define MENU_OFF 0
#define MENU_STATIC_WHITE 1
#define MENU_RUNNING_SPOTS 2
#define MENU_DOOR_BEAM 3


namespace Menu {

    void init();

    uint8_t getMode();

    void changeMode(uint8_t newMode);
}

#endif //ESPSTRIP_MENU_H
