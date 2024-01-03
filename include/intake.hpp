#pragma once
#include "api.h"
class Intake {
private:
    pros::Motor intakeMotor; 
    int polarity = 1; 
public:
    Intake(uint8_t port);
    void set_voltage(int voltage);
    void switch_polarity();
};