#pragma once
#include "api.h"

class Wings {
    private:
        pros::ADIDigitalOut right_wing; 
        pros::ADIDigitalOut left_wing;
        pros::ADIDigitalOut arms; 

        bool wing_state = false; 
        bool arm_state = false;
    public:
        Wings(uint8_t port_right, uint8_t port_left, uint8_t arm_port);
        void toggle_piston();
        void toggle_wings();
        void toggle_arm(); 
        bool get_state_wings();
        bool get_state_arms(); 
    
};