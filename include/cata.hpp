#pragma once
#include "api.h"

class Catapult {
    private:
        pros::Motor m_small_motor; //5.5W
        pros::Motor m_big_motor; // 11W
    public:
        Catapult( int8_t small_motor_port, int8_t big_motor_port );
        void set_voltage(int32_t voltage);
    
        

};