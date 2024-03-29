
#include "Drivetrain.hpp"

#define E 2.71828 

// regular constructor 
Drivetrain::Drivetrain(int8_t left1, int8_t left2, int8_t left3, 
    int8_t right1, int8_t right2, int8_t right3) :
    leftMotors {{left1, left2, left3}},
    rightMotors {{right1, right2, right3}}

    {}; 

// copy constructor (used in Robot.cpp)
Drivetrain::Drivetrain(Drivetrain& t) 
:
    leftMotors {{t.leftMotors[0], t.leftMotors[1], t.leftMotors[2]}},
    rightMotors {{ t.rightMotors[0], t.rightMotors[1], t.rightMotors[2]}}

{};

// dampen input voltages
std::vector<double> dampen_turns(double left_voltage, double right_voltage, 
    double left_dampen, double right_dampen) {

    return {left_voltage * left_dampen , right_voltage * right_dampen };
}

// updates voltage supplied to each side 
void Drivetrain::move_voltage(double left_voltage, double right_voltage) {
    leftMotors.move_voltage(left_voltage);
    rightMotors.move_voltage(right_voltage); 
}

std::vector<double> Drivetrain::arcade(double left_y_input, double right_x_input) {
    // computes velocity for left and right side 
    double left_output = left_y_input -  right_x_input;
    double right_output = left_y_input + right_x_input;

    // scales for voltage range 
    return {left_output/127 * 12000, right_output/127 * 12000};
}


// computes curvature drive values 
// std::vector<double> Drivetrain::curvature(
//     double xSpeed, double zRotation, bool allowTurnInPlace) {

//     // scales everything to a -1 to 1 range
//     xSpeed = xSpeed/127;
//     zRotation = zRotation/127;

//     double leftSpeed = 0.0;
//     double rightSpeed = 0.0;

//     // if turn in place, default to arcade-like calculation 
//     if (allowTurnInPlace) {
//     leftSpeed = xSpeed - zRotation;
//     rightSpeed = xSpeed + zRotation;
//     } 

//     // left and right side are adjusted according to the rotational amount specified by right joystick
//     // dampens the impact of curvature joystick by the speed 
//     else {
//     leftSpeed = xSpeed - std::abs(xSpeed) * zRotation; // x(1 - z)
//     rightSpeed = xSpeed + std::abs(xSpeed) * zRotation; // x (1 + z)
//     }

//     // Desaturate wheel speeds 
//     // (essentially if one value is outside of the limits -1 to 1, rescales values accordingly)
//     double maxMagnitude = std::max(std::abs(leftSpeed), std::abs(rightSpeed));
//     if (maxMagnitude > 1.0) {
//     leftSpeed /= maxMagnitude;
//     rightSpeed /= maxMagnitude;
//     }

//     return {leftSpeed * 12000, rightSpeed* 12000};
// }


std::vector<double> Drivetrain::curvature(double throttle, double turn) {
    if (throttle == 0) {
        return arcade(throttle, turn);
    }

    double leftPower = throttle + (std::abs(throttle) * turn) / 127.0;
    double rightPower = throttle - (std::abs(throttle) * turn) / 127.0;

    return {leftPower, rightPower}; 
    }


 // If we're not moving forwards change to arcade drive
  

/* 
overall driver command code, adjusts for friction and selects 
drive type 
0 = arcade
1 = curvature 

left input = input from left joystick
right input = input from right joystick 
*/ 
void Drivetrain::op_control(int drive_type, double left_input, 
    double right_input, double left_dampen, double right_dampen, double curve_gain ) {
    std::vector<double> raw_volt;

    if (drive_type ==0) {
        raw_volt = arcade(left_input, right_input); 
    }
    else if (drive_type == 1) {
        raw_volt = curvature(right_input, left_input);
    }

    std::vector<double> dampened_velocities = dampen_turns(raw_volt[0], 
        raw_volt[1], left_dampen, right_dampen);
    move_voltage(dampened_velocities[0],dampened_velocities[1]);

}

auto Drivetrain::get_left_motor_group() {
    return leftMotors[0];
}

// std::vector<double> curvature(double xSpeed, double zRotation, bool allowTurnInPlace);


double Drivetrain::curve_input(double power, double t) {
    return std::pow(E, ((std::fabs(power) - 12000) * t)/1000)  * power; 
}
