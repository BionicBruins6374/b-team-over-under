#include "Matchloader.hpp"
#include "constants.hpp"

Matchloader::Matchloader(int8_t big_motor, int8_t small_motor) :
    m_big_motor {big_motor, pros::E_MOTOR_GEAR_BLUE},
    m_small_motor {small_motor, pros::E_MOTOR_GEAR_BLUE}

    {};

void Matchloader::set_voltage(int32_t voltage) {
    m_big_motor.move_voltage(voltage);
    m_small_motor.move_velocity(voltage);
}

// setter; changes state of matchloader 
void Matchloader::toggle() {
    state = !state;
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
    // if the magnitude of the voltage is greater than the expected voltage (inputted)
    if (std::abs(m_big_motor.get_voltage()) > std::abs(voltage) ) {
        // set the voltage to 0 
        m_big_motor.move_voltage(0); 
    }
    // if the magnitude of the voltage is less than the expected voltage (inputted)
    else if (std::abs(m_big_motor.get_voltage()) <= std::abs(voltage)) {
        // reset assert voltage to expected voltage
        m_big_motor.move_voltage(voltage); 
    }
}

