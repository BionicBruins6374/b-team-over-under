#pragma once
#include "api.h"

class Wings {
    private:
        pros::ADIDigitalOut right_wing; 
        pros::ADIDigitalOut left_wing;
        pros::ADIDigitalOut hang; 

        bool wing_state = false; 
        bool hang_state = true;
    public:
        Wings(uint8_t port_right, uint8_t port_left, uint8_t hang_port);
        void toggle_piston();
        void toggle_wings();
        void toggle_hang(); 
        bool get_state_wings();
        bool get_state_hang(); 
    
};