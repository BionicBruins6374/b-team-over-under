#pragma once

#include "main.h"

class Wings {
private:
    pros::ADIDigitalOut piston;
    bool wingOut = false;

public:
    void pistonOut();
    Wings(int8_t pistonPort);
};
