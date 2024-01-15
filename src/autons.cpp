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



///
// Constants
///

// It's best practice to tune constants when the robot is empty and with heavier game objects, or with lifts up vs down.
// If the objects are light or the cog doesn't change much, then there isn't a concern here.

void default_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 0, 0, 0, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0, 0, 0, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0, 0, 0, 0);
  chassis.set_pid_constants(&chassis.turnPID, 0, 0, 0, 0);
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
  chassis.set_exit_condition(chassis.turn_exit, 100, 10, 600, 7, 500, 600);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 100, 60, 500, 150, 500, 600);
}




///
// Drive Example
///
void drive_example() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater then the slew distance + a few inches
  chassis.set_mode(ez::DRIVE); // Drive
  
  std::printf("\ncalled drive_example\n");
  chassis.set_drive_pid(4, 90, false);
  chassis.wait_drive();

  std::printf("\n12 drivespeed\n"); 
  chassis.set_drive_pid(-12, DRIVE_SPEED, false);
  chassis.wait_drive();

  pros::delay(1000);

  chassis.set_drive_pid(8, 90, false);
  chassis.wait_drive();

  chassis.set_mode(ez::DISABLE); 

  // chassis.set_tank(127, 127); // Run drive motors myself
  // pros::delay(2000);
  // chassis.set_tank(0, 0);


}


void defensive_x2() {

  chassis.set_angle(chassis.get_gyro()); 

  chassis.set_mode(ez::DRIVE); 
  // chassis.set_mode(ez::DRIVE); 
  chassis.set_drive_pid(4, 90);
  chassis.wait_drive();

  // chassis.set_turn_pid(-68.2, TURN_SPEED);// negative = clockwise 
  // chassis.wait_drive();
  
  // chassis.set_mode(ez::DRIVE); // Drive
  // init with bot angled at theta
  chassis.set_drive_pid(2.6925 * constants::TILE_LENGTH, 90, false);
  chassis.wait_drive();

  // chassis.set_mode(ez::TURN); // Drive
  chassis.set_turn_pid(-315, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_mode(ez::DISABLE); 


  // chassis.set_drive_pid( 1.5 * constants::TILE_LENGTH, 90, false ); 
  // chassis.wait_drive(); 

  // chassis.set_drive_pid( -1 * constants::TILE_LENGTH, 90, false ); 
  // chassis.wait_drive(); 


}

void defensive_raw() {
  Wings wings = Wings {ports::WING_PORT_LEFT, ports::WING_PORT_RIGHT, ports::ARM_PORT};
  chassis.joy_thresh_opcontrol(-100, -100);
  pros::Task::delay(3500); //testing 
   
  chassis.joy_thresh_opcontrol(0,0);
  pros::Task::delay(500); 

  wings.toggle_wings();

  chassis.joy_thresh_opcontrol(50, 0); 
  pros::Task::delay(1000);

  chassis.joy_thresh_opcontrol(0, 50);  
  pros::Task::delay(375); // 135/360 

  chassis.joy_thresh_opcontrol(90, 90); 
  pros::Task::delay(1000); 

  chassis.joy_thresh_opcontrol(-80, -80); 
  pros::Task::delay(500); 

  chassis.joy_thresh_opcontrol(80, 80); 
  pros::Task::delay(500); 


  



  // chassis.joy_thresh_opcontrol(0,80);
  // pros::Task::delay(500); 

  // chassis.joy_thresh_opcontrol(-20,-20);
  // pros::Task::delay();


  // intake.switch_polarity();
  // intake.toggle(); 
  // pros::task::delay(1000);

  // chassis.joy_thresh_opcontrol(90, 90);
  // pros::Task::delay(400);

  // chassis.joy_thresh_opcontrol(0,0);
  // pros::Task::delay(100); 

  // chassis.joy_thresh_opcontrol(-90, -90);
  // pros::Task::delay(500);
  // chassis.joy_thresh_opcontrol(0, 0);

  //360 ccw
  // 135 cw 
}

void offensive_raw() {
  Intake intake = Intake {ports::INTAKE_MOTOR};
  intake.toggle(); 

  chassis.joy_thresh_opcontrol(-90, -90);
  pros::Task::delay(1000);
  
  chassis.joy_thresh_opcontrol(0,0);
  pros::Task::delay(100); 

  chassis.joy_thresh_opcontrol(90, 90);
  pros::Task::delay(400);

  // double ram??

  chassis.joy_thresh_opcontrol(50, 0); 
  pros::Task::delay(500);

  chassis.joy_thresh_opcontrol(90, 90);
  pros::Task::delay(200); 
  intake.switch_polarity(); 
  pros::Task::delay(200); 

  chassis.joy_thresh_opcontrol(0,0);

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



///
// Swing Example
///
void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is target degrees
  // The third parameter is speed of the moving side of the drive


  chassis.set_swing_pid(ez::LEFT_SWING, 45, SWING_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_until(12);

  chassis.set_swing_pid(ez::RIGHT_SWING, 0, SWING_SPEED);
  chassis.wait_drive();
}



///
// Auto that tests everything
///
void combining_movements() {
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_swing_pid(ez::RIGHT_SWING, -45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_drive();
}



///
// Interference example
///
void tug (int attempts) {
  for (int i=0; i<attempts-1; i++) {
    // Attempt to drive backwards
    printf("i - %i", i);
    chassis.set_drive_pid(-12, 127);
    chassis.wait_drive();

    // If failsafed...
    if (chassis.interfered) {
      chassis.reset_drive_sensor();
      chassis.set_drive_pid(-2, 20);
      pros::delay(1000);
    }
    // If robot successfully drove back, return
    else {
      return;
    }
  }
}

// If there is no interference, robot will drive forward and turn 90 degrees. 
// If interfered, robot will drive forward and then attempt to drive backwards. 
void interfered_example() {
 chassis.set_drive_pid(24, DRIVE_SPEED, true);
 chassis.wait_drive();

 if (chassis.interfered) {
   tug(3);
   return;
 }

 chassis.set_turn_pid(90, TURN_SPEED);
 chassis.wait_drive();
}



// . . .
// Make your own autonomous functions here!
// . . .