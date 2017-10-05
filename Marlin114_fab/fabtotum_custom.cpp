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
MachineManager machine;

int machine_mode = 1; // INIT HYBRID MODE
int installed_head = 0; // INIT NO HEAD

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

bool MachineManager::change_state(machine_states dst_state)
{    
    if (dst_state == machine_states::ENGRAVING) { // LASER MODE
        servo[0].detach();

        //TCCR4A = 0b01000001;// COM1A1 COM1A0 COM1B1 COM1B0 COM1C1 COM1C0 WGM11 WGM10
        TCCR4A &= ~(_BV(COM1A1) | _BV(WGM11));
        TCCR4A |= ~(_BV(COM1A0) | _BV(WGM10));

        //TCCR4B = 0b00001001;//ICNC1  ICES1     -   WGM13  WGM12   CS12  CS11  CS10
        TCCR4B &= ~(_BV(CS12) | _BV(CS11));
        TCCR4B |= _BV(CS10);

        digitalWrite(SERVO0_PIN, 0);
        digitalWrite(BEEPER_PIN, 0);
        _delay_ms(150);
        digitalWrite(BEEPER_PIN, 1);
        SERIAL_PROTOCOLLNPGM("Laser mode enabled");
    }

    current_state = dst_state;
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
        io_init();
        set_led_color(0, 255, 255);
    }

   void M60() {
        servo[0].detach();
        
   }   


    void M61() {
        stepper.synchronize();
        if (parser.seenval('S')) analogWrite(SERVO0_PIN, parser.value_int());
        else
            digitalWrite(SERVO0_PIN, 255 );
   }   
    
    void M62() {
            stepper.synchronize();
            digitalWrite(SERVO0_PIN, 0 );
   }   

 

    void M450() {
        if (parser.seen('S')) {
            machine_mode = parser.value_int();
            machine.change_state(machine_mode);
        }
        else {
            // Report current state
            SERIAL_ECHO_START();
            SERIAL_ECHOLNPAIR("Machine mode =",
                machine.state_desc[machine.get_current_state()]);
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
        #define cip(freq, dur, dly) do { \
              BUZZ(dur, freq/2); \
              BUZZ(dly, 0); \
        } while (0)

        cip(1780, 50, 50);
        cip(1780, 50, 50);
        cip(1780, 50, 80);
        cip(2200, 100, 100);
        
    }

    void M729() {
        #define cip(freq, dur, dly) do { \
              BUZZ(dur, freq/2); \
              BUZZ(dly, 0); \
        } while (0)

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
    void M793() {
        const bool seen_S = parser.seen('S');
            if (seen_S) installed_head = parser.value_int();
        
            else if (!seen_S) {
            // Report current state
            SERIAL_ECHOLNPAIR("Installed Head =", installed_head);
            }
    }

    
}
