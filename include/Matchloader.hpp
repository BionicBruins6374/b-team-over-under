#pragma once
#include "api.h"

class Matchloader {
    private:
        pros::Motor m_big_motor; // 11W
        pros::Motor m_small_motor; 
        int8_t direction = 1; 
        // std::vector<pros::Motor> motor_list {m_small_motor, m_big_motor}; 
        // pros::Motor_Group motors {motor_list}; 
        bool state = false; // true = on
        bool arm_state = false;
        int32_t speed = 0; 
    public:
        Matchloader(int8_t big_motor_port, int8_t small_motor_port);
        void set_voltage(int32_t voltage);
        void toggle(); 
        void switch_polarity(); 
        void toggle_arm(); 
        int get_polarity(); 
        int get_state(); 
        void bang_set_voltage(int32_t voltage);
        double get_temp(); 

        void set_speed(int32_t speed); 
        int32_t get_speed(); 
        void set_state(bool state);

        void move_position(int pos);

        
};