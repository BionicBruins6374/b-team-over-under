#include "main.h"
#include "autons.hpp"
#include "ports.hpp"
#include "lemlib/api.hpp"

pros::Controller master {pros::E_CONTROLLER_MASTER}; 


pros::Motor left_front_motor(ports::LEFT_FRONT_TOP_DT, pros::E_MOTOR_GEARSET_06); // port 1, blue gearbox, not reversed
pros::Motor left_middle_motor(ports::LEFT_FRONT_BOTTOM_DT, pros::E_MOTOR_GEARSET_06); // port 1, blue gearbox, not reversed
pros::Motor left_back_motor(ports::LEFT_BACK_DT, pros::E_MOTOR_GEARSET_06); // port 2, green gearbox, not reversed

pros::Motor right_front_motor(ports::RIGHT_FRONT_TOP_DT, pros::E_MOTOR_GEARSET_06); // port 3, red gearbox, reversed
pros::Motor right_middle_motor(ports::RIGHT_FRONT_BOTTOM_DT, pros::E_MOTOR_GEARSET_06); // port 3, red gearbox, reversed
pros::Motor right_back_motor(ports::RIGHT_BACK_DT, pros::E_MOTOR_GEARSET_06); // port 4, red gearbox, reversed

pros::MotorGroup left_side_motors({left_front_motor,left_middle_motor, left_back_motor});
pros::MotorGroup right_side_motors({right_front_motor, right_middle_motor, right_back_motor});

lemlib::Drivetrain drivetrain2(
  &left_side_motors, // left motor group
  &right_side_motors, // right motor group
  11, // 10 inch track width
  lemlib::Omniwheel::NEW_325, // using new 3.25" omnis
  450, // drivetrain rpm is 360
  4 // chase power is 2. If we had traction wheels, it would have been 8
);

// inertial sensor
pros::Imu inertial_sensor(10); // port 2
 
// odometry struct
lemlib::OdomSensors sensors {
    nullptr, // vertical tracking wheel 1
    nullptr, // vertical tracking wheel 2
    nullptr, // horizontal tracking wheel 1
    nullptr, // we don't have a second tracking wheel, so we set it to nullptr
    &inertial_sensor // inertial sensor
    // nullptr
};

// forward/backward PID
lemlib::ControllerSettings lateralController {
    14, // proportional gain (kP)
    0, // integral gain (kI)
    29, // derivative gain (kD)
    3, // anti windup
    1, // small error range, in inches
    100, // small error range timeout, in milliseconds
    3, // large error range, in inches
    500, // large error range timeout, in milliseconds
    5 // maximum acceleration (slew)
};
 
// turning PID
lemlib::ControllerSettings angularController {
    1.85, // kP
    0, // integral gain (kI)
    11, // derivative gain (kD)
    3, // anti windup
    1, // small error range, in inches
    100, // small error range timeout, in milliseconds
    3, // large error range, in inches
    500, // large error range timeout, in milliseconds
    2 // maximum acceleration (slew)
};


// lemlib::Logger log {lemlib::logger::Level::debug};

lemlib::Chassis chassis(drivetrain2, lateralController, angularController, sensors);

// Drive chassis_ez (
//   // Left Chassis Ports (negative port will reverse it!)
//   // RED AND GREEN = LEFT 
//   // front, back-bottom, back-top 
//   //   the first port is the sensored port (when trackers are not used!)
 
 
//   // Right Chassis Ports (negative port = reversed) 
//   // ALL RED = RIGHT  
//   //   the first port is the sensored port (when trackers are not used!)
 
//   // { 
//   //   ports::RIGHT_FRONT_TOP_DT,
//   //   ports::RIGHT_FRONT_BOTTOM_DT,
//   //   ports::RIGHT_BACK_DT
   
//   // },

//   {  
//   -ports::LEFT_BACK_DT,
//   -ports::LEFT_FRONT_BOTTOM_DT,
//   -ports::LEFT_FRONT_TOP_DT
//   }
 
//   // Right Chassis Ports (negative port = reversed) 
//   // ALL RED = RIGHT  
//   //   the first port is the sensored port (when trackers are not used!)
//   ,{ 
//     ports::RIGHT_FRONT_TOP_DT,
//     ports::RIGHT_FRONT_BOTTOM_DT,
//     ports::RIGHT_BACK_DT
   
//   }
  
//   // IMU Port
//   ,11

//   // Wheel Diameter (Remember, 4" wheels are actually 4.125!)
//   //    (or tracking wheel diameter)
//   ,3.25

//   // Cartridge RPM
//   //   (or tick per rotation if using tracking wheels)
//   ,600 

//   // External Gear Ratio (MUST BE DECIMAL)
//   //    (or gear ratio of tracking wheel)
//   ,0.75 //36/48 * 600
// );

void screen() {
    // loop forever
    while (true) {
        lemlib::Pose pose = chassis.getPose(); // get the current position of the robot
        pros::lcd::print(0, "x: %f", pose.x); // print the x position
        pros::lcd::print(1, "y: %f", pose.y); // print the y position
        pros::lcd::print(2, "heading: %f", pose.theta); // print the heading
        pros::delay(10);
    }
}

void initialize() {
  // Print our branding over your terminal :D
  pros::lcd::initialize(); // initialize brain screen
  pros::delay(500); // Stop the user from doing anything while legacy ports configure.
  chassis.calibrate(); // calibrate the chassis
  // chassis.setPose(0, 0, 0);

  pros::Task screenTask(screen); // create a task to print the position to the screen
  // Configure your chassis controls
  // lemlib::logger::setDebug(true);
  lemlib::infoSink()->info("Chassis pose: {}", chassis.getPose());
  // chassis.set_curve_default(4.2, 6.3); // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)  
  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // chassis.set_left_curve_buttons (pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT); // If using tank, only the left side is used. 
  // chassis.set_right_curve_buttons(pros::E_CONTROLLER_DIGITAL_Y,    pros::E_CONTROLLER_DIGITAL_A);
  pros::ADIAnalogIn sensor (ports::ROTATIONAL_SENSOR);
  sensor.calibrate();
}


void disabled() {
  // . . .
}

void competition_initialize() {

  pros::lcd::initialize(); // initialize brain screen
  pros::delay(500); // Stop the user from doing anything while legacy ports configure.
  chassis.calibrate(); // calibrate the chassis
  // chassis.setPose(0, 0, 0);

  pros::Task screenTask(screen); // 

  // . . .
}





void opcontrol() {
  // This is preference to what you like to drive on.

  // chassis.set_drive_brake(MOTOR_BRAKE_BRAKE);
  // chassis.arcade_standard(ez::SPLIT); 

  // Defines components 
  Intake intake = Intake {ports::INTAKE_MOTOR};
  // Matchloader cata = Matchloader {ports::BIG_CATAPULT_MOTOR,ports::SMALL_CATAPULT_MOTOR };
  Pneumatics wings = Pneumatics {ports::WING_PORT_FRONT_RIGHT, ports::WING_PORT_FRONT_LEFT, ports::WING_PORT_BACK, ports::RATCHET};
  Climb climb = Climb {-ports::BIG_CATAPULT_MOTOR,ports::SMALL_CATAPULT_MOTOR, ports::ROTATIONAL_SENSOR  }; 
  // Climb climb = Climb {18, 20 }; 
  Matchloader cata = Matchloader {18,19};

  

  Drivetrain dt = Drivetrain {
 
  ports::RIGHT_FRONT_TOP_DT,
  ports::RIGHT_FRONT_BOTTOM_DT,
  ports::RIGHT_BACK_DT,

   ports::LEFT_BACK_DT,
  ports::LEFT_FRONT_BOTTOM_DT, 
  ports::LEFT_FRONT_TOP_DT  };

  // intake.set_state(true);
  Robot robot = Robot {dt, intake, cata, wings, climb}; 
  pros::delay(100); 
  chassis.setPose(0, 0, 0);
  // reset matchloader encoders with matchloader up
  int time = 0;
  while (true) { 
    // chassis.arcade(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y), master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X), 2);
    // chassis_ez.opcontrol_arcade_standard(ez::SPLIT);
    pros::delay(10); // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
    robot.update("hi");
  }

}


// rn this is starting after we intake triball btw 
void purple_6ball(Pneumatics wings, Intake intake) {
     // backward: 0, -60
    chassis.setPose(0, 0, 0);
    // intake?? or push triball
    // 0, -33, -2
    chassis.moveToPose(0, -33, 0, 2000, {.forwards = false,
        .chasePower = 0,
        .lead = 0.6,
        .maxSpeed = 127,
        .minSpeed = 0,
        .earlyExitRange = 0});
    // 2 -36 -45
    chassis.moveToPose(0, -33, -45, 2000, {.forwards = false,
        .chasePower = 0,
        .lead = 0.6,
        .maxSpeed = 127,
        .minSpeed = 0,
        .earlyExitRange = 0});
    // 13.5 -48 -42
    chassis.moveToPose(13.5, -44, -42, 2000, {.forwards = false,
        .chasePower = 0,
        .lead = 0.6,
        .maxSpeed = 127,
        .minSpeed = 0,
        .earlyExitRange = 0});


    // 30 -50 -90 
    // chassis.moveToPose(30, -50, -90, 2000,{.forwards = false,
    //     .chasePower = 0,
    //     .lead = 0.6,
    //     .maxSpeed = 127,
    //     .minSpeed = 120,
    //     .earlyExitRange = 0});

    // chassis.moveToPose(25, -50, -90, 2000,{.forwards = false,
    //     .chasePower = 0,
    //     .lead = 0.6,
    //     .maxSpeed = 127,
    //     .minSpeed = 120,
    //     .earlyExitRange = 0});

    // chassis.moveToPose(9.4, 7.8, 0, 2000, {.forwards = false,
    //     .chasePower = 0,
    //     .lead = 0.3,
    //     .maxSpeed = 127,
    //     .minSpeed = 0,
    //     .earlyExitRange = 0});
   
}

void awp_short(Pneumatics wings, Intake intake) {
  // init pos: 66 -50, 
  chassis.setPose(66, -50, 135); // TODO: change this value based on how forward we need to be to stay in range  

  //move along the matchload bar
  chassis.moveToPose(50, -64, 135, 1000, {.forwards = false,
        .chasePower = 0,
        .lead = 0.1,
        .maxSpeed = 67,
        .minSpeed = 0,
        .earlyExitRange = 0});
  
  // pop wings 
  wings.toggle_back_wings(); 
  // turn to climb bar (and take out triball) 
  // x, y, timeout, maxSpeed 
  chassis.turnTo(0, -64, 1000, true, 127);

  // move to climb bar intake facing front: 0 -64
  chassis.moveToPose(0, -64, 0, 1000, {.forwards = true,
        .chasePower = 0,
        .lead = 0.6,
        .maxSpeed = 100,
        .minSpeed = 0,
        .earlyExitRange = 0});

}


void autonomous() {
  
  Intake intake = Intake {ports::INTAKE_MOTOR};
  Pneumatics wings = Pneumatics {ports::WING_PORT_FRONT_RIGHT, ports::WING_PORT_FRONT_LEFT, ports::WING_PORT_BACK, ports::RATCHET};
  Matchloader matchloader = Matchloader {ports::BIG_CATAPULT_MOTOR,ports::SMALL_CATAPULT_MOTOR };
  Climb climb = Climb { ports::BIG_CATAPULT_MOTOR,ports::SMALL_CATAPULT_MOTOR, ports::ROTATIONAL_SENSOR }; 

  std::printf("delaying..");
  pros::Task::delay(500);

  // modified_exit_condition(); 
  chassis.setPose(0, 0, 0);
 
  purple_6ball(wings, intake ); 
  awp_short(wings, intake); 



}