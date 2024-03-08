#pragma once
#include "api.h"

class Climb {
    private:
        pros::Motor m_big_motor; // 11W
        pros::Motor m_small_motor; //5.5W

        int8_t direction = 1; 
        bool state = false; // true = on
        bool arm_state = false;
        int32_t speed = 0; 
    public:
        pros::ADIAnalogIn pot;

        Climb(int8_t big_motor_port, int8_t small_motor_port, uint8_t rotational_port);
        void set_voltage(int32_t voltage);
        void toggle(); 
        void switch_polarity(); 
        int get_polarity(); 
        int get_state(); 
        void bang_set_voltage(int32_t voltage);
        double get_temp(); 

        void set_speed(int32_t speed); 
        int32_t get_speed(); 
        void set_state(bool state);

        void move_position(int pos);
        void move_rel(int post);
        int get_pos();  

        
};