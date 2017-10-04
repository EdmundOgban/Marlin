/****************************************************************************************
* FABtotum Controller pin assignment
*
****************************************************************************************/

//////////////////FIX THIS//////////////
#ifndef __AVR_ATmega1280__
 #ifndef __AVR_ATmega2560__
 #error Oops!  Make sure you have 'Arduino Mega (ATmega1280)' selected from the 'Tools -> Boards' menu.
 #endif
#endif

#define BOARD_NAME "Fabtotum"

#define LARGE_FLASH true

#define Y_STEP_PIN         54
#define Y_DIR_PIN          55
#define Y_ENABLE_PIN       38
#define Y_MIN_PIN          14//15
#define Y_MAX_PIN          15//14

#define X_STEP_PIN         60
#define X_DIR_PIN          61
#define X_ENABLE_PIN       56
#define X_MIN_PIN          2//3
#define X_MAX_PIN          3//2

#define Z_STEP_PIN         46
#define Z_DIR_PIN          48
#define Z_ENABLE_PIN       62
#define Z_MIN_PIN          19//18
#define Z_MAX_PIN          18//19

//#define Y2_STEP_PIN        36
//#define Y2_DIR_PIN         34
//#define Y2_ENABLE_PIN      30

//#define Z2_STEP_PIN        36
//#define Z2_DIR_PIN         34
//#define Z2_ENABLE_PIN      30

#define E0_STEP_PIN        26
#define E0_DIR_PIN         28
#define E0_ENABLE_PIN      24

#define E1_STEP_PIN        36
#define E1_DIR_PIN         34
#define E1_ENABLE_PIN      30

#define E2_STEP_PIN        21
#define E2_DIR_PIN         20
#define E2_ENABLE_PIN      23



#define LED_PIN            13

#define BEEPER_PIN         4

#define HEATER_0_PIN       10   
#define HEATER_1_PIN       22
#define HEATER_2_PIN       22
#define HEATER_BED_PIN      8
#define FAN_PIN             9

#define TEMP_0_PIN         13   // ANALOG NUMBERING
#define TEMP_BED_PIN       14   // ANALOG NUMBERING
#define TEMP_1_PIN         15   // ANALOG NUMBERING
#define TEMP_2_PIN         13   // ANALOG NUMBERING


//fastio define
#define WIRE_END_PIN	          78 //avable only in fastio
#define NOT_RASPI_PWR_ON_PIN	  85 //avable only in fastio
#define	NOT_SECURE_SW_PIN	      71 //avable only in fastio
#define	NOT_REEL_LENS_OPEN_PIN	  70 //avable only in fastio
#define	LIGHT_SIGN_ON_PIN	      83 //avable only in fastio
#define	RPI_RECOVERY_PIN	      79 //avable only in fastio

//additional IO
#define	RED_PIN	            5
#define	GREEN_PIN	        7
#define	BLUE_PIN	        12
//#define	HOT_LED_PIN	        53 //non usato da marlin
#define STAT_LED_RED_PIN    53
#define	DOOR_OPEN_PIN	    49
#define	HEAD_LIGHT_PIN	    45
#define	LASER_GATE_PIN	    44
//#define	SCL	21
//#define	SDA	20
#define	MILL_MOTOR_ON_PIN	41
#define NOT_SERVO0_ON_PIN   23
#define	NOT_SERVO1_ON_PIN	25

//additional analog
#define MAIN_CURRENT_SENSE_PIN	12 // ANALOG NUMBERING (+54 PER DIGITAL) 
#define	MON_5V_PIN	            10 // ANALOG NUMBERING (+54 PER DIGITAL)
#define	MON_24V_PIN	            9  // ANALOG NUMBERING (+54 PER DIGITAL)
//#define	PRESSURE_ANALOG_PIN	    3  // ANALOG NUMBERING (+54 PER DIGITAL)
#define Z_MIN_PROBE_PIN         57 // pressure analog pin


//servo
#define SERVO0_PIN         11
#define SERVO1_PIN         6

 
