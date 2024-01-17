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
    bool intake_on = false;    
public:
    
    Intake(int8_t port);
    void set_voltage(int32_t voltage);

    void switch_polarity();
    int8_t get_polarity(); 

    Intake::level get_level();
    void move_level(); 

    int8_t get_state();

    void toggle(); 
    void toggle(bool state); // set state urself  

    void set_polarity(int polar);

    int get_avg_velocity();


};