#pragma once
#include "api.h"

class Drivetrain {
    private:
        pros::Motor_Group leftMotors; 
        pros::Motor_Group rightMotors; 
    public: 
        Drivetrain(int8_t left1, int8_t left2, int8_t left3, int8_t right1, int8_t right2, int8_t right3); 
        Drivetrain(Drivetrain& t); 
        // std::vector<double> curvature(double xSpeed, double zRotation, bool allowTurnInPlace);
        std::vector<double> curvature(double xSpeed, double zRotation);

        double curve_input(double power, double t);
        std::vector<double> arcade(double left_y_input, double right_x_input);  
        void move_voltage(double left_voltage, double right_voltage);
        void op_control(int drive_type, double left_input, double right_input, double left_dampen, double right_dampen, double curve_gains );
        auto get_left_motor_group(); 
        
};