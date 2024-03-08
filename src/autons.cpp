#include "main.h"
#include "Robot.hpp"
#include "ports.hpp"

// Intake intake = Intake {ports::INTAKE_MOTOR};
// Pneumatics wings = Pneumatics {ports::WING_PORT_FRONT_RIGHT, ports::WING_PORT_FRONT_LEFT, ports::WING_PORT_BACK, ports::RATCHET};
// Matchloader matchloader = Matchloader {ports::BIG_CATAPULT_MOTOR,ports::SMALL_CATAPULT_MOTOR };
// Climb climb = Climb { ports::BIG_CATAPULT_MOTOR,ports::SMALL_CATAPULT_MOTOR }; 

// pros::Motor left_front_motor(ports::LEFT_FRONT_TOP_DT, pros::E_MOTOR_GEARSET_06); // port 1, blue gearbox, not reversed
// pros::Motor left_middle_motor(ports::LEFT_FRONT_BOTTOM_DT, pros::E_MOTOR_GEARSET_06); // port 1, blue gearbox, not reversed
// pros::Motor left_back_motor(ports::LEFT_BACK_DT, pros::E_MOTOR_GEARSET_06); // port 2, green gearbox, not reversed

// pros::Motor right_front_motor(ports::RIGHT_FRONT_TOP_DT, pros::E_MOTOR_GEARSET_06); // port 3, red gearbox, reversed
// pros::Motor right_middle_motor(ports::RIGHT_FRONT_BOTTOM_DT, pros::E_MOTOR_GEARSET_06); // port 3, red gearbox, reversed
// pros::Motor right_back_motor(ports::RIGHT_BACK_DT, pros::E_MOTOR_GEARSET_06); // port 4, red gearbox, reversed

// pros::MotorGroup left_side_motors({left_front_motor,left_middle_motor, left_back_motor});
// pros::MotorGroup right_side_motors({right_front_motor, right_middle_motor, right_back_motor});

// lemlib::Drivetrain drivetrain2(
//   &left_side_motors, // left motor group
//   &right_side_motors, // right motor group
//   11, // 10 inch track width
//   lemlib::Omniwheel::NEW_325, // using new 3.25" omnis
//   450, // drivetrain rpm is 360
//   4 // chase power is 2. If we had traction wheels, it would have been 8
// );

// // inertial sensor
// pros::Imu inertial_sensor(14); // port 2
 
// // odometry struct
// lemlib::OdomSensors sensors {
//     nullptr, // vertical tracking wheel 1
//     nullptr, // vertical tracking wheel 2
//     nullptr, // horizontal tracking wheel 1
//     nullptr, // we don't have a second tracking wheel, so we set it to nullptr
//     &inertial_sensor // inertial sensor
//     // nullptr
// };

// // forward/backward PID
// lemlib::ControllerSettings lateralController {
//     27, // proportional gain (kP)
//     0, // integral gain (kI)
//     26, // derivative gain (kD)
//     3, // anti windup
//     1, // small error range, in inches
//     100, // small error range timeout, in milliseconds
//     3, // large error range, in inches
//     500, // large error range timeout, in milliseconds
//     2 // maximum acceleration (slew)
// };
 
// // turning PID
// lemlib::ControllerSettings angularController {
//     1.85, // kP
//     0, // integral gain (kI)
//     11, // derivative gain (kD)
//     3, // anti windup
//     1, // small error range, in inches
//     100, // small error range timeout, in milliseconds
//     3, // large error range, in inches
//     500, // large error range timeout, in milliseconds
//     2 // maximum acceleration (slew)
// };


// lemlib::Logger log {lemlib::logger::Level::debug};

// lemlib::Chassis chassis(drivetrain2, lateralController, angularController, sensors);
/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////


const int DRIVE_SPEED = 110; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                             // If this is 127 and the robot tries to heading correct, it's only correcting by
                             // making one side slower.  When this is 87%, it's correcting by making one side
                             // faster and one side slower, giving better heading correction.
const int TURN_SPEED  = 90;
const int SWING_SPEED = 90;

double T= constants::TILE_LENGTH *0.8; 
// const double AM = constants::AUTON_MULTIPLIER;
// const double AM = 1.9 - master.get_battery_level() /100 ;



///
// Constants
///

// It's best practice to tune constants when the robot is empty and with heavier game objects, or with lifts up vs down.
// If the objects are light or the cog doesn't change much, then there isn't a concern here.



// void skills() {
//     chassis.setPose(-55, -45, 0);
//     chassis.moveToPose(-24, 60, 120, 3000, {.forwards = true}); 
//     // 46 -50
//     chassis.moveToPose(46, -50, 120, 3000, {.forwards = true}); 
//     // 59 25
//     chassis.moveToPose(59, -25, 120, 3000, {.forwards = true}); 
// }
