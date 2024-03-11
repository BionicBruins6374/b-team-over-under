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

pros::Motor_Group left_side_motors {{left_front_motor,left_middle_motor, left_back_motor}};
// left_side_motors.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
pros::Motor_Group right_side_motors = pros::Motor_Group{{right_front_motor, right_middle_motor, right_back_motor}};
// right_side_motors.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);


lemlib::Drivetrain drivetrain2(
  &left_side_motors, // left motor group
  &right_side_motors, // right motor group
  11, // 10 inch track width
  lemlib::Omniwheel::NEW_325, // using new 3.25" omnis
  450, // drivetrain rpm is 360
  2 // chase power is 2. If we had traction wheels, it would have been 8
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
    4 // maximum acceleration (slew)
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
    5 // maximum acceleration (slew)
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
  Pneumatics wings = Pneumatics {ports::WING_PORT_BACK, ports::WING_PORT_FRONT_RIGHT, ports::WING_PORT_FRONT_LEFT, ports::RATCHET};
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

  intake.set_state(true);
  left_side_motors.set_brake_modes(pros::E_MOTOR_BRAKE_BRAKE);
  right_side_motors.set_brake_modes(pros::E_MOTOR_BRAKE_BRAKE);

  Robot robot = Robot {dt, intake, cata, wings, climb}; 
  pros::delay(100); 
  // chassis.setPose(0, 0, 0);
  // reset matchloader encoders with matchloader up
  // std::uint32_t time = pros::millis();

  while (true) { 
    chassis.arcade(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y), master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X), 2);
    // chassis_ez.drive_brake_set(pros::E_MOTOR_BRAKE_HOLD);
    // chassis_ez.opcontrol_arcade_standard(ez::SPLIT);
    pros::delay(10); // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
    robot.update("hi");
  
  }

}


// rn this is starting after we intake triball btw 
void purple_6ball(Pneumatics wings, Intake intake) {
     // backward: 0, -60
     // 1.1 * 24 
    intake.set_voltage(12000); 
    chassis.setPose(0, -3, 0);
    // intake?? or push triball
    // // 0, -33, -2
    chassis.moveToPoint(0,0,0, 500); 
    pros::delay(400); 

    // moves it back to goal 
    chassis.moveToPose(0, -37.5, 0, 2000, {.forwards = false,
        .chasePower = 0,
        .lead = 0.1,
        .maxSpeed = 80,
        .minSpeed = 0,
        .earlyExitRange = 0});

        pros::delay(1000);
    // align with goal
    chassis.moveToPose(0, -39, -40, 1000 , {.forwards = false,
        .chasePower = 0,
        .lead = 0.1,
        .maxSpeed = 90,
        .minSpeed = 0,
        .earlyExitRange = 0});

    // move across bar
    chassis.moveToPoint(7, -43, 2000, false, 60);  
    pros::delay(500);  
    
    wings.toggle_front_right();
    // take out triball
    chassis.turnTo(32, -53, 2000, false, 120);
    pros::delay(500);
    wings.toggle_front_right();
    // back ram
    chassis.moveToPoint(34, -53, 1000, false);

    // make this a half task

    // 10.36 -53.39 -88.89

    pros::delay(500);
    // move back
    chassis.moveToPoint(20, -52, 2000, true);

    // ram with front to deintake
    chassis.turnTo(34,-52, 1000, true, 120);
    intake.set_voltage(-12000);
    pros::delay(100); 
    chassis.moveToPoint(34, -52, 2000, true, 120);


    intake.set_voltage(12000);

    // move back (for better angle)
    chassis.moveToPoint(15, -52, 2000, true);

    // move to close triball
    chassis.moveToPose(31, -2, 11, 2000,{.forwards = true,
        .chasePower = 0,
        .lead = 0.3,
        .maxSpeed = 127,
        .minSpeed = 120,
        .earlyExitRange = 0});

    pros::Task::delay(1000); 

    // turn to deintake 
    chassis.turnTo(41,-100, 1000, true, 127);
    intake.set_voltage(-12000);
    pros::delay(200); 

    // turn away
    chassis.turnTo(80,0, 1000, true, 127); 
     

    // // turn to second triball
    chassis.turnTo(47, -3, 1000, true, 127);
    chassis.moveToPoint(47 ,-3, 1000, true);

    // turn to slighter angle
    // chassis.moveToPoint( 60 + 24, -24 - 12, 1000, true);
    chassis.moveToPose(58, -34.6, 175, 1000,  {.forwards = true,
        .chasePower = 0,
        .lead = 0.1,
        .maxSpeed = 90,
        .minSpeed = 0,
        .earlyExitRange = 0} );
    // turn and move forward


  
   
}
void disrupt(Pneumatics wings, Intake intake){
  
  //set current as 0
  chassis.setPose(0,0,17);
  //intake on
  intake.set_voltage(12000);
  //move to the middle of the two sets of triballs
  chassis.moveToPose(13, 53, 26, 2000 , {
        .forwards = true,
        .chasePower = 0,
        .lead = 0.4,
        .maxSpeed = 127,
        .minSpeed = 0,
        .earlyExitRange = 0});
  chassis.turnTo(10,48,2000, 120);
  chassis.moveToPoint(10, 48, 2000, true, 120);
  pros::delay(250);
  //wings
  wings.toggle_front_left();
  wings.toggle_back_wings();
  //move back
  chassis.moveToPose(15, 49, 90, 1000 , {
    .forwards = false,
        .chasePower = 0,
        .lead = 0.4,
        .maxSpeed = 125,
        .minSpeed = 0,
        .earlyExitRange = 0});
  chassis.moveToPoint(36, 49, 2000, tru
  e);
  intake.set_voltage(-12000);
  pros::delay(500); 
  intake.set_voltage(0); 



}


void beginning_match(Climb climb) {
  climb.set_voltage(-10000); 
  pros::Task::delay(300); 
  climb.set_voltage(0); 
}

// utlizes this for coordinates (theyre on the bottom left of the field): https://lemlib.github.io/Path-Gen/
// void awp_short(Pneumatics wings, Intake intake) {
//   // init pos: 66 -50, 
//   chassis.setPose(0, 0, 135); // TODO: change this value based on how forward we need to be to stay in range  
//   // toggle front wings
//   wings.toggle_front_wings();
//   // turn to triball
//   chassis.turnTo(24,0, 1000, true, 127);
//   wings.toggle_front_wings();
//   //go to triball
//   chassis.moveToPose(24, 0, 135, 1000, {.forwards = true,
//         .chasePower = 0,
//         .lead = 0.1,
//         .maxSpeed = 67,
//         .minSpeed = 0,
//         .earlyExitRange = 0});
//  //turn oto back
//   chassis.turnTo(43,62, 1000, false, 127);
//   //move along the matchload bar
//   chassis.moveToPose(43, 62, 135, 1000, {.forwards = false,
//         .chasePower = 0,
//         .lead = 0.1,
//         .maxSpeed = 100,
//         .minSpeed = 0,
//         .earlyExitRange = 0});
//   // turn to goal
//   chassis.turnTo(53, 36, 1000, true, 127);
//   //ram once
//  chassis.moveToPose(57, 23, 135, 1000, {.forwards = true,
//         .chasePower = 0,
//         .lead = 0.1,
//         .maxSpeed = 100,
//         .minSpeed = 0,
//         .earlyExitRange = 0});
//   //turn to matchload bar
//   chassis.turnTo(64, 47, 1000, false, 127); 
//   //move to bar
//   chassis.moveToPose(64, 47, 135, 1000, {.forwards = false,
//         .chasePower = 0,
//         .lead = 0.6,
//         .maxSpeed = 100,
//         .minSpeed = 0,
//         .earlyExitRange = 0});
//   //toggle wings
//   wings.toggle_back_wings();
//   //turn
//   chassis.turnTo(48, 65, 1000, false);
//   // take triball out
//   chassis.moveToPose(48, 65, 0, 1000, {.forwards = false,
//         .chasePower = 0,
//         .lead = 0.6,
//         .maxSpeed = 100,
//         .minSpeed = 0,
//         .earlyExitRange = 0});
//   wings.toggle_back_wings();

//   chassis.turnTo(-3, 64, 1000, false);
//   chassis.moveToPose(-3, 64, 0, 1000, {.forwards = false,
//         .chasePower = 0,
//         .lead = 0.6,
//         .maxSpeed = 100,
//         .minSpeed = 0,
//         .earlyExitRange = 0});


// }

void awp_short(Pneumatics wings, Intake intake, Climb climb) {
  // init pos: 66 -50, 

     chassis.setPose(0, 0, 45); 

     chassis.moveToPoint(9.1, 8.5, 1000, true);

     chassis.turnTo(0, -20, 1000, false, 127);

    //  chassis.moveToPose(0.9, 0.9, 45, 1000, {
    //       .forwards = false,
    //       .chasePower = 0,
    //       .lead = 0.1,
    //       .maxSpeed = 127,
    //       .minSpeed = 0,
    //       .earlyExitRange = 0});

     wings.toggle_front_right();

     chassis.moveToPose(0, 0, 135, 1000, {
          .forwards = false,
          .chasePower = 0,
          .lead = 0.1,
          .maxSpeed = 127,
          .minSpeed = 60,
          .earlyExitRange = 0});


     chassis.turnTo(0, -20, 1000, false, 127);

     chassis.moveToPose(0, -15, 0, 1000, {
          .forwards = false,
          .chasePower = 0,
          .lead = 0.15,
          .maxSpeed = 127,
          .minSpeed = 60,
          .earlyExitRange = 0});

    wings.toggle_front_right();

    // 175 = front
    chassis.moveToPoint(0, -38,  5000, false, 90);

    intake.set_voltage(-12000);
    pros::Task::delay(2000);
    intake.set_voltage(0);


  climb.set_voltage(10000); 
  pros::delay(1700);
  climb.set_voltage(0);
}




void autonomous() {
  
  Intake intake = Intake {ports::INTAKE_MOTOR};
  Pneumatics wings = Pneumatics {ports::WING_PORT_BACK, ports::WING_PORT_FRONT_RIGHT, ports::WING_PORT_FRONT_LEFT, ports::RATCHET};
  Matchloader matchloader = Matchloader {ports::BIG_CATAPULT_MOTOR,ports::SMALL_CATAPULT_MOTOR };
  Climb climb = Climb {-ports::BIG_CATAPULT_MOTOR,ports::SMALL_CATAPULT_MOTOR, ports::ROTATIONAL_SENSOR  }; 

  std::printf("delaying..");
  pros::Task::delay(500);

  // modified_exit_condition(); 
  chassis.setPose(0, 0, 0);
  beginning_match(climb);
  // purple_6ball(wings, intake ); 
  // awp_short(wings, intake, climb); 
  disrupt(wings, intake); 
   


}
