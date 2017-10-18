
#ifndef __FABTOTUM_CUSTOM_H
#define __FABTOTUM_CUSTOM_H

#include "buzzer.h"

extern Buzzer buzzer;

#include "Configuration.h"

extern void set_led_color(
    const uint8_t r, const uint8_t g, const uint8_t b
#if ENABLED(RGBW_LED)
    , const uint8_t w = 0
#endif
);

#define BUZZ(d,f) buzzer.tone(d, f)
#define cip(freq, dur, dly) do { \
      BUZZ(dur, freq/2); \
      BUZZ(dly, 0); \
} while (0)

#define LASER_SCAN_ON()  digitalWrite(LASER_GATE_PIN,LOW)
#define LASER_SCAN_OFF() digitalWrite(LASER_GATE_PIN,HIGH)
#define MILL_MOTOR_ON()  digitalWrite(MILL_MOTOR_ON_PIN,HIGH)
#define MILL_MOTOR_OFF() digitalWrite(MILL_MOTOR_ON_PIN,LOW)
#define PW_SERVO0_ON()  digitalWrite(NOT_SERVO0_ON_PIN,LOW)
#define PW_SERVO0_OFF() digitalWrite(NOT_SERVO0_ON_PIN,HIGH)
#define PW_SERVO1_ON()  digitalWrite(NOT_SERVO1_ON_PIN,LOW)
#define PW_SERVO1_OFF() digitalWrite(NOT_SERVO1_ON_PIN,HIGH)

#define MILLING_MOTOR_CCW -1
#define MILLING_MOTOR_BRAKE 0
#define MILLING_MOTOR_CW 1

#define SERVO_SPINDLE_MAX  1832    //(MILL MOTOR input: 1060 us equal to Full CCW, 1460us equal to zero, 1860us equal to Full CW)
#define SERVO_SPINDLE_MIN  1148
#define SERVO_SPINDLE_ZERO 1488
#define SERVO_SPINDLE_ARM  1550

#define RPM_SPINDLE_MAX  14500    // spindle max rpm
#define RPM_SPINDLE_MIN  0        // spindle min rpm


//#define RASPI_PWR_ON() WRITE(NOT_RASPI_PWR_ON_PIN,LOW)
//#define RASPI_PWR_OFF() WRITE(NOT_RASPI_PWR_ON_PIN,HIGH)
//#define LIGHT_SIG_ON() WRITE(LIGHT_SIGN_ON_PIN, HIGH)
//#define LIGHT_SIG_OFF() WRITE(LIGHT_SIGN_ON_PIN, LOW)

namespace FABtotum {
    enum motor_states {
        DISABLED,
        STOPPED,
        RUNNING_CW,
        RUNNING_CCW
    };

    static motor_states milling_motor_state = motor_states::DISABLED;

    void init();

    void milling_motor_set_speed(int8_t, uint16_t);
    void milling_motor_manage(int);

    void M60();
    void M61();
    void M62();
    
    void M450();

    void M700();    

    void M720();
    void M721();
    void M722();
    void M723();
    void M724();
    void M725();
    void M726();
    void M727();
    void M728();
    void M729();
//    void M730();
    void M741(); // M741 - read DOOR_OPEN sensor    
    void M744(); // M744 - read HOT_BED placed in place
    void M750(); // Read pressure sensor raw
    void M751(); // Read 24 Vdc bus
    void M752(); // Read 5 Vdc bus
    void M753(); // Read current sensor raw


    void M763();
    //void M793();    
}

class MachineManager {
/********** ATTRIBUTES **********/
public:
    enum machine_states {
        NOT_INIT,
        HYBRID,
        FFF,
        MILLING,
        ENGRAVING,
        SCANNING,
        SLS,
    };

private:
    const char* state_desc[7] PROGMEM = {
        "Not initialized",
        "Hybrid",
        "Fused Filament Fabrication",
        "Milling",
        "Laser engraving",
        "3D scanning",
        "Selective Laser Sintering"
    };

    machine_states current_state = machine_states::NOT_INIT;

/********** METHODS **********/
public:
    bool change_state(machine_states dst_state);

    machine_states get_current_state() {
        return current_state;
    }
    const char* get_state_description() {
        return state_desc[get_current_state()];
    }
    const char* get_state_description(machine_states state) {
        return state_desc[state];
    }

private:
    bool enter_state_milling(void);
    bool enter_state_engraving(void);

};

// STUB
class HeadManager {
};

#endif