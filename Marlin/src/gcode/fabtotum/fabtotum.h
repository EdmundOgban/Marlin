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
 * fabtotum.h - Include file for FABtotum's custom GCode and machinery
 *
 */


#include "../../MarlinCore.h"
#include "../../module/temperature.h"
#include "../../libs/buzzer.h"

#define FABTOTUM_SERIAL_CODE 0
#define FABTOTUM_CONTROL_SERIAL_CODE 0
#define FABTOTUM_CONTROL_BATCH_NUMBER 0

namespace FABtotum {
    void M300();
    void M701();
    void M702();
    void M703();
    void M728();
    void M735();
    void M744();
    void M762();
    void M763();
    
    // read FABtotum Personal Fabricator Main Controller serial ID
    inline void M760() { SERIAL_PRINT(FABTOTUM_SERIAL_CODE, DEC); }
    // read FABtotum Personal Fabricator Main Controller control code of serial ID
    inline void M761() { SERIAL_PRINT(FABTOTUM_CONTROL_SERIAL_CODE, DEC); }
    // read FABtotum Personal Fabricator Main Controller control code of production batch number
    inline void M764() { SERIAL_PRINT(FABTOTUM_CONTROL_BATCH_NUMBER, DEC); }
    // read FABtotum Personal Fabricator Firmware Version
    inline void M765() { SERIAL_ECHOLNPGM(SHORT_BUILD_VERSION); }
    // read FABtotum Personal Fabricator Firmware Build Date and Time
    inline void M766() { SERIAL_ECHOLNPAIR(__DATE__, " " __TIME__); }
    // read FABtotum Personal Fabricator Firmware Update Author
    inline void M767() { SERIAL_ECHOLNPGM(STRING_CONFIG_H_AUTHOR); }
}

