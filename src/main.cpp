#include "main.h"
#include "autons.hpp"
#include "ports.hpp"


// Chassis constructor DIRECTIONS ARE FORM FRONT
Drive chassis (
  // Left Chassis Ports (negative port will reverse it!)
  // RED AND GREEN = LEFT 
  // front, back-bottom, back-top 
  //   the first port is the sensored port (when trackers are not used!)
 
 
  // Right Chassis Ports (negative port = reversed) 
  // ALL RED = RIGHT  
  //   the first port is the sensored port (when trackers are not used!)
 

  {  
   -ports::LEFT_BACK_DT,
  -ports::LEFT_FRONT_BOTTOM_DT,
  -ports::RIGHT_FRONT_TOP_DT
  }
 
  // Right Chassis Ports (negative port = reversed) 
  // ALL RED = RIGHT  
  //   the first port is the sensored port (when trackers are not used!)
  ,{ 
    -ports::RIGHT_FRONT_TOP_DT,
    -ports::RIGHT_FRONT_BOTTOM_DT,
    -ports::RIGHT_BACK_DT
   
  }
  
  // IMU Port
  ,12

  // Wheel Diameter (Remember, 4" wheels are actually 4.125!)
  //    (or tracking wheel diameter)
  ,3.25

  // Cartridge RPM
  //   (or tick per rotation if using tracking wheels)
  ,600

  // External Gear Ratio (MUST BE DECIMAL)
  //    (or gear ratio of tracking wheel)
  ,1 
);


void initialize() {
  // Print our branding over your terminal :D
  ez::print_ez_template();
  
  pros::delay(500); // Stop the user from doing anything while legacy ports configure.

  // Configure your chassis controls
  chassis.toggle_modify_curve_with_controller(false); // Enables modifying the controller curve with buttons on the joysticks
  chassis.set_active_brake(0); // Sets the active brake kP => magnitude of resistance to pushing
  chassis.set_curve_default(4.2, 6.3); // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)  
  default_constants(); // Set the drive to your own constants from autons.cpp!

  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // chassis.set_left_curve_buttons (pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT); // If using tank, only the left side is used. 
  // chassis.set_right_curve_buttons(pros::E_CONTROLLER_DIGITAL_Y,    pros::E_CONTROLLER_DIGITAL_A);
   
  // Autonomous Selector using LLEMU
  ez::as::auton_selector.add_autons({
    Auton("Example Drive\n\nDrive forward and come back.", drive_example),
    Auton("Example Turn\n\nTurn 3 times.", turn_example),
    Auton("Drive and Turn\n\nDrive forward, turn, come back. ", drive_and_turn)
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



void autonomous() {
  chassis.reset_pid_targets(); // Resets PID targets to 0
  chassis.reset_gyro(); // Reset gyro position to 0
  chassis.reset_drive_sensor(); // Reset drive sensors to 0
  chassis.set_drive_brake(MOTOR_BRAKE_HOLD); // Set motors to hold.  This helps autonomous consistency.
  default_constants();

  Intake intake = Intake {ports::INTAKE_MOTOR};
  Pneumatics wings = Pneumatics {ports::WING_PORT_RIGHT, ports::WING_PORT_LEFT, 'A', 'B', 'C', 'D'};
  Matchloader matchloader = Matchloader {ports::BIG_CATAPULT_MOTOR,ports::SMALL_CATAPULT_MOTOR };
 

  std::printf("delaying..");
  pros::Task::delay(500);

  modified_exit_condition(); 

  //offensive_x3(intake, wings);
  // defensive_triballA(intake, pneumatics)
  // offensive_new(intake, pneumatics );
  // intake.set_voltage(12000); 
  // drive_example(); 
  // skills_ez(matchloader, wings);
  // defensive_triball(intake, pneumatics);
  // alliance_triball();
  // defence_auton(pneumatics);
  // skills_triball(wings, matchloader); 
  // matchloader.set_voltage(12000);
  // matchloader.move_position(-1200);  // * 6
  // hwanseo_offensive(intake, wings);
  // auton_skills(matchloader, wings); 

  // awp_diff(wings, intake); 

  awp_short(wings, intake); 

  //offensive_4ball(wings, intake);

}

void opcontrol() {
  // This is preference to what you like to drive on.

  chassis.set_drive_brake(MOTOR_BRAKE_BRAKE);
  chassis.arcade_standard(ez::SPLIT); 

  // Defines components 
  Intake intake = Intake {ports::INTAKE_MOTOR};
  Matchloader cata = Matchloader {ports::BIG_CATAPULT_MOTOR,ports::SMALL_CATAPULT_MOTOR };
  Pneumatics wings = Pneumatics {ports::WING_PORT_RIGHT, ports::WING_PORT_LEFT, 'A', 'B', 'C', 'D'};
  Drivetrain dt = Drivetrain {
  -ports::LEFT_BACK_DT,
  -ports::LEFT_FRONT_BOTTOM_DT, 
  -ports::RIGHT_FRONT_TOP_DT,  
  -ports::RIGHT_FRONT_TOP_DT,
  -ports::RIGHT_FRONT_BOTTOM_DT,
  -ports::RIGHT_BACK_DT};

  Robot robot = Robot {dt, intake, cata, wings}; 

  // reset matchloader encoders with matchloader up
  while (true) { 

    pros::delay(ez::util::DELAY_TIME); // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
    robot.update("TESTING");
  }

}
// void skills () {
//   chassis.set_drive_brake(MOTOR_BRAKE_BRAKE);
//   // Defines components 
//   Intake intake = Intake {ports::INTAKE_MOTOR};
//   Matchloader cata = Matchloader {ports::BIG_CATAPULT_MOTOR,ports::SMALL_CATAPULT_MOTOR };
//   // Pneumatics wings = Pneumatics {ports::WING_PORT_RIGHT, ports::WING_PORT_LEFT, ports::ARM_PORT};
//   // Robot robot = Robot {intake, cata, wings}; 
//   // skills_triball();
//   while (true) { 

//   pros::delay(ez::util::DELAY_TIME); // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
//   robot.update("TESTING");
//   }
// }
void test_motor(int8_t port_num) {
    pros::Motor mot = pros::Motor{port_num}; 
    mot.move_voltage(12000);
} 

void timer() {
  int count = 0; 
  while (true) {
  chassis.joy_thresh_opcontrol(50,0); 
  pros::Task::delay(1);
  master.print(0,0, "count: %d", count);
  }
}
