#pragma once
#include "api.h"

class Wings {
    private:
        pros::ADIDigitalOut piston; 
        bool state = false; 
    public:
        Wings(int8_t piston_port);
        void toggle_piston();
};