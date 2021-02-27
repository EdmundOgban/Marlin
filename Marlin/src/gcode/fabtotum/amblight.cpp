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

/**
 * amblight.cpp - FABtotum software ambient light fading and dimming
 *
 */

#include "amblight.h"

// CASE_LIGHT_PIN is ACTIVE HIGH
// R/G/B is ACTIVE LOW
#define RGB_INVERT_POLARITY

#ifdef COMMON_INVERT_POLARITY
  #define C_HIGH LOW
  #define C_LOW HIGH
#else
  #define C_HIGH HIGH
  #define C_LOW LOW
#endif

#ifdef RGB_INVERT_POLARITY
  #define RGB_HIGH LOW
  #define RGB_LOW HIGH
#else
  #define RGB_HIGH HIGH
  #define RGB_LOW LOW
#endif


AmbientLight::AmbientLight()
    : fading(true)
{
    SET_OUTPUT(RED_PIN);
    SET_OUTPUT(GREEN_PIN);
    SET_OUTPUT(BLUE_PIN);
    SET_OUTPUT(CASE_LIGHT_PIN);

    WRITE(CASE_LIGHT_PIN, C_HIGH);
    set_color(255, 255, 0);
}

void AmbientLight::manage_dimming() {
    WRITE(RED_PIN, (red_cnt > red_target) ? RGB_LOW : RGB_HIGH);
    WRITE(GREEN_PIN, (green_cnt > green_target) ? RGB_LOW : RGB_HIGH);
    WRITE(BLUE_PIN, (blue_cnt > blue_target) ? RGB_LOW : RGB_HIGH);

    if (++red_cnt == TIME_CONSTANT)
        red_cnt = 0;

    if (++green_cnt == TIME_CONSTANT)
        green_cnt = 0;

    if (++blue_cnt == TIME_CONSTANT)
        blue_cnt = 0;
}

void AmbientLight::manage_fading() {
    WRITE(CASE_LIGHT_PIN, (common_cnt > common_target) ? C_LOW : C_HIGH);

    if (++common_cnt == TIME_CONSTANT) {
        common_cnt = 0;
        common_target += 1 * fading_dir;

        if (common_target == TIME_CONSTANT || common_target == 0)
            fading_dir = -fading_dir;
    }
}

void AmbientLight::tick() {
    manage_dimming();
    if (fading)
        manage_fading();
}

void AmbientLight::fade_on() {
    common_cnt = 0;
    common_target = max(max(r, g), b) / VAL_MAX * TIME_CONSTANT;
    fading = true;
}

void AmbientLight::fade_off() {
    fading = false;
    WRITE(CASE_LIGHT_PIN, C_HIGH);
}

void AmbientLight::set_color(uint8_t r, uint8_t g, uint8_t b) {
    this->r = r;
    this->g = g;
    this->b = b;
    red_target = int((double)r / VAL_MAX * TIME_CONSTANT);
    green_target = int((double)g / VAL_MAX * TIME_CONSTANT);
    blue_target = int((double)b / VAL_MAX * TIME_CONSTANT);
}

void AmbientLight::set_red(uint8_t r) {
    set_color(r, g, b);
}

void AmbientLight::set_green(uint8_t g) {
    set_color(r, g, b);
}

void AmbientLight::set_blue(uint8_t b) {
    set_color(r, g, b);
}

void AmbientLight::push() {
    old_r = r;
    old_g = g;
    old_b = b;
    old_fading = fading;
}

void AmbientLight::pop() {
    set_color(old_r, old_g, old_b);

    if (old_fading)
        fade_on();
    else
        fade_off();
}

AmbientLight amblight;
