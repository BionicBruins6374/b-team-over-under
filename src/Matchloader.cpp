#include "Matchloader.hpp"
#include "constants.hpp"

Matchloader::Matchloader(int8_t big_motor, uint8_t piston_port) :
    m_big_motor {big_motor}, 
    arm_piston {piston_port}
    //   motors ({m_small_motor, m_big_motor})
    {};



void Matchloader::set_voltage(int32_t voltage) {
    // max volt: 5.5W/ 2.5 A = 2.2 Volts = 2200 milivolts?? TODO: test
   
//    m_small_motor.move_voltage(voltage); // max voltage will be half as much bc/ V = W/I (amps/watts), you half 
   m_big_motor.move_voltage(voltage);
}

void Matchloader::toggle() {
    state = !state;
//     if (state) {
//         set_voltage(constants::HIGH_VOLTAGE_CATA);
//     }
//     else {
//         set_voltage(0);
//     }
}

// TODO: slip gear cycle + task


void Matchloader::toggle_arm() {
    arm_state != arm_state;
    arm_piston.set_value(arm_state); 
}

void Matchloader::switch_polarity() {
    direction *= -1; 
}

double Matchloader::get_temp() {
    return m_big_motor.get_temperature(); 
}

int Matchloader::get_polarity() {
    return direction; 
}

int Matchloader::get_state() {
   return state;  
}

void Matchloader::bang_set_voltage(int32_t voltage) {
    if (std::abs(m_big_motor.get_voltage()) > std::abs(voltage) ) {
        m_big_motor.move_voltage(0); 
    }
    else if (std::abs(m_big_motor.get_voltage()) <= std::abs(voltage)) {
        m_big_motor.move_voltage(voltage); 
    }
}