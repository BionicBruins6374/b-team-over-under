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

double T= constants::TILE_LENGTH *0.8; 
// const double AM = constants::AUTON_MULTIPLIER;
const double AM = 1.9 - master.get_battery_level() /100 ;



///
// Constants
///

// It's best practice to tune constants when the robot is empty and with heavier game objects, or with lifts up vs down.
// If the objects are light or the cog doesn't change much, then there isn't a concern here.

void default_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 5.2, 0, 5, 0); // setting first param to 11 would make it spin 
  chassis.set_pid_constants(&chassis.forward_drivePID, 35, 0, 25, 0); 
  chassis.set_pid_constants(&chassis.backward_drivePID, 35, 0, 25, 0);
  chassis.set_pid_constants(&chassis.turnPID, 8.05, 0, 24, 0);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 0, 0);

}


void modified_exit_condition() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 75, 50, 250, 150, 500, 450);
}

double pt(double x, double y){
  return(sqrt(x * x + y * y));
}


///
// Drive Example
///
void drive_example() {
  // std::printf("\ncalled drive_example\n");
  // chassis.set_drive_pid(4, 90, false);
  // chassis.wait_drive();
  chassis.set_angle(chassis.get_gyro()); 

  // chassis.set_drive_pid(-T, DRIVE_SPEED, false);
  // chassis.wait_drive();

  // pros::delay(1000);

  // chassis.set_drive_pid(T, 90, false);
  // chassis.wait_drive();

  chassis.set_drive_pid(T * AM, DRIVE_SPEED * 0.8, false);
  chassis.wait_drive();
  // chassis.set_swing_pid

  chassis.set_drive_pid(-T * AM, DRIVE_SPEED  * 0.8, false);
  chassis.wait_drive();

  // chassis.set_swing_pid(ez::LEFT_SWING, 90, TURN_SPEED);
  // chassis.wait_drive();

  // chassis.set_swing_pid(ez::LEFT_SWING, 45, TURN_SPEED);
  // chassis.wait_drive();

  // chassis.set_swing_pid(ez::LEFT_SWING, 0, TURN_SPEED);
  // chassis.wait_drive();

  // chassis.set_swing_pid(ez::LEFT_SWING, -45, TURN_SPEED);
  // chassis.wait_drive();

   chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive(); 

}

void offensive_new(Intake intake, Pneumatics pneumatics) {
  // init facing front, parallel with goal
  chassis.set_angle(chassis.get_gyro()); 

  chassis.set_turn_pid(45, TURN_SPEED); 
  chassis.wait_drive();


  double diag1 = sqrt(5 * T*T ); 
  // intake on
  intake.set_voltage(constants::HIGH_VOLTAGE_INTAKE);
  chassis.set_drive_pid(diag1, DRIVE_SPEED, false);
  chassis.wait_drive(); 

  pros::Task::delay(1000); 

  chassis.set_drive_pid(-diag1/4, DRIVE_SPEED, false); 
  chassis.wait_drive(); 


  // flips around to shoot triball 
  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  intake.set_voltage(-constants::HIGH_VOLTAGE_INTAKE);
  pros::Task::delay(500);

  chassis.set_turn_pid(25, TURN_SPEED);  // TODO 
  chassis.wait_drive(); 

  intake.set_voltage(constants::HIGH_VOLTAGE_INTAKE);

  double diag2  = 1.25 * T * T;
  // turn on intake
  chassis.set_drive_pid(diag2, DRIVE_SPEED, false); // sqrt((0.5T)^2 + T^2)
  chassis.wait_drive(); 

  intake.set_voltage(0); // TODO

  chassis.set_drive_pid (-diag2/4, DRIVE_SPEED, false);
  chassis.wait_drive();

  // turn on wings and approach from an angle 
  pneumatics.toggle_front_wings(); 
  chassis.set_turn_pid(-45 , TURN_SPEED); // TODO
  chassis.wait_drive(); 
  pros::Task::delay(400);
  // move forward tiny bit 
  chassis.set_drive_pid(2, DRIVE_SPEED, false);
  // angle towards goal 
  chassis.set_turn_pid(90, TURN_SPEED);   
  chassis.wait_drive(); 

  // drive to goal
  chassis.set_drive_pid(T/2 * AM, DRIVE_SPEED, false); 
  chassis.wait_drive(); 
  
  intake.set_voltage(-constants::HIGH_VOLTAGE_INTAKE); 
}

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

void offensive_ez(Pneumatics pneumatics){
  // reset angle
  pneumatics.toggle_front_wings(); 
  chassis.set_drive_pid(1.5 * T, DRIVE_SPEED, false); 
  chassis.wait_drive(); 

  // go -0.75T

  // set angle to 0

  // 0.75T 

  // -0.75T 
  
  // set angle 0

  // -0.75t


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


void skills_ez(Matchloader matchloader, Pneumatics pneumatics) {
// init angle 
  chassis.set_angle(chassis.get_gyro());
  // init = 65 deg
  matchloader.set_voltage(-12000);
  pros::Task::delay(45000);
  matchloader.set_voltage(0); 

  // move 3.5 tiles 
  chassis.set_drive_pid(3.5 * T, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(25 + 90, TURN_SPEED);
  chassis.wait_drive();


  // turn 25 deg ( or more so we overshoot) (so we face goal directly)
  // turn on wings
  pneumatics.toggle_front_wings();
  // drive forward 4 tiles
  chassis.set_drive_pid(4* T, DRIVE_SPEED, false);
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

void defence_auton(Pneumatics wings){
  chassis.set_angle(chassis.get_gyro());

  //move bot forward sqrt(3) tiles
  chassis.set_drive_pid(T * 3, DRIVE_SPEED, true );
  chassis.wait_drive();
  //move bot back to starting location 
  chassis.set_drive_pid(- T * 3, 50 , true);
  chassis.wait_drive();
  //turn some degrees
  chassis.set_turn_pid(-135, DRIVE_SPEED);
  chassis.wait_drive();
  //pop wings to touch side bar
  wings.toggle_back_wings();
  
  //move bot forward 2 tiles to push middle tribal
  //moves 1.85 so it doesnt go past middle bar
  chassis.set_drive_pid(-1 * T * 3, DRIVE_SPEED, false);
  chassis.wait_drive();

  //moves robot backwards so its ready to matchload

  // chassis.set_drive_pid(-1 * T * 2, DRIVE_SPEED, true);
  // chassis.wait_drive();


}
//beggining seconds for skills

void skills_triball(Pneumatics wings, Matchloader cata) {
  // make it a task so can op control override it?? 
  //move bot forward sqrt(3) tiles

  //maybe add the reset angle 
  // 28 = length of bot in holes
  chassis.set_drive_pid((25 + 7) * AM, DRIVE_SPEED, true );
  chassis.wait_drive();

  //move back slightly 
  //10.5 INCHES
  chassis.set_drive_pid(-3 * AM , DRIVE_SPEED * 0.7 , false);
  chassis.wait_drive(); 

  chassis.set_turn_pid(-25, TURN_SPEED);
   chassis.wait_drive();

  chassis.set_drive_pid(-8 * AM , DRIVE_SPEED * 0.7 , false);
  chassis.wait_drive();

  //after tribal is in spin bot to ideal angle for matchloading
  //while spinning start matchload so matchloaders can start counting
  chassis.set_turn_pid(-100, TURN_SPEED);
  chassis.wait_drive();

  //pop wings to touch loading bar 
  wings.toggle_front_wings();
  //move back VERY LITTLE so the bot is touching the bar
  chassis.set_drive_pid(T * 0.55 * -1, DRIVE_SPEED, false);

}

//adelle defensive (1 alliance in)(2 over the barrier)
void defensive_triballA(Intake intake, Pneumatics wings){
  //go straight
  chassis.set_angle(chassis.get_gyro());
  chassis.set_drive_pid(T*sqrt(5), DRIVE_SPEED, false);
  chassis.wait_drive();

  //intake triball
  intake.set_voltage(constants::HIGH_VOLTAGE_INTAKE);
  pros::Task::delay(500);

  //go backwards
  chassis.set_drive_pid(T*0.5, DRIVE_SPEED, false);
  chassis.wait_drive();

  //turn to face straight
  chassis.set_turn_pid(63.43, TURN_SPEED);
  chassis.wait_drive();
  
  //open wings
  wings.toggle_front_wings();
  pros::Task::delay(500);

  //go to barrier
  chassis.set_drive_pid(T*1.25, DRIVE_SPEED, false);
  chassis.wait_drive();

  //outake triball
  intake.set_voltage(-constants::HIGH_VOLTAGE_INTAKE);
  pros::Task::delay(500);
}

//adelle offensive (1 alliance in)(2 triballs in)
void offensive_x3(Intake intake, Pneumatics wings) {

  //TEMP
  T = T*2;  
  //set angle
  chassis.set_angle(chassis.get_gyro());

  //face the goal and score
  chassis.set_turn_pid(30, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(T*2, DRIVE_SPEED, false);
  chassis.wait_drive();
  chassis.set_drive_pid(-T*0.75, DRIVE_SPEED, false);
  chassis.wait_drive();
  
  //turn for triball
  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(2.83*T, DRIVE_SPEED, false);
  chassis.wait_drive();

  //turn on intake
  intake.set_voltage(constants::HIGH_VOLTAGE_INTAKE);
  pros::Task::delay(500);
  
  //go back
  chassis.set_drive_pid(-0.5*T, DRIVE_SPEED, false);
  chassis.wait_drive();
  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(2.4*T, DRIVE_SPEED, false);
  chassis.wait_drive();
  chassis.set_drive_pid(T, DRIVE_SPEED, false);

}

void awp_diff(Pneumatics wings, Intake intake ) {
  int T_L = T;
  chassis.set_angle(chassis.get_gyro());

  pros::Task::delay(50);
 wings.toggle_front_wings();
  pros::Task::delay(100);
 wings.toggle_front_wings();

 double mid_fwd = pt(0.5, 2);


 intake.set_voltage(12000);


 chassis.set_drive_pid((1.0655 +0.2 + 1)* T_L * AM, DRIVE_SPEED, false);
 chassis.wait_drive();
 
 pros::Task::delay(500);


 chassis.set_turn_pid(7, TURN_SPEED);
 chassis.wait_drive();

 chassis.set_drive_pid((-2.2 * T_L)* AM , DRIVE_SPEED, false);
 chassis.wait_drive();
 
  // chassis.set_swing_pid(ez::RIGHT_SWING, 170, TURN_SPEED);
 // chassis.wait_drive();
  chassis.set_turn_pid(145-10, TURN_SPEED);
 chassis.wait_drive();


 // ram
 chassis.set_drive_pid(AM * (26 * 0.5  -0.7*T_L), DRIVE_SPEED, false );
 chassis.wait_drive();


 // 150 inc
 chassis.set_turn_pid(140, TURN_SPEED); // TODO INC ANGLE (spin ccw)
 chassis.wait_drive();
 // T
 chassis.set_drive_pid((T_L)* AM, DRIVE_SPEED, true);
 chassis.wait_drive();
 wings.toggle_front_wings();

 chassis.set_drive_pid((T_L * 0.3)* AM, DRIVE_SPEED/3, false);
 chassis.wait_drive();

 // 180-35
 chassis.set_turn_pid(150-35, TURN_SPEED/2); // TODO CHANGE SPEED??
 chassis.wait_drive();


 //little bit
 chassis.set_drive_pid(T_L* AM * 0.2, DRIVE_SPEED/2, false);
 chassis.wait_drive();
 
 // 0.6t
 chassis.set_drive_pid(T_L* AM * 0.2, DRIVE_SPEED/2, false);
 chassis.wait_drive();
 
  // 35 ccw
 chassis.set_turn_pid(105-35, TURN_SPEED/2);
 chassis.wait_drive();

  wings.toggle_front_wings();

 // 1.75
 chassis.set_drive_pid(T_L* AM * 1.26, DRIVE_SPEED/1.5, false);
 chassis.wait_drive();
 // outtake
 intake.set_voltage(-12000);

 }


  


void drive_to_angle(double angle) {
  chassis.set_turn_pid(angle, TURN_SPEED/2);
  chassis.wait_drive(); 
}

void awp_short(Pneumatics wings, Intake intake) {
  chassis.set_angle(chassis.get_gyro());

  wings.toggle_front_wings();
  wings.toggle_front_wings();

  intake.set_voltage(12000);
  // todo--siwtch to 0.42  
  chassis.set_drive_pid(-0.42 * T * AM, DRIVE_SPEED * 0.7, false );
  chassis.wait_drive();
  wings.toggle_front_wings();

  chassis.set_drive_pid(0.42 * T * AM, DRIVE_SPEED * 0.7, false);
  chassis.wait_drive();
  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  wings.toggle_front_wings();

  chassis.set_drive_pid(0.1* T * AM, DRIVE_SPEED, false);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(0.3 * T * AM, DRIVE_SPEED, false);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, TURN_SPEED); 
  chassis.wait_drive();

  chassis.set_drive_pid(1.23 * T * AM, DRIVE_SPEED, false); 
  chassis.wait_drive();

   chassis.set_turn_pid(-45, TURN_SPEED); 
  chassis.wait_drive();
  // chassis.set_turn_pid(135, TURN_SPEED);   
  intake.set_voltage(-12000);
  // pros::Task::delay(5);
  // intake.set_voltage(0);



  // // set angle 45
  // chassis.set_turn_pid(45, TURN_SPEED); 
  // // drive 1.5 T 
  // chassis.set_drive_pid(1.5 * T * AM );

}


void offensive_4ball(Pneumatics wings, Intake intake) {

  // shoots preload
  wings.toggle_front_wings();
  wings.toggle_front_wings(); 
  intake.set_voltage(constants::HIGH_VOLTAGE_INTAKE); 
  // step 1
  chassis.set_drive_pid(pt(2.333, 2.5) * T * AM, DRIVE_SPEED, false); 
  chassis.wait_drive();
  // turn to 135
  chassis.set_turn_pid(135, TURN_SPEED);
  chassis.wait_drive();

  // step 2
  chassis.set_drive_pid(2 * T * AM, DRIVE_SPEED, false); 
  chassis.wait_drive();

  // deintake and then reintake
  intake.set_voltage(-constants::HIGH_VOLTAGE_INTAKE); 
  pros::Task::delay(1000);
  intake.set_voltage(constants::HIGH_VOLTAGE_INTAKE); 

  // step 3
  chassis.set_drive_pid(-T * AM, DRIVE_SPEED, false); 
  chassis.wait_drive();

  // turn to (135 + 135) = 270
  chassis.set_turn_pid(270, TURN_SPEED);
  chassis.wait_drive();

  double d = pt(T, T); 

  // step 4
  chassis.set_drive_pid(d * AM, DRIVE_SPEED, false);
  chassis.wait_drive();

  pros::Task::delay(1000); 

  // step 5
  chassis.set_drive_pid(-d/2  * AM, DRIVE_SPEED, false);
  chassis.wait_drive();

  // turn to 180
  chassis.set_turn_pid(180, TURN_SPEED);
  chassis.wait_drive();

  // step 6
  chassis.set_drive_pid(pt(2.5, 2.5) * T  * AM, DRIVE_SPEED, false);
  chassis.wait_drive();

  // turn to 90
  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();

  // step 7
  chassis.set_drive_pid(d/2  * AM, DRIVE_SPEED, false);
  chassis.wait_drive();

  // turn to 45
  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  // step 8
  chassis.set_drive_pid(T  * AM, DRIVE_SPEED, false); 
  chassis.wait_drive();

  intake.set_voltage(-constants::HIGH_VOLTAGE_INTAKE); 
  pros::Task::delay(1000);
  intake.set_voltage(0);

  // backs out
  chassis.set_drive_pid(0.5 * T * AM, DRIVE_SPEED, false); 
  chassis.wait_drive(); 

}

void hwanseo_offensive(Intake intake, Pneumatics wings){
  //enter code here
  chassis.set_angle(chassis.get_gyro());

  //wings out for alliance triball
  pros::Task::delay(50);
  wings.toggle_front_wings(); 
  pros::Task::delay(100);
  wings.toggle_front_wings();  
  intake.set_voltage(constants::HIGH_VOLTAGE_INTAKE); 

  //drive to center triball
  chassis.set_drive_pid(3 * T * AM, DRIVE_SPEED*0.9, true);
  chassis.wait_drive();
  

  //turn toward goal
  chassis.set_turn_pid(135, TURN_SPEED/1.5);
  chassis.wait_drive();
  
  //open wings
  wings.toggle_front_wings();
  
  //push in to goal
  chassis.set_drive_pid(1.5 * T * AM, DRIVE_SPEED, false);
  chassis.wait_drive();
  intake.set_voltage(-constants::HIGH_VOLTAGE_INTAKE);
  wings.toggle_front_wings();
  
  //move back
  chassis.set_drive_pid(-1 * T * AM, DRIVE_SPEED, false);
  chassis.wait_drive();
  
  //turn to other triball
  chassis.set_turn_pid(262, TURN_SPEED);
  chassis.wait_drive();

  //intake on + drive to triball
  intake.set_voltage(constants::HIGH_VOLTAGE_INTAKE);
  chassis.set_drive_pid(0.7 * T * AM, DRIVE_SPEED, false);
  chassis.wait_drive();

  //turn to bar 
  chassis.set_turn_pid(162, TURN_SPEED);
  chassis.wait_drive();

  // drive to matchload 
  chassis.set_drive_pid(2* T * AM, DRIVE_SPEED, false);
  chassis.wait_drive();

  chassis.set_drive_pid(0.5 * T * AM, DRIVE_SPEED/3, false);
  chassis.wait_drive();
  // take out triball
  wings.toggle_front_wings();
  // turn to goal
  chassis.set_turn_pid(50, TURN_SPEED);
  chassis.wait_drive();
  // drive to goal
  chassis.set_drive_pid(0.8* T * AM, DRIVE_SPEED, false);
  chassis.wait_drive();
  // deintake
  intake.set_voltage(-constants::HIGH_VOLTAGE_INTAKE);
  
  wings.toggle_front_wings();

  chassis.set_drive_pid(-0.3 * T * AM, DRIVE_SPEED, false);
  chassis.wait_drive();
  chassis.set_drive_pid(0.5 * T * AM, DRIVE_SPEED, false);
  chassis.wait_drive();
  chassis.set_drive_pid(-0.5* T * AM, DRIVE_SPEED, false);
  chassis.wait_drive();

  chassis.set_turn_pid(230, TURN_SPEED);
  chassis.wait_drive();
//from here?
  chassis.set_drive_pid(0.7 * T * AM, DRIVE_SPEED, false);
  chassis.wait_drive();
  intake.set_voltage(-constants::HIGH_VOLTAGE_INTAKE);
  chassis.set_turn_pid(280, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-2 * T * AM, DRIVE_SPEED, false);
  chassis.wait_drive();
  
  chassis.set_turn_pid(40, TURN_SPEED);
  chassis.wait_drive();
  
  chassis.set_drive_pid(-1 * T * AM, DRIVE_SPEED, false);
  chassis.wait_drive();
  
  chassis.set_drive_pid(1.5 * T * AM, DRIVE_SPEED, false);
  chassis.wait_drive();
  


}


// void auton_skills(Matchloader cata, Pneumatics wings){
//   chassis.set_angle(chassis.get_gyro());

//   // push alliance 1.5 tiles
//   chassis.set_drive_pid(T * AM * 1.5, false);
//   chassis.wait_drive();
//   // go back 
//   chassis.set_drive_pid(T * AM * -1.5, false);
//   chassis.wait_drive();
//   // go to matchload 
//   chassis.set_turn_pid(-10, TURN_SPEED);
//   chassis.wait_drive();

//   chassis.set_drive_pid(T * 0.10 * AM, DRIVE_SPEED, false);
//   chassis.wait_drive();

//   chassis.set_turn_pid(90, false);
//   chassis.wait_drive();

//   //actuall matchload code goes in this line
//   cata.bang_set_voltage(constants::HIGH_VOLTAGE_CATA); 
//   //wait for cata then uncata the cata
//   //wait
//   cata.bang_set_voltage(0);
//   // forward little
//   chassis.set_drive_pid(T * 3.5 * -1, DRIVE_SPEED, false);
//   chassis.wait_drive();
//   // now under barier  (UNDER??? OMG IS THAT AN OVER UNDER REFRENCE )
  
//   //turn left 
//   chassis.set_turn_pid(-45, TURN_SPEED);
//   chassis.wait_drive();

//   chassis.set_drive_pid(T * sqrt(2), DRIVE_SPEED, false);
//   chassis.wait_drive();

//   //face goal
//   chassis.set_turn_pid(0, TURN_SPEED);
//   chassis.wait_drive();

//   //pop wings 
//   wings.toggle_front_wings();
  

//   //push tribals into side goal
//   chassis.set_drive_pid(T, false);
//   chassis.wait_drive();

//   wings.toggle_front_wings();

//   //reverse last step **
//   chassis.set_drive_pid(T * -1, false);
//   chassis.wait_drive();

//   //turn into middle
//   chassis.set_turn_pid(-80, TURN_SPEED);
//   chassis.wait_drive();

//   //forward
//   chassis.set_drive_pid(T * 2 * AM, DRIVE_SPEED, false);
//   chassis.wait_drive();

//   //turn to forward goal 
//   chassis.set_turn_pid(0, TURN_SPEED);
//   chassis.wait_drive();

//   //pop wings
//   wings.toggle_front_wings();

//   //push tribals into front goal

//   //unpop wings

//   //** loop once

//   //*
//   //*

//   //do the last part 

// }


// void auton_skills(Matchloader cata, Pneumatics wings){
//   chassis.set_angle(chassis.get_gyro());
// /**
 

//   // push alliance 1.5 tiles
//   chassis.set_drive_pid(T * AM * 1.5, false);
//   chassis.wait_drive();
//   // go back 
//   chassis.set_drive_pid(T * AM * -1.5, false);
//   chassis.wait_drive();
//   // go to matchload 
//   chassis.set_turn_pid(-10, TURN_SPEED);
//   chassis.wait_drive();

//   chassis.set_drive_pid(T * 0.10 * AM, DRIVE_SPEED, false);
//   chassis.wait_drive();

//   chassis.set_turn_pid(90, false);
//   chassis.wait_drive();

//   //actuall matchload code goes in this line
//   cata.bang_set_voltage(constants::HIGH_VOLTAGE_CATA); 
//   //wait for cata then uncata the cata
//   //wait
//   cata.bang_set_voltage(0);
//   // forward little
//   chassis.set_drive_pid(T * 3.5 * -1, DRIVE_SPEED, false);
//   chassis.wait_drive();
//   // now under barier  (UNDER??? OMG IS THAT AN OVER UNDER REFRENCE )
  
//   //turn left 
//   chassis.set_turn_pid(-45, TURN_SPEED);
//   chassis.wait_drive();

//   chassis.set_drive_pid(T * sqrt(2), DRIVE_SPEED, false);
//   chassis.wait_drive();

//   //face goal
//   chassis.set_turn_pid(0, TURN_SPEED);
//   chassis.wait_drive();

//   //pop wings 
//   wings.toggle_front_wings();
  

//   //push tribals into side goal
//   chassis.set_drive_pid(T, false);
//   chassis.wait_drive();

//   wings.toggle_front_wings();

//   //reverse last step **
//   chassis.set_drive_pid(T * -1, false);
//   chassis.wait_drive();

//   //turn into middle
//   chassis.set_turn_pid(-80, TURN_SPEED);
//   chassis.wait_drive();

//   //forward
//   chassis.set_drive_pid(T * 2 * AM, DRIVE_SPEED, false);
//   chassis.wait_drive();

//   //turn to forward goal 
//   chassis.set_turn_pid(0, TURN_SPEED);
//   chassis.wait_drive();

//   //pop wings
//   wings.toggle_front_wings();

//   //push tribals into front goal
//   chassis.set_drive_pid(1.45 * T * AM, DRIVE_SPEED, false);
//   chassis.wait_drive();


//   //unpop wings
//   wings.toggle_front_wings();

//   //go back 
//   chassis.set_drive_pid(-1 * 1.45 * T * AM, DRIVE_SPEED, false);
//   chassis.wait_drive();

//   //turn 
//   chassis.set_turn_pid(-20, TURN_SPEED);
//   chassis.wait_drive();


//   //push again
//   chassis.set_drive_pid(0.8 * T, DRIVE_SPEED, false);
//   chassis.wait_drive();

//   //go out 
//   chassis.set_drive_pid(0.8 * T * -1, DRIVE_SPEED, false);
//   chassis.wait_drive();

//   //turn 
//   chassis.set_turn_pid(-90, TURN_SPEED);
//   chassis.wait_drive();
//   //go forward to the top of goal
//   chassis.set_drive_pid(1.5 * T, DRIVE_SPEED, false);
//   chassis.wait_drive();

//   chassis.set_turn_pid(90, TURN_SPEED);
//   chassis.wait_drive();

//   // pop wings 
//   wings.toggle_front_wings();


//   // push into top goal
//   chassis.set_drive_pid(1, DRIVE_SPEED, false);
//   chassis.wait_drive();

//   */
  

//   // fin

//   //simple 

//   //turn to matchload
//   chassis.set_turn_pid(-20, TURN_SPEED);
//   chassis.wait_drive();


//   //matchload
//   cata.set_voltage(constants::HIGH_VOLTAGE_CATA);
  
//   pros::delay(4500);//currently random time

//   cata.bang_set_voltage(0);

//   //face forward
//   chassis.set_turn_pid(0, TURN_SPEED);
//   chassis.wait_drive();

//   //go forward
//   chassis.set_drive_pid(1.5 * T * -1, DRIVE_SPEED, false);
//   chassis.wait_drive();


//   // turn right
//   chassis.set_turn_pid(20, TURN_SPEED);
//   chassis.wait_drive();

//   chassis.set_drive_pid(T * -1, DRIVE_SPEED, false);
//   chassis.wait_drive();

//   chassis.set_turn_pid(0, TURN_SPEED);
//   chassis.wait_drive();

//   // go under barrier 
//   chassis.set_drive_pid(3 * T * -1, DRIVE_SPEED);
//   chassis.wait_drive();

//   //line front with bottom goal

//   // ram
//   // ram again


// }

void beginning_match(Climb climb) {
  climb.set_voltage(10000); 
  pros::Task::delay(100); 
  climb.set_voltage(0); 
}


void close_disrupt(Pneumatics wings){
  chassis.set_angle(chassis.get_gyro());

  // wings.toggle_front_wings();
  // pros::Task::delay(500);
  // wings.toggle_front_wings();


  chassis.set_drive_pid(T * 2.45 * AM, DRIVE_SPEED * 1.1, true);
  chassis.wait_drive();

  wings.toggle_front_wings();

  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();

  

  chassis.set_drive_pid(1 * T * AM, DRIVE_SPEED, false);
  chassis.wait_drive();

  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();

  pros::Task::delay(500);
  wings.toggle_front_wings();


//   chassis.set_drive_pid(-0.8 * T * AM, DRIVE_SPEED, false); 
//   chassis.wait_drive(); 

//   chassis.set_turn_pid(45, TURN_SPEED);
//   chassis.wait_drive();

//   chassis.set_drive_pid(-2.5 * T * AM, DRIVE_SPEED, true);
//   chassis.wait_drive(); 

//   chassis.set_turn_pid(45, TURN_SPEED);
//   chassis.wait_drive(); 

// }
}