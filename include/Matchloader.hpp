#pragma once
#include "api.h"

class Matchloader {
    private:
        pros::Motor m_big_motor; // 11W
        pros::ADIDigitalOut arm_piston; 
        int8_t direction = 1; 
        // std::vector<pros::Motor> motor_list {m_small_motor, m_big_motor}; 
        // pros::Motor_Group motors {motor_list}; 
        bool state = false; // true = on
        bool arm_state = false;
    public:
        Matchloader(int8_t big_motor_port, uint8_t piston_port  );
        void set_voltage(int32_t voltage);
        void toggle(); 
        void switch_polarity(); 
        void toggle_arm(); 
        int get_polarity(); 
        int get_state(); 
        void bang_set_voltage(int32_t voltage);
        double get_temp(); 
};