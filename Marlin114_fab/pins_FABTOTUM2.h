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

#define BOARD_NAME "Fabtotum2"

#define LARGE_FLASH true

#define X_STEP_PIN         25
#define X_DIR_PIN          26
#define X_ENABLE_PIN       27
#define X_MIN_PIN          63
#define X_MAX_PIN          62

#define Y_STEP_PIN         22
#define Y_DIR_PIN          23
#define Y_ENABLE_PIN       24
#define Y_MIN_PIN          65
#define Y_MAX_PIN          64

#define Z_STEP_PIN         28
#define Z_DIR_PIN          29
#define Z_ENABLE_PIN       37
#define Z_MIN_PIN          67
#define Z_MAX_PIN          66

#define Y2_STEP_PIN        -1//36
#define Y2_DIR_PIN         -1//34
#define Y2_ENABLE_PIN      -1//30

#define Z2_STEP_PIN        -1//36
#define Z2_DIR_PIN         -1//34
#define Z2_ENABLE_PIN      -1//30

// interno 1:10 16 uStep
#define E0_STEP_PIN        36
#define E0_DIR_PIN         35
#define E0_ENABLE_PIN      34

// 5# asse 1:20 16 uStep
#define E1_STEP_PIN        33
#define E1_DIR_PIN         32
#define E1_ENABLE_PIN      31

// testa pro 1:20 4 uStep
#define E2_STEP_PIN        33//21 SCL
#define E2_DIR_PIN         32//20 SDA
#define E2_ENABLE_PIN      31//49 NOT_SERVO1_ON_PIN


#define LED_PIN            42 //green on board

#define BEEPER_PIN         9

#define HEATER_0_PIN       5   
#define HEATER_1_PIN       3 //empty pin
#define HEATER_2_PIN       3
#define HEATER_BED_PIN     2 
#define FAN_PIN            4 

#define TEMP_0_PIN         0 // ANALOG NUMBERING
#define TEMP_BED_PIN       1 // ANALOG NUMBERING
#define TEMP_1_PIN         2 // ANALOG NUMBERING
#define TEMP_2_PIN         2 // ANALOG NUMBERING

#define PS_ON_PIN          80
#define PS_ON_AWAKE        -1

// special pins
#define	RED_PIN	          46
#define	GREEN_PIN	      45
#define	BLUE_PIN	      44
#define	HOT_LED_PIN	      43 // sostituito da STAT_LED_RED
#define CASE_LIGHT_PIN    53


//servo
#define SERVO0_PIN         6
#define SERVO1_PIN         7
#define Z_MIN_PROBE_PIN     67

// milling & laser
#define	MILL_MOTOR_ON_PIN   47

// MARLIN PINS
#define SPINDLE_LASER_ENABLE_PIN    47
//#define SPINDLE_DIR_PIN           -1
#define SPINDLE_LASER_PWM_PIN       6
#define FAN1_PIN                10 //controller fan
#define STAT_LED_RED_PIN        -1      //fabtotum HOT_LED_PIN
#define STAT_LED_BLUE_PIN   HOT_LED_PIN //fabtotum HOT_LED_PIN


// Fabtotum special pins
// not initialized by marlin

#define NOT_SERVO0_ON_PIN       49 //libero
#define	NOT_SERVO1_ON_PIN	    48 //sonda

#define WIRE_END_PIN	          68
#define NOT_RASPI_PWR_ON_PIN	  80//fastio
#define	NOT_SECURE_SW_PIN	      69
#define	NOT_REEL_LENS_OPEN_PIN    15
#define	RPI_RECOVERY_PIN	      79//fastio

//additional IO
#define	DOOR_OPEN_PIN	  14
//#define	HEAD_LIGHT_PIN	  10 non presente in flat V2
#define	LASER_GATE_PIN	  8

//additional analog
#define MAIN_CURRENT_SENSE_PIN	3 // ANALOG NUMBERING (+54 PER DIGITAL) 
#define	MON_5V_PIN	            4 // ANALOG NUMBERING (+54 PER DIGITAL)
#define	MON_24V_PIN	            5  // ANALOG NUMBERING (+54 PER DIGITAL)
#define	PRESSURE_ANALOG_PIN	    6  // ANALOG NUMBERING (+54 PER DIGITAL)




//Smart Head
//#define   HEAD_TX 18//uart1
//#define   HEAD_RX 19//uart1
//#define	SCL     21
//#define	SDA     20