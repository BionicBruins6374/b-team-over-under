#include "Climb.hpp"


Climb::Climb(int8_t big_motor, int8_t small_motor, uint8_t rotational_port) :
    m_big_motor {big_motor},
    m_small_motor {small_motor},
    pot {rotational_port}
    {};

void Climb::set_voltage(int32_t voltage) {
    m_big_motor.move_voltage(voltage);
    m_small_motor.move_velocity(voltage);
}

// setter; changes state of climb 
void Climb::toggle() {
    state = !state;
}


void Climb::switch_polarity() {
    direction *= -1; 
}

double Climb::get_temp() {
    return m_big_motor.get_temperature(); 
}

int Climb::get_polarity() {
    return direction; 
}

int Climb::get_state() {
   return state;  
}

void Climb::bang_set_voltage(int32_t voltage) {
    // if the magnitude of the voltage is greater than the expected voltage (inputted)
    if (std::abs(m_big_motor.get_voltage()) > std::abs(voltage) && std::abs(m_small_motor.get_voltage()) > std::abs(voltage) ) {
        // set the voltage to 0 
        
        m_big_motor.move_voltage(0); 
        m_small_motor.move_voltage(0);

    
    }
    // if the magnitude of the voltage is less than the expected voltage (inputted)
    else if (std::abs(m_big_motor.get_voltage()) <= std::abs(voltage) && std::abs(m_small_motor.get_voltage()) <= std::abs(voltage)) {
        // reset assert voltage to expected voltage
        m_big_motor.move_voltage(voltage); 
        m_small_motor.move_voltage(voltage);
    }
}

void Climb::set_speed(int32_t speed_inp) {
    speed = speed_inp;
}

int32_t Climb::get_speed() {
    return speed; 

}

void Climb::set_state (bool state_input){
    state = state_input;
}


void Climb::move_position(int position) {
    m_big_motor.move_absolute(position, 127);
    m_small_motor.move_absolute(position, 127);
    
}

void Climb::move_rel(int position) {
    m_big_motor.move_relative(position, 127);
    m_small_motor.move_relative(position, 127);
}

int Climb::get_pos() {
    return m_big_motor.get_position(); 
}