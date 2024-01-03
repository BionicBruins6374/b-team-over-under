#pragma once
#include "api.h"
class Intake {
private:
    pros::Motor intakeMotor; 
    int polarity = 1; 
    level level_state = high;
    int32_t current_ideal_voltage = 0;
public:
    Intake(uint8_t port);
    void set_voltage(int voltage);
    void switch_polarity();

    level get_level();
    void move_level(); 

    int32_t get_volt();

    enum level {
        high = 12000,
        low = 10000
    };
};

