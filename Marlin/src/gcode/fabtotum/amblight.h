
/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#pragma once

/**
 * amblight.h - Include file for FABtotum software ambient light fading and dimming
 *
 */

#include "../../inc/MarlinConfig.h"
#include "../parser.h"

#define TIME_CONSTANT 16
#define VAL_MAX 255


class AmbientLight {
private:
    uint16_t red_cnt = 0, green_cnt = 0, blue_cnt = 0;
    uint16_t red_target = 0, green_target = 0, blue_target = 0;
    uint16_t common_cnt = 0;
    uint16_t common_target = 0;
    // uint8_t postscaler = 0;
    uint8_t r = 0, g = 0, b = 0;
    uint16_t old_r, old_g, old_b;
    bool old_fading, fading = false;
    int fading_dir = 1;

    inline void manage_dimming();
    inline void manage_fading();

public:
    AmbientLight();
    void tick();
    void set_color(uint8_t r, uint8_t g, uint8_t b);
    void set_red(uint8_t r);
    void set_green(uint8_t g);
    void set_blue(uint8_t b);
    void fade_on();
    void fade_off();
    void push();
    void pop();
};
