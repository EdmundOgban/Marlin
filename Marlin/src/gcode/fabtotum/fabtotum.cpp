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
 * fabtotum.cpp - FABtotum custom GCode and machinery
 *
 */
 

#include "fabtotum.h"

//MachineManager machine;
bool silent = false;

static inline const void beep(uint8_t period, uint8_t t) {
  SET_PWM(BEEPER_PIN);
  analogWrite(BEEPER_PIN, period);
  delay(t);
}

static void fab_beep() {
  if (silent)
    return;

  //play intro tune
  beep(180, 50);
  beep(0, 50);

  beep(185, 50);
  beep(0, 50);

  beep(190, 50);
  beep(0, 80);

  beep(115, 100);
  beep(0, 100);
}

void FABtotum::M300() {
  BUZZ(10, 5989);
  delay(10);
  BUZZ(10, 5989);
  delay(10);
}

void FABtotum::M728() {
  amblight.fade_off();
  fab_beep();
}

void FABtotum::M701() {
  if (parser.seenval('S'))
    amblight.set_red(parser.value_byte());
}

void FABtotum::M702() {
  if (parser.seenval('S'))
    amblight.set_green(parser.value_byte());
}

void FABtotum::M703() {
  if (parser.seenval('S'))
    amblight.set_blue(parser.value_byte());
}

void FABtotum::M735() {
  if (parser.seenval('S'))
    silent = parser.value_bool();
}

// read HOT_BED placed in place
void FABtotum::M744() {
  if (thermalManager.degBed() > 0)
    SERIAL_ECHOLNPGM(STR_ENDSTOP_HIT);
  else
    SERIAL_ECHOLNPGM(STR_ENDSTOP_OPEN);
}

// read FABtotum Personal Fabricator Main Controller board version number
void FABtotum::M762() {
}

// read FABtotum Personal Fabricator Main Controller production batch number
void FABtotum::M763() {
    // if (parser.seenval('S')) {
    //     machine.set_batch_number(parser.value_long());
    // }
    // else {
    //     SERIAL_PRINTLN(machine.batch_number, DEC);
    // }
}
