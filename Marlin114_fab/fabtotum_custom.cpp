/**
 * FABtotum custom code
 *
 *
 */

#include "pins_FABTOTUM.h"
#include "macros.h"
#include "servo.h"
#include "stepper.h"
#include "gcode.h"
#include "fabtotum_custom.h"

extern Servo servo[NUM_SERVOS];
extern int16_t fanSpeeds[FAN_COUNT];
MachineManager machine;

uint16_t val_a = 2000, val_b = 1000, val_c = 500;
int16_t milling_motor_current_speed = 0;

int FABIOs[][2] = {
    {NOT_SERVO0_ON_PIN     , OUTPUT},
    {NOT_SERVO1_ON_PIN     , OUTPUT},
    {MILL_MOTOR_ON_PIN     , OUTPUT}, //controlllare robe per M3,M4,M5
//    {RPI_RECOVERY_PIN      , OUTPUT},
    {LASER_GATE_PIN        , OUTPUT},
    {NOT_SECURE_SW_PIN     , INPUT},
    {NOT_REEL_LENS_OPEN_PIN, INPUT},
    {DOOR_OPEN_PIN         , INPUT},
    
    //{HEAD_LIGHT_PIN        , OUTPUT},//non presente in flat V2
//    {NOT_RASPI_PWR_ON_PIN  , OUTPUT},
    {WIRE_END_PIN          , INPUT},

    {analogInputToDigitalPin(MAIN_CURRENT_SENSE_PIN), INPUT},
    {analogInputToDigitalPin(MON_5V_PIN)            , INPUT},
    {analogInputToDigitalPin(MON_24V_PIN)           , INPUT},
    {analogInputToDigitalPin(PRESSURE_ANALOG_PIN)   , INPUT},
    // That's all, folks!
    {-1, -1}
};

bool MachineManager::enter_state_engraving() {
    servo[0].detach();

    //TCCR4A = 0b01000001;// COM1A1 COM1A0 COM1B1 COM1B0 COM1C1 COM1C0 WGM11 WGM10
    TCCR4A &= ~(_BV(COM4A1) | _BV(WGM41));
    TCCR4A |=  (_BV(COM4A0) | _BV(WGM40));

    //TCCR4B = 0b00001001;//ICNC1  ICES1     -   WGM13  WGM12   CS12  CS11  CS10
    TCCR4B &= ~(_BV(CS42)  | _BV(CS41));
    TCCR4B |=  (_BV(WGM42) | _BV(CS40));

    digitalWrite(SERVO0_PIN, 0);
    SERIAL_PROTOCOLLNPGM("Laser mode enabled");

    return true;
}

bool MachineManager::enter_state_milling() {
    return true;
}

bool MachineManager::change_state(machine_states dst_state)
{
    bool valid_state = false;

    switch (dst_state) {
        case machine_states::ENGRAVING:
            valid_state = enter_state_engraving();
            break;
        case machine_states::MILLING:
            valid_state = enter_state_milling();
            break;
    }

    if (valid_state) {
        set_led_color(245, 230, 220);
        cip(2200, 20, 250);
        cip(2200, 20, 0);
        current_state = dst_state;
    }

    return valid_state;
}


namespace FABtotum {

    static void io_init() {
        int i = 0;
        int* val = FABIOs[i];

        while (*val != -1) {
            pinMode(val[0], val[1]);
            val = FABIOs[++i];
        }
        
        // Init fastio Pin
        SET_OUTPUT(NOT_RASPI_PWR_ON_PIN);
        SET_OUTPUT(RPI_RECOVERY_PIN);
        digitalWrite(MILL_MOTOR_ON_PIN, LOW);
        
        LASER_SCAN_OFF();
        PW_SERVO0_OFF();
        PW_SERVO1_OFF();
        //LIGHT_SIG_ON();
    }

    void init() {
        cip(2200, 20, 0);
        set_led_color(255, 230, 0);
        io_init();
    }

    inline uint16_t milling_motor_rpm_to_servo(int16_t rpm)
    {
        float a = (float)(rpm+RPM_SPINDLE_MAX) / RPM_SPINDLE_MAX_BY_2;

        return (uint16_t)lroundf(a*SERVO_SPINDLE_INTERVAL) + SERVO_SPINDLE_MIN;
    }

    void milling_motor_enable()
    {
        Servo pilot = servo[0];

        PW_SERVO0_ON();
        MILL_MOTOR_ON();
        fanSpeeds[0] = 255;
        pilot.attach(0);
        pilot.write(SERVO_SPINDLE_ARM);
        _delay_ms(2000);
        pilot.write(milling_motor_rpm_to_servo(0));
        _delay_ms(1000);
    }

    void milling_motor_disable()
    {
        Servo pilot = servo[0];

        milling_motor_set_speed(MILLING_MOTOR_BRAKE, 0);
        milling_motor_state = motor_states::DISABLED;
        _delay_ms(500);
        MILL_MOTOR_OFF();
        PW_SERVO0_OFF();
        fanSpeeds[0] = 0;
        pilot.detach();
    }

    #define RAMP_STEPS 15
    #define RAMP_TIME 1000 // msecs 
    #define RAMP_STEPS_DELAY (RAMP_TIME/RAMP_STEPS)

    void milling_motor_ramp_to(int16_t rpm) {
        Servo pilot = servo[0];
        int16_t step = (rpm-milling_motor_current_speed)/RAMP_STEPS;

        for (int i = 0; i < RAMP_STEPS; i++) {
            milling_motor_current_speed += step;
            pilot.write(milling_motor_rpm_to_servo(milling_motor_current_speed));
            _delay_ms(RAMP_STEPS_DELAY);
        }
    }

    void milling_motor_set_speed(int8_t direction, uint16_t rpm=0)
    {
        NOLESS(rpm, RPM_SPINDLE_MIN);
        NOMORE(rpm, RPM_SPINDLE_MAX);

        Servo pilot = servo[0];

        switch (direction) {
            case MILLING_MOTOR_CW:
                milling_motor_ramp_to(rpm);
                milling_motor_state = motor_states::RUNNING_CW;
            break;

            case MILLING_MOTOR_CCW:
                milling_motor_ramp_to(-rpm);
                milling_motor_state = motor_states::RUNNING_CCW;
            break;
            
            case MILLING_MOTOR_BRAKE:
                pilot.write(milling_motor_rpm_to_servo(0));
                milling_motor_current_speed = 0;
                milling_motor_state = motor_states::STOPPED;
            break;
        }
    }

    void milling_motor_manage(int m_code)
    {
        uint16_t rpm = parser.seen('S') ? parser.value_ushort() : 0;

        if (machine.get_current_state() != MachineManager::machine_states::MILLING) {
            SERIAL_ERROR_START();
            SERIAL_ECHOPAIR("current state (", machine.get_state_description());
            SERIAL_ECHOLNPAIR(") disallows command M", m_code);
            return;
        }

        stepper.synchronize();

        switch (m_code) {
            case 3:
                if (milling_motor_state == motor_states::DISABLED) {
                    milling_motor_enable();
                }
                else if (milling_motor_state == motor_states::RUNNING_CCW) {
                    milling_motor_set_speed(MILLING_MOTOR_BRAKE, 0);
                    _delay_ms(1000);
                }
                milling_motor_set_speed(MILLING_MOTOR_CW, rpm);
            break;

            case 4:
                if (milling_motor_state == motor_states::DISABLED) {
                    milling_motor_enable();
                }
                else if (milling_motor_state == motor_states::RUNNING_CW) {
                    milling_motor_set_speed(MILLING_MOTOR_BRAKE, 0);
                    _delay_ms(1000);
                }
                milling_motor_set_speed(MILLING_MOTOR_CCW, rpm);
            break;

            case 5:
                milling_motor_disable();
            break;
        }
    }
 
    void M1000() {
        val_a = parser.seen('A') ? parser.value_ushort() : val_a;
        val_b = parser.seen('B') ? parser.value_ushort() : val_b;
        val_c = parser.seen('C') ? parser.value_ushort() : val_c;
        SERIAL_ECHOPAIR("A:", val_a);
        SERIAL_ECHOPAIR(" B:", val_b);
        SERIAL_ECHOLNPAIR(" C:", val_c);
    }
 
    void M60() {
         servo[0].detach();
    }

    void M61() {
        stepper.synchronize();
        if (parser.seenval('S'))
            analogWrite(SERVO0_PIN, parser.value_int());
        else
            digitalWrite(SERVO0_PIN, 255 );
    }   
    
    void M62() {
        stepper.synchronize();
        digitalWrite(SERVO0_PIN, 0 );
    }   

     void M450() {
        if (parser.seen('S')) {
            int machine_mode = parser.value_int();
            machine.change_state(machine_mode);
        }
        else {
            // Report current state
            SERIAL_ECHO_START();
            SERIAL_ECHOPAIR("Machine mode: ", machine.get_current_state());
            SERIAL_ECHOLNPAIR(" ", machine.get_state_description());
        }
  }
 
   void M700() {
       //if (code_seen('S')) analogWrite(LASER_GATE_PIN,255-(code_value_int()));
        if (parser.seenval('S'))
            analogWrite(LASER_GATE_PIN, 255-(parser.value_int()));
        else 
            LASER_SCAN_OFF();
   }
    
    void M720() {
        MILL_MOTOR_ON();
    }
    
    void M721() {
        MILL_MOTOR_OFF();
    }
    void M722() {
        PW_SERVO0_ON();
    }
    
    void M723() {
        PW_SERVO0_OFF();
    }

    void M724() {
        PW_SERVO1_ON();
    }
    
    void M725() {
        PW_SERVO1_OFF();
    }
    
    void M726() {
//        RASPI_PWR_ON();
    }
//    
    void M727() {
//        RASPI_PWR_OFF();
    }
    
    
    
    // RASPI ALIVE
    void M728() {
        cip(1780, 50, 50);
        cip(1780, 50, 50);
        cip(1780, 50, 80);
        cip(2200, 100, 100);
    }

    void M729() {
        cip(2200, 100, 100);
        cip(1780, 50, 50);        
    }
    
//    void M730() {
//        if (code_seen('S')) {
//            if (code_value_int() == 0)
//                LIGHT_SIG_OFF();
//            else
//                LIGHT_SIG_ON();
//        }
//    }

    void M741() { // M741 - read DOOR_OPEN sensor
        if (digitalRead(DOOR_OPEN_PIN))
            SERIAL_PROTOCOLLNPGM("TRIGGERED");
        else 
            SERIAL_PROTOCOLLNPGM("open");
    }

    
    void M744() { // M744 - read HOT_BED placed in place
        if(thermalManager.degBed()>0)
        {SERIAL_PROTOCOLLNPGM("TRIGGERED");}
        else
        {SERIAL_PROTOCOLLNPGM("open");}
        
    }
    void M750() {
        unsigned long VAL = analogRead(PRESSURE_ANALOG_PIN);
        SERIAL_ECHOLNPAIR("Pressure raw =", (VAL*4887/10000));
    }

    void M751() {
        unsigned long VAL = analogRead(MON_24V_PIN);
        SERIAL_ECHOLNPAIR("24 Vdc bus is = ", (VAL*5213/10000));
    }
    void M752() {
        unsigned long VAL = analogRead(MON_5V_PIN);
        SERIAL_ECHOLNPAIR("5 Vdc bus is = ", (VAL*9775/100000));
    }
    void M753() {
        unsigned long VAL = analogRead(MAIN_CURRENT_SENSE_PIN);
        SERIAL_ECHOLNPAIR("Current raw =", (VAL*4887/10000));
    }

    
    // FAB-UI settings tweak
    void M763() {
        SERIAL_ECHOLNPGM("5");
    }

    // Set/read installed head soft ID
#pragma warning(da implementare)
    /*
    void M793() {
        const bool seen_S = parser.seen('S');
            if (seen_S) installed_head = parser.value_int();
        
            else if (!seen_S) {
            // Report current state
            SERIAL_ECHOLNPAIR("Installed Head =", installed_head);
            }
    }
    */
    
}
