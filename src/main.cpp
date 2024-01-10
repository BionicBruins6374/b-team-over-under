#include "main.h"
#include "ports.hpp"



// Chassis constructor DIRECTIONS ARE FORM FRONT
Drive chassis (
  // Left Chassis Ports (negative port will reverse it!)
  // RED AND GREEN = LEFT 
  // front, back-bottom, back-top 
  //   the first port is the sensored port (when trackers are not used!)
  {
  ports::LEFT_FRONT_DT,
  ports::LEFT_BACK_BOTTOM_DT,
  ports::RIGHT_BACK_TOP_DT}

  // Right Chassis Ports (negative port = reversed) 
  // ALL RED = RIGHT  
  //   the first port is the sensored port (when trackers are not used!)
  ,{
  ports::RIGHT_FRONT_DT,
  ports::RIGHT_BACK_BOTTOM_DT,
  ports::RIGHT_BACK_TOP_DT}

  // IMU Port
  ,ports::LEFT_BACK_BOTTOM_DT

  // Wheel Diameter (Remember, 4" wheels are actually 4.125!)
  //    (or tracking wheel diameter)
  ,3.25

  // Cartridge RPM
  //   (or tick per rotation if using tracking wheels)
  ,600

  // External Gear Ratio (MUST BE DECIMAL)
  //    (or gear ratio of tracking wheel)
  ,0.36 // 325/600 TODO
);



void autonomous() {
  chassis.reset_pid_targets(); // Resets PID targets to 0
  chassis.reset_gyro(); // Reset gyro position to 0
  chassis.reset_drive_sensor(); // Reset drive sensors to 0
  chassis.set_drive_brake(MOTOR_BRAKE_HOLD); // Set motors to hold.  This helps autonomous consistency.
  
  default_constants(); 
  drive_example(); 
  pros::Task::delay(3000);
  
  // chassis.joy_thresh_opcontrol(-90, -90);
  // pros::Task::delay(1000);
  
  // chassis.joy_thresh_opcontrol(0,0);
  // pros::Task::delay(100); 

  // chassis.joy_thresh_opcontrol(90, 90);
  // pros::Task::delay(400);

  // chassis.joy_thresh_opcontrol(0,0);
  // pros::Task::delay(100); 

  // chassis.joy_thresh_opcontrol(-90, -90);
  // pros::Task::delay(500);
  // chassis.joy_thresh_opcontrol(0, 0);


  // ez::as::auton_selector.call_selected_auton(); // Calls selected auton from autonomous selector.
}


void opcontrol() {
  // This is preference to what you like to drive on.
  chassis.set_drive_brake(MOTOR_BRAKE_COAST);
  Intake intake = Intake {ports::INTAKE_MOTOR};
  Catapult cata = Catapult {ports::SMALL_CATAPULT_MOTOR, ports::BIG_CATAPULT_MOTOR};
  Wings wings = Wings {ports::WING_PORT};
  Robot robot = Robot {intake, cata, wings}; 

  while (true) {

    pros::delay(ez::util::DELAY_TIME); // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
    robot.update("TESTING");
  }
}


void initialize() {
  // Print our branding over your terminal :D
  ez::print_ez_template();
  
  pros::delay(500); // Stop the user from doing anything while legacy ports configure.

  // Configure your chassis controls
  chassis.toggle_modify_curve_with_controller(true); // Enables modifying the controller curve with buttons on the joysticks
  chassis.set_active_brake(0.1); // Sets the active brake kP => magnitude of resistance to pushing
  chassis.set_curve_default(4.2, 6.3); // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)  
  default_constants(); // Set the drive to your own constants from autons.cpp!

  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // chassis.set_left_curve_buttons (pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT); // If using tank, only the left side is used. 
  // chassis.set_right_curve_buttons(pros::E_CONTROLLER_DIGITAL_Y,    pros::E_CONTROLLER_DIGITAL_A);

  // Autonomous Selector using LLEMU
  ez::as::auton_selector.add_autons({
    Auton("Example Drive\n\nDrive forward and come back.", drive_example),
    Auton("Example Turn\n\nTurn 3 times.", turn_example),
    Auton("Drive and Turn\n\nDrive forward, turn, come back. ", drive_and_turn),
    Auton("Drive and Turn\n\nSlow down during drive.", wait_until_change_speed),
    Auton("Swing Example\n\nSwing, drive, swing.", swing_example),
    Auton("Combine all 3 movements", combining_movements),
    Auton("Interference\n\nAfter driving forward, robot performs differently if interfered or not.", interfered_example),
  });

  // Initialize chassis and auton selector
  chassis.initialize();
  ez::as::initialize();
}


void disabled() {
  // . . .
}

void competition_initialize() {
  // . . .
}



