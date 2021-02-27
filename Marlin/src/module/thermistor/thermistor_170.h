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

// Pt100 with 4k7 pullup - FABTotum Extruder
const temp_entry_t temptable_170[] PROGMEM = {
    { OV(23), 300 },
    { OV(25), 295 },
    { OV(26), 290 },
    { OV(28), 285 },
    { OV(30), 280 },
    { OV(33), 275 },
    { OV(35), 270 },
    { OV(38), 265 },
    { OV(41), 260 },
    { OV(44), 255 },
    { OV(47), 250 },
    { OV(51), 245 },
    { OV(55), 240 },
    { OV(60), 235 },
    { OV(65), 230 },
    { OV(71), 225 },
    { OV(77), 220 },
    { OV(84), 215 },
    { OV(91), 210 },
    { OV(100), 205 },
    { OV(109), 200 },
    { OV(119), 195 },
    { OV(130), 190 },
    { OV(142), 185 },
    { OV(155), 180 },
    { OV(170), 175 },
    { OV(186), 170 },
    { OV(204), 165 },
    { OV(223), 160 },
    { OV(244), 155 },
    { OV(267), 150 },
    { OV(291), 145 },
    { OV(318), 140 },
    { OV(347), 135 },
    { OV(377), 130 },
    { OV(409), 125 },
    { OV(443), 120 },
    { OV(478), 115 },
    { OV(514), 110 },
    { OV(552), 105 },
    { OV(589), 100 },
    { OV(627), 95 },
    { OV(664), 90 },
    { OV(701), 85 },
    { OV(736), 80 },
    { OV(769), 75 },
    { OV(801), 70 },
    { OV(830), 65 },
    { OV(857), 60 },
    { OV(882), 55 },
    { OV(904), 50 },
    { OV(923), 45 },
    { OV(940), 40 },
    { OV(955), 35 },
    { OV(967), 30 },
    { OV(978), 25 },
    { OV(987), 20 },
    { OV(995), 15 },
    { OV(1001), 10 },
    { OV(1006), 5 },
    { OV(1010), 0 } // safety
};
