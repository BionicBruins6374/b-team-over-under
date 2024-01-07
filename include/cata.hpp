#pragma once
#include "api.h"

class Catapult {
    private:
        pros::Motor m_small_motor; //5.5W
        pros::Motor m_big_motor; // 11W
        // std::vector<pros::Motor> motor_list {m_small_motor, m_big_motor}; 
        // pros::Motor_Group motors {motor_list}; 
        bool state = false; // true = on
    public:
        Catapult( int8_t small_motor_port, int8_t big_motor_port );
        void set_voltage(int32_t voltage);
        void toggle(); 
};