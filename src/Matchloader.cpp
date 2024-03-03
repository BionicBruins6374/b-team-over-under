#include "Matchloader.hpp"
#include "constants.hpp"

Matchloader::Matchloader(int8_t big_motor, int8_t small_motor) :
    m_big_motor {big_motor},
    m_small_motor {small_motor}

    {};

void Matchloader::set_voltage(int32_t voltage) {
    m_big_motor.move_voltage(voltage);
    m_small_motor.move_voltage(voltage);
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

void Matchloader::set_speed(int32_t speed_inp) {
    speed = speed_inp;
}

int32_t Matchloader::get_speed() {
    return speed; 

}

void Matchloader::set_state (bool state_input){
    state = state_input;
}


void Matchloader::move_position(int position) {
    m_big_motor.move_absolute(position, 127);
    m_small_motor.move_absolute(position, 127);
    
}

void Matchloader::move_rel(int position) {
    m_big_motor.move_relative(position, 127);
    m_small_motor.move_relative(position, 127);
}

int Matchloader::get_pos() {
    return m_big_motor.get_position(); 
}