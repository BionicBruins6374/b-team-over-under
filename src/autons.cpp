#include "main.h"
#include "Robot.hpp"
#include "ports.hpp"



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

const double T= constants::TILE_LENGTH; 
const double AM = constants::AUTON_MULTIPLIER;



///
// Constants
///

// It's best practice to tune constants when the robot is empty and with heavier game objects, or with lifts up vs down.
// If the objects are light or the cog doesn't change much, then there isn't a concern here.

void default_constants() {
   chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 1, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 4, 0, 5.5, 0); 
  chassis.set_pid_constants(&chassis.backward_drivePID, 4, 0, 5.5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5.25, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void one_mogo_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void two_mogo_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}


void modified_exit_condition() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}




///
// Drive Example
///
void drive_example() {
  chassis.set_mode(ez::DRIVE); // Drive
  
  // std::printf("\ncalled drive_example\n");
  // chassis.set_drive_pid(4, 90, false);
  // chassis.wait_drive();

  chassis.set_drive_pid(-12, DRIVE_SPEED, false);
  chassis.wait_drive();

  pros::delay(1000);

  chassis.set_drive_pid(12, 90, false);
  chassis.wait_drive();

  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();
}
//note for self :  use as auton example
// offensive simple, intakes triball at barrier, pushes 
void offensive_x2() {

  Intake intake = Intake {ports::INTAKE_MOTOR };
  chassis.set_angle(chassis.get_gyro()); 
  // turn on intake 
  intake.set_voltage(constants::HIGH_VOLTAGE_INTAKE); 
  chassis.set_drive_pid(6, DRIVE_SPEED, false); 

  
  // turn 90
  // chassis.set_turn_pid(270, TURN_SPEED); // check if ccw or cw;;; 
  // chassis.wait_drive();

  chassis.set_drive_pid(-2 * T, DRIVE_SPEED, false);
  chassis.wait_drive();

  // set turn to 45 
  chassis.set_turn_pid(-45, TURN_SPEED); // check if ccw or cw;;; 
  chassis.wait_drive();

  // drive -triangle 
  chassis.set_drive_pid(-0.9013 * T*AM, DRIVE_SPEED, false);  // sqrt(0.5^2 + 0.75^2)
  chassis.wait_drive();

  // set turn to 0
  chassis.set_turn_pid(-90, TURN_SPEED); // check if ccw or cw;;; 
  chassis.wait_drive();
  // drive -t 
  chassis.set_drive_pid(-T*AM, DRIVE_SPEED, false);
  chassis.wait_drive();
  // wait 
  pros::Task::delay(1000); 

  // drive 0.5t
  chassis.set_drive_pid(0.5 * T*AM, DRIVE_SPEED, false);
  chassis.wait_drive();
  // set turn to 180
  chassis.set_turn_pid(90, TURN_SPEED); // check if ccw or cw;;; 
  chassis.wait_drive();

  // drive 0.5 t
  chassis.set_drive_pid(0.5 * T*AM, DRIVE_SPEED, false);
  chassis.wait_drive();

  intake.set_voltage(-constants::HIGH_VOLTAGE_INTAKE); 
  
  pros::Task::delay(1000); 
  chassis.set_drive_pid(-6, DRIVE_SPEED, false); 

  intake.set_voltage(0); 


}


void defensive_x2() {

  chassis.set_angle(chassis.get_gyro()); 

  // chassis.set_mode(ez::DRIVE); 
  // chassis.set_mode(ez::DRIVE); 
  chassis.set_drive_pid(4, 90);
  chassis.wait_drive();

  chassis.set_turn_pid(-68.2, TURN_SPEED);// negative = clockwise 
  chassis.wait_drive();
  
  // chassis.set_mode(ez::DRIVE); // Drive
  // init with bot angled at theta
  chassis.set_drive_pid(2.6925 * T * 4, 90, false);
  chassis.wait_drive();

  // chassis.set_mode(ez::TURN); // Drive
  chassis.set_turn_pid(-315, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_mode(ez::DISABLE); 


  // chassis.set_drive_pid( 1.5 * T, 90, false ); 
  // chassis.wait_drive(); 

  // chassis.set_drive_pid( -1 * T, 90, false ); 
  // chassis.wait_drive(); 


}



///
// Turn Example
///
void turn_example() {
  // The first parameter is target degrees
  // The second parameter is max speed the robot will drive at
  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();
}



///
// Combining Turn + Drive
///
void drive_and_turn() {
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_drive();
}



///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
  // wait_until will wait until the robot gets to a desired position


  // When the robot gets to 6 inches, the robot will travel the remaining distance at a max speed of 40
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_until(6);
  chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  // When the robot gets to -6 inches, the robot will travel the remaining distance at a max speed of 40
  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_until(-6);
  chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
  chassis.wait_drive();
}






// . . .
// Make your own autonomous functions here!
// . . .

void alliance_triball() {
  chassis.joy_thresh_opcontrol(-90, -90);
  pros::Task::delay(1000);
  
  chassis.joy_thresh_opcontrol(0,0);
  pros::Task::delay(100);

  chassis.joy_thresh_opcontrol(90, 90);
  pros::Task::delay(400);

  chassis.joy_thresh_opcontrol(0,0);
  pros::Task::delay(100); 

  chassis.joy_thresh_opcontrol(-90, -90);
  pros::Task::delay(500);

  
  chassis.joy_thresh_opcontrol(0, 0);
  pros::Task::delay(100); 
  chassis.joy_thresh_opcontrol(90, 90); 
  pros::Task::delay(300); 
}

//OMG MY FIRST REAL CODE THING (not including the other function that zoya used as a test) -- sahil

void defence_auton(){
  //move bot forward sqrt(3) tiles
  chassis.set_drive_pid(24 * sqrt(3), DRIVE_SPEED, true );
  //move bot back to starting location 
  chassis.set_drive_pid(-24 * sqrt(3), DRIVE_SPEED, true);
  //turn some degrees
  chassis.set_turn_pid(110, DRIVE_SPEED);
  //move bot forward 2 tiles to push middle tribal
  chassis.set_drive_pid(24 * 1.85);

}