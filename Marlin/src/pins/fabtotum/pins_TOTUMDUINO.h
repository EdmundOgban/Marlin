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
 * Arduino Mega with RAMPS v1.4 (or v1.3) pin assignments
 *
 * Applies to the following boards:
 *
 *  RAMPS_14_EFB (Hotend, Fan, Bed)
 *  RAMPS_14_EEB (Hotend0, Hotend1, Bed)
 *  RAMPS_14_EFF (Hotend, Fan0, Fan1)
 *  RAMPS_14_EEF (Hotend0, Hotend1, Fan)
 *  RAMPS_14_SF  (Spindle, Controller Fan)
 *
 *  RAMPS_13_EFB (Hotend, Fan, Bed)
 *  RAMPS_13_EEB (Hotend0, Hotend1, Bed)
 *  RAMPS_13_EFF (Hotend, Fan0, Fan1)
 *  RAMPS_13_EEF (Hotend0, Hotend1, Fan)
 *  RAMPS_13_SF  (Spindle, Controller Fan)
 *
 *  Other pins_MYBOARD.h files may override these defaults
 *
 *  Differences between
 *  RAMPS_13 | RAMPS_14
 *         7 | 11
 */

#ifdef TARGET_LPC1768
  #error "Oops! Set MOTHERBOARD to an LPC1768-based board when building for LPC1768."
#elif defined(__STM32F1__)
  #error "Oops! Set MOTHERBOARD to an STM32F1-based board when building for STM32F1."
#endif

#if NOT_TARGET(IS_RAMPS_SMART, IS_RAMPS_DUO, IS_RAMPS4DUE, TARGET_LPC1768, __AVR_ATmega1280__, __AVR_ATmega2560__)
  #error "Oops! Select 'Arduino/Genuino Mega or Mega 2560' in 'Tools > Board.'"
#endif

// Custom flags and defines for the build
//#define BOARD_CUSTOM_BUILD_FLAGS -D__FOO__

#ifndef BOARD_INFO_NAME
  #define BOARD_INFO_NAME "Totumduino"
#endif

//
// Servos
//
#ifndef SERVO0_PIN
  #define SERVO0_PIN                          11
#endif
#ifndef SERVO1_PIN
  #define SERVO1_PIN                           6
#endif
// #ifndef SERVO2_PIN
//   #define SERVO2_PIN                           5
// #endif
// #ifndef SERVO3_PIN
//   #define SERVO3_PIN                           4
// #endif

//
// Limit Switches
//
#ifndef X_STOP_PIN
  #ifndef X_MIN_PIN
    #define X_MIN_PIN                          2
  #endif
  #ifndef X_MAX_PIN
    #define X_MAX_PIN                          3
  #endif
#endif
#ifndef Y_STOP_PIN
  #ifndef Y_MIN_PIN
    #define Y_MIN_PIN                         14
  #endif
  #ifndef Y_MAX_PIN
    #define Y_MAX_PIN                         15
  #endif
#endif
#ifndef Z_STOP_PIN
  #ifndef Z_MIN_PIN
    #define Z_MIN_PIN                         19
  #endif
  #ifndef Z_MAX_PIN
    #define Z_MAX_PIN                         18
  #endif
#endif

//
// Z Probe (when not Z_MIN_PIN)
//
// #ifndef Z_MIN_PROBE_PIN
//   #define Z_MIN_PROBE_PIN                     32
// #endif

//
// Steppers
//
#define X_STEP_PIN                            60
#define X_DIR_PIN                             61
#define X_ENABLE_PIN                          56
// #ifndef X_CS_PIN
//   #define X_CS_PIN                            53
// #endif

#define Y_STEP_PIN                            54
#define Y_DIR_PIN                             55
#define Y_ENABLE_PIN                          38
// #ifndef Y_CS_PIN
//   #define Y_CS_PIN                            49
// #endif

#ifndef Z_STEP_PIN
  #define Z_STEP_PIN                          46
#endif
#define Z_DIR_PIN                             48
#define Z_ENABLE_PIN                          62
// #ifndef Z_CS_PIN
//   #define Z_CS_PIN                            40
// #endif

// Printing PRO Feeder
// #define E0_STEP_PIN                           21
// #define E0_DIR_PIN                            20
// #define E0_ENABLE_PIN                         23
// #ifndef E0_CS_PIN
//   #define E0_CS_PIN                           42
// #endif

// Built-in Feeder
#define E0_STEP_PIN                           26
#define E0_DIR_PIN                            28
#define E0_ENABLE_PIN                         24
// #ifndef E1_CS_PIN
//   #define E1_CS_PIN                           44
// #endif

//
// Temperature Sensors
//
#ifndef TEMP_0_PIN
  #define TEMP_0_PIN                          13  // Analog Input
#endif
// #ifndef TEMP_1_PIN
//   #define TEMP_1_PIN                          15  // Analog Input
// #endif
#ifndef TEMP_BED_PIN
  #define TEMP_BED_PIN                        14  // Analog Input
#endif

//
// SPI for Max6675 or Max31855 Thermocouple
//
// #ifndef MAX6675_SS_PIN
//   #define MAX6675_SS_PIN                      66  // Don't use 53 if using Display/SD card (SDSS) or 49 (SD_DETECT_PIN)
// #endif


//
// Heaters / Fans

#define HEATER_0_PIN                          10
#define HEATER_BED_PIN                         8
#define FAN_PIN                                9


//
// Misc. Functions
//

#define BEEPER_PIN                             4
#define	RED_PIN	        	                     5
#define	GREEN_PIN	      	                     7
#define	BLUE_PIN	   	        	              12
#define	CASE_LIGHT_PIN                	      83


// #define SDSS                                  53
// #define LED_PIN                               13

// #ifndef FILWIDTH_PIN
//   #define FILWIDTH_PIN                         5  // Analog Input on AUX2
// #endif

// RAMPS 1.4 DIO 4 on the servos connector
// #ifndef FIL_RUNOUT_PIN
//   #define FIL_RUNOUT_PIN                       4
// #endif

// #ifndef PS_ON_PIN
//   #define PS_ON_PIN                           12
// #endif

// #if ENABLED(CASE_LIGHT_ENABLE) && !defined(CASE_LIGHT_PIN) && !defined(SPINDLE_LASER_ENA_PIN)
//   #if NUM_SERVOS <= 1                             // Prefer the servo connector
//     #define CASE_LIGHT_PIN                     6  // Hardware PWM
//   #elif HAS_FREE_AUX2_PINS
//     #define CASE_LIGHT_PIN                    44  // Hardware PWM
//   #endif
// #endif


/* From old FABlin pins.h - should be implemented at some point
//fastio define
#define WIRE_END_PIN            78
#define NOT_RASPI_PWR_ON_PIN	  85
#define	NOT_SECURE_SW_PIN	      71
#define	NOT_REEL_LENS_OPEN_PIN	70
#define	LIGHT_SIGN_ON_PIN	      83
#define	RPI_RECOVERY_PIN	      79

//power_off_pins
#define	PWR_IN_PIN	            50
#define PWR_OUT_PIN	            51

//additional IO

#define	HOT_LED_PIN	  	        53
#define STAT_LED_RED  	        53
#define	DOOR_OPEN_PIN	          49
#define	HEAD_LIGHT_PIN	        45
#define	LASER_GATE_PIN	        44
//#define	SCL	                  21
//#define	SDA	                  20
#define	MILL_MOTOR_ON_PIN	      41
#define NOT_SERVO1_ON_PIN       23
#define	NOT_SERVO2_ON_PIN		    25

//additional analog
#define MAIN_CURRENT_SENSE_PIN	12 // ANALOG NUMBERING
#define	MON_5V_PIN	            10 // ANALOG NUMBERING
#define	MON_24V_PIN	             9 // ANALOG NUMBERING
#define	PRESSURE_ANALOG_PIN	     3	 // ANALOG NUMBERING


//servo
#define SERVO0_PIN              11
#define SERVO1_PIN               6 -> inserito come autofan estrusore 0

// Default pins for additional serial ports (may be reconfigured at run-time)
#define RX4                     67
#define TX4                     11
*/



//
// M3/M4/M5 - Spindle/Laser Control
//
#if HAS_CUTTER && !defined(SPINDLE_LASER_ENA_PIN)
  #if !NUM_SERVOS                                 // Use servo connector if possible
    #define SPINDLE_LASER_ENA_PIN              4  // Pullup or pulldown!
    #define SPINDLE_LASER_PWM_PIN              6  // Hardware PWM
    #define SPINDLE_DIR_PIN                    5
  #elif HAS_FREE_AUX2_PINS
    #define SPINDLE_LASER_ENA_PIN             40  // Pullup or pulldown!
    #define SPINDLE_LASER_PWM_PIN             44  // Hardware PWM
    #define SPINDLE_DIR_PIN                   65
  #else
    #error "No auto-assignable Spindle/Laser pins available."
  #endif
#endif
