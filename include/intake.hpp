#pragma once
#include "api.h"
class Intake {

enum level {
        high = 12000,
        low = 10000
    };

private:
    pros::Motor intakeMotor; 
    int polarity = 1; 
    Intake::level level_state = high;
    int32_t current_ideal_voltage = 0;
    

public:
    
    Intake(int8_t port);
    void set_voltage(int8_t voltage);
    void switch_polarity();

    Intake::level get_level();
    void move_level(); 

    int32_t get_volt();

};