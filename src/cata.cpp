#include "Cata.hpp"
#include "constants.hpp"

Catapult::Catapult(int8_t small_motor, int8_t big_motor) :
    m_small_motor {small_motor},
    m_big_motor {big_motor}
    //   motors ({m_small_motor, m_big_motor})
    {};



void Catapult::set_voltage(int32_t voltage) {
    // max volt: 5.5W/ 2.5 A = 2.2 Volts = 2200 milivolts?? TODO: test
   
//    m_small_motor.move_voltage(voltage); // max voltage will be half as much bc/ V = W/I (amps/watts), you half 
   m_big_motor.move_voltage(voltage);
}

void Catapult::toggle() {
    state = !state;
    if (state) {
        set_voltage(constants::HIGH_VOLTAGE_CATA);
    }
    else {
        set_voltage(0);
    }
}

// TODO: slip gear cycle + task