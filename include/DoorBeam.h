//
// Created by paul on 23/03/2021.
//

#ifndef ESPSTRIP_DOORBEAM_H
#define ESPSTRIP_DOORBEAM_H

#include <cstdint>

namespace DoorBeam {

    void draw();

    void spacingUp();

    void spacingDown();

    uint16_t getSpacing();

    void sizeUp();

    void sizeDown();

    uint16_t getSize();
}

#endif //ESPSTRIP_DOORBEAM_H
