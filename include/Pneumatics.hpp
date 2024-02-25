#pragma once
#include "api.h"

class Pneumatics {
    private:
        pros::ADIDigitalOut front_wing; 
        pros::ADIDigitalOut back_wing;
        pros::ADIDigitalOut hang_left_1; 
    
        bool back_wings_state = false; 
        bool front_wings_state = false; 
        bool hang_state = false;
    public:
        Pneumatics(uint8_t port_back, uint8_t port_front, uint8_t hang_port_L1);
        void toggle_back_wings();
        void toggle_front_wings(); 
        void toggle_hang(); 

        bool get_state_back_wings();
        bool get_state_front_wings(); 
        bool get_state_hang(); 
    
};