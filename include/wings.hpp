#pragma once
#include "api.h"

class Wings {
    private:
        pros::ADIAnalogOut piston_port; 
    public:
        void toggle_piston();
};