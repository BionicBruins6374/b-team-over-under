#pragma once
#include "api.h"

class Wings {
    private:
        pros::ADIDigitalOut piston_right; 
        pros::ADIDigitalOut piston_left; 

        bool state = false; 
    public:
        Wings(uint8_t port_right, uint8_t port_left);
        void toggle_piston();
        bool get_state();
    
};