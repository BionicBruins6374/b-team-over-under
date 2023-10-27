#pragma once

#include "main.h"



class Flywheel {
    private:
    // TODO: test and change values
        enum Speed {
            high = 11000,
            low = 7000
        };
        bool powerState = false; // false is off, true is on
        Speed speed = high; // high speed is true, low speed is false; will only be considered when Flywheel on
        Motor m_left;   
        int8_t polarity = -1; // -1 = deintaking, 1 = shooting; TODO: change default value?     
    public:
        Flywheel(uint8_t m_left_port);
        void toggle();
        void speed_change(); 
        void change_direction();
};