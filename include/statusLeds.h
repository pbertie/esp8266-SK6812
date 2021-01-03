//
// Created by paul on 07/12/2020.
//

#ifndef ESPSTRIP_STATUSLEDS_H
#define ESPSTRIP_STATUSLEDS_H

#include <cstdint>

uint16_t flashBuiltIn(uint32_t duration = 500, uint16_t count = 1, unsigned long initDelay = 0);

uint16_t flashR(uint32_t duration = 500, uint16_t count = 1, unsigned long initDelay = 0);

uint16_t flashG(uint32_t duration = 500, uint16_t count = 1, unsigned long initDelay = 0);

uint16_t flashB(uint32_t duration = 500, uint16_t count = 1, unsigned long initDelay = 0);

uint16_t flashRGB(uint8_t R, uint8_t G, uint8_t B, uint32_t duration = 500, uint16_t count = 1, unsigned long initDelay = 0);

#endif //ESPSTRIP_STATUSLEDS_H
