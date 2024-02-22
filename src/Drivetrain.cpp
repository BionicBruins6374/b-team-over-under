
#include "Drivetrain.hpp"

// constructor 
Drivetrain::Drivetrain(int8_t left1, int8_t left2, int8_t left3, 
    int8_t right1, int8_t right2, int8_t right3) :
    leftMotors {{left1, left2, left3}},
    rightMotors {{right1, right2, right3}}

    {}; 

// copy constructor 
Drivetrain::Drivetrain(Drivetrain& t) 
:
    leftMotors {{t.leftMotors[0], t.leftMotors[1], t.leftMotors[2]}},
    rightMotors {{ t.rightMotors[0], t.rightMotors[1], t.rightMotors[2]}}

{
    // problem:  = is overloaded--so copy thingy doesnt work properly?
    
};

// dampen input voltages
std::vector<double> dampen_turns(double left_voltage, double right_voltage, double left_dampen, double right_dampen) {
  
    return {left_voltage * left_dampen , right_voltage * right_dampen };

}

// updates voltage supplied to each side 
void Drivetrain::move_voltage(double left_voltage, double right_voltage) {
    leftMotors.move_voltage(left_voltage);
    rightMotors.move_voltage(right_voltage); 
}



std::vector<double> Drivetrain::arcade(double left_y_input, double right_x_input) {
    // scales joystick inputs for arcade drive 
    double left_output = left_y_input -  right_x_input;
    double right_output = left_y_input + right_x_input;

    return {left_output/127 * 12000, right_output/127 * 12000};
}


// computes curvature drive values 
std::vector<double> Drivetrain::curvature(double xSpeed, double zRotation, bool allowTurnInPlace) {
    xSpeed = std::clamp(xSpeed, -1.0, 1.0);
    zRotation = std::clamp(zRotation, -1.0, 1.0);

  double leftSpeed = 0.0;
  double rightSpeed = 0.0;

  if (allowTurnInPlace) {
    leftSpeed = xSpeed - zRotation;
    rightSpeed = xSpeed + zRotation;
  } else {
    leftSpeed = xSpeed - std::abs(xSpeed) * zRotation;
    rightSpeed = xSpeed + std::abs(xSpeed) * zRotation;
  }

  // Desaturate wheel speeds
  double maxMagnitude = std::max(std::abs(leftSpeed), std::abs(rightSpeed));
  if (maxMagnitude > 1.0) {
    leftSpeed /= maxMagnitude;
    rightSpeed /= maxMagnitude;
  }

  return {leftSpeed/127 * 12000, rightSpeed/127 * 12000};
}


/* 
overall driver command code, adjusts for friction
0 = arcade
1 = curvature 

left input = input from left joystick
right input = input from right joystick 

*/ 
void Drivetrain::op_control(int drive_type, double left_input, double right_input, double left_dampen =1, double right_dampen =1 ) {
    std::vector<double> raw_volt;

    if (drive_type ==0) {
        raw_volt = arcade(left_input, right_input); 
    }
    else if (drive_type == 1) {
        raw_volt = curvature(left_input,right_input,false);
    }

    std::vector<double> dampened_velocities = dampen_turns(raw_volt[0], raw_volt[1], left_dampen, right_dampen);
    move_voltage(dampened_velocities[0],dampened_velocities[1]);

}