#include "Cata.hpp"

Catapult::Catapult(int8_t small_motor, int8_t big_motor) :
    m_small_motor {small_motor},
    m_big_motor {big_motor}
    {};

void Catapult::set_voltage(int32_t voltage) {
    // max volt: 5.5W/ 2.5 A = 2.2 Volts = 2200 milivolts?? TODO: test
    m_small_motor.move_voltage(voltage /2); // max voltage will be half as much bc/ V = W/I (amps/watts), you half 
    m_big_motor.move_voltage(voltage);
}


// TODO: slip gear cycle + task