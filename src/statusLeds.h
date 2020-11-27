//
// Created by paul on 07/12/2020.
//

#ifndef ESPSTRIP_STATUSLEDS_H
#define ESPSTRIP_STATUSLEDS_H

#include <cstdint>

void flashBuiltIn(uint32_t duration = 500, uint16_t count = 1, unsigned long initDelay = 0);

void flashR(uint32_t duration = 500, uint16_t count = 1, unsigned long initDelay = 0);

void flashG(uint32_t duration = 500, uint16_t count = 1, unsigned long initDelay = 0);

void flashB(uint32_t duration = 500, uint16_t count = 1, unsigned long initDelay = 0);

#endif //ESPSTRIP_STATUSLEDS_H
