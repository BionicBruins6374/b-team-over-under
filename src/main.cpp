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
pros::Imu inertial_sensor(14); // port 2
 
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
    27, // proportional gain (kP)
    0, // integral gain (kI)
    26, // derivative gain (kD)
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
  chassis.setPose(0, 0, 0);

  pros::Task screenTask(screen); // create a task to print the position to the screen
  // Configure your chassis controls
  // lemlib::logger::setDebug(true);
  lemlib::infoSink()->info("Chassis pose: {}", chassis.getPose());
  // chassis.set_curve_default(4.2, 6.3); // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)  
  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // chassis.set_left_curve_buttons (pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT); // If using tank, only the left side is used. 
  // chassis.set_right_curve_buttons(pros::E_CONTROLLER_DIGITAL_Y,    pros::E_CONTROLLER_DIGITAL_A);
   
  
}


void disabled() {
  // . . .
}

void competition_initialize() {

  pros::lcd::initialize(); // initialize brain screen
  pros::delay(500); // Stop the user from doing anything while legacy ports configure.
  chassis.calibrate(); // calibrate the chassis
  chassis.setPose(0, 0, 0);

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
  Matchloader cata = Matchloader {18,20};

  

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
    chassis.arcade(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y), master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X), 2);
    pros::delay(10); // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
    robot.update("hi");
  }

}

void skills(Pneumatics wings) {
    // chassis.setPose(-55, -45, -90);
    chassis.setPose(0, 0, 0);

    // align wih alley
    chassis.moveToPose(-0.2, -0.67, -34, 500, {.forwards = true}); 

    chassis.moveToPose(-12.8, 18.5, -32, 500, {.forwards = true});

    chassis.moveToPose(-12, 17.5, -64.4, 500, {.forwards = true});

    chassis.moveToPose(-20.5, 21.8, -64.4, 750, {.forwards = true});
    
    chassis.moveToPose(-18, 20, -90, 500, {.forwards = true});

    // move through alley 
    chassis.moveToPose(-96, 23, -90, 2000, {.forwards = true});

    // align with corner 
    chassis.moveToPose(-100, 23, -125, 700, {.forwards = true});

    chassis.moveToPose(-110, 14.9, -125, 700, {.forwards = true});

    // ram 
    chassis.moveToPose(-110, 3.5, -175, 700, {.forwards = true, .minSpeed = 127, .earlyExitRange = 1.5});

    // go back
    chassis.moveToPose(-115, -1, -174, 3000, {.forwards = true, .minSpeed = 110});

    pros::delay(500);

    chassis.moveToPose(-115, -1, -174, 3000, {.forwards = true, .minSpeed = 127, .earlyExitRange = 1.5});

    pros::delay(500); 
    
    // ram again 
    chassis.moveToPoint(-115, 3.5, 3000, false, 127); // using moveToPoin to avoid all the fancy curvy shit of boomerang

    // go back 
    chassis.moveToPoint(-115, -1, 3000,true,127);

    // TURN CORNER 

    // turn towards 0,0
    chassis.turnTo(0,0, 1000, true, 90);

    // move forward T 
    chassis.moveToPoint(-115 + 16, -2, 3000, true); // using moveToPoin to avoid all the fancy curvy shit of boomerang

    wings.toggle_front_right(); 
    // swing turn
    chassis.moveToPose(-91, -20, -70, 3000, {.forwards = true, .minSpeed = 50}); // using moveToPoin to avoid all the fancy curvy shit of boomerang
    chassis.turnTo(-91, -18, 500, true); 


    // move forward (ram into goal) 
    // -86 -17.5 -98
    chassis.moveToPose(-100, -16.5, -98, 1000, {.forwards = true, .minSpeed = 127, .earlyExitRange = 1.5} );
    pros::delay(500); 
    // ????
    chassis.moveToPose(-101.9, -19, -90, 1000, {.forwards = true, .minSpeed = 127, .earlyExitRange = 1.5} );

    wings.toggle_front_right(); 

    // move away from goal
    chassis.moveToPose(-90, -19, -90, 1000, {.forwards = false, .minSpeed = 120});
    chassis.moveToPose(-84, -17, 90, 1000, {.forwards = true} ); // moves a little towards joola to curve well


    // spin 180 
    chassis.moveToPose(-86, -62, -90, 1000, {.forwards = true, .lead = 1.2} ); // need to tune 1.2

    wings.toggle_front_wings(); 

    // move forward
    chassis.moveToPose(-100, -62, 90, 1000, {.forwards = true, .minSpeed = 127, .earlyExitRange = 1.5});

    pros::delay(500); 

    // move back a bit
    chassis.moveToPose(-88, -62, 90, 1000, {.forwards = true, .minSpeed = 127, .earlyExitRange = 1.5});



}



void purple_6ball() {
     // backward: 0, -60
    chassis.setPose(0, -60, -90);
    // intake?? or push triball
    
    // 48 -60
    chassis.moveToPoint(45, -60, 3000, false, 127);
    // 62 -50, slower
    chassis.moveToPoint(62, -50, 3000, false, 100);
    pros::delay(500); 
    // 62 -24 
    chassis.moveToPoint(62, -24, 300,false, 127);
    // 4 -28
    chassis.moveToPoint(4, -28, 3000, true, 127 );
    // turn 75 deg slowly  (to 9,0)
    chassis.turnTo(9, 0, 1000); 
    // deintake
    // set turn to 0 slowish 
    // 4 0
    chassis.moveToPoint(4, 0, 3000, true, 127 );
    // 9 -8
    chassis.moveToPoint(9, -8, 3000, true, 127);
    // 48 -8
    chassis.moveToPoint(48, -8, 3000, true, 127 );
}


void autonomous() {
  
  Intake intake = Intake {ports::INTAKE_MOTOR};
  Pneumatics wings = Pneumatics {ports::WING_PORT_FRONT_RIGHT, ports::WING_PORT_FRONT_LEFT, ports::WING_PORT_BACK, ports::RATCHET};
  Matchloader matchloader = Matchloader {ports::BIG_CATAPULT_MOTOR,ports::SMALL_CATAPULT_MOTOR };
  Climb climb = Climb { ports::BIG_CATAPULT_MOTOR,ports::SMALL_CATAPULT_MOTOR, ports::ROTATIONAL_SENSOR }; 

  std::printf("delaying..");
  pros::Task::delay(500);

  // modified_exit_condition(); 
  // chassis.setPose(0, 0, 0);
  // example movement: Move to x: 20 and y: 15, and face heading 90. Timeout set to 4000 ms
  // chassis.moveToPose(0, 12, 127, 3000);
  // pros::delay(1000);
  // chassis.moveToPose(0, 0, 127, 3000, {.forwards = false});

  // chassis.turnTo(9, 0, 1000, 90); 
  // pros::delay(1000); 
  // chassis.turnTo(-9, 0, 1000, 90); 
  // lemlib::infoSink()->info("Chassis pose: {}", chassis.getPose());
  
  // chassis.follow("curve1.txt", 2000, 15, true);
  // example movement: Move to x: 0 and y: 0 and face heading 270, going backwards. Timeout set to 4000ms
  // chassis.moveToPose(0, 6, 270, 4000, {.forwards = false});
  // // cancel the movement after it has travelled 10 inches
  // // chassis.waitUntil(10);
  // // chassis.cancelMotion();
  //  chassis.moveToPose(0, 12, 270, 4000, {.forwards = false});
  // skills(wings);
  // purple_6ball();  
  // chassis.moveToPose(36, 25 * 0.5, 90, 2000 );
  // chassis.moveToPose(0,0, 0, 3000, {.forwards = false} );


}