#pragma once
#include "api.h"

class Pneumatics {
    private:
        pros::ADIDigitalOut front_wing; 
        pros::ADIDigitalOut back_wing;
        pros::ADIDigitalOut hang_left_1; 
        pros::ADIDigitalOut hang_left_2; 
        pros::ADIDigitalOut hang_right_1; 
        pros::ADIDigitalOut hang_right_2; 

        bool back_wings_state = false; 
        bool front_wings_state = false; 
        bool hang_state = true;
    public:
        Pneumatics(uint8_t port_back, uint8_t port_front, uint8_t hang_port_L1, 
        uint8_t hang_port_L2, uint8_t hang_port_R1, uint8_t hang_port_R2);
        void toggle_back_wings();
        void toggle_front_wings(); 
        void toggle_hang(); 

        bool get_state_back_wings();
        bool get_state_front_wings(); 
        bool get_state_hang(); 
    
};