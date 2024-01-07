#pragma once
#include "api.h"

class Wings {
    private:
        pros::ADIDigitalOut piston; 
        bool state = false; 
    public:
        Wings(uint8_t piston_port);
        void toggle_piston();
        bool get_state();
    
};