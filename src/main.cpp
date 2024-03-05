#include "main.h"
#include "autons.hpp"
#include "ports.hpp"
#include "lemlib/api.hpp"



pros::Motor left_front_motor(ports::LEFT_FRONT_TOP_DT, pros::E_MOTOR_GEARSET_06); // port 1, blue gearbox, not reversed
pros::Motor left_middle_motor(ports::LEFT_FRONT_TOP_DT, pros::E_MOTOR_GEARSET_06); // port 1, blue gearbox, not reversed
pros::Motor left_back_motor(ports::LEFT_BACK_DT, pros::E_MOTOR_GEARSET_06); // port 2, green gearbox, not reversed
pros::Motor right_front_motor(ports::RIGHT_FRONT_TOP_DT, pros::E_MOTOR_GEARSET_06); // port 3, red gearbox, reversed
pros::Motor right_middle_motor(ports::RIGHT_FRONT_BOTTOM_DT, pros::E_MOTOR_GEARSET_06); // port 3, red gearbox, reversed
pros::Motor right_back_motor(ports::RIGHT_BACK_DT, pros::E_MOTOR_GEARSET_06); // port 4, red gearbox, reversed

pros::MotorGroup left_side_motors({left_front_motor,left_front_motor, left_back_motor});
pros::MotorGroup right_side_motors({right_front_motor, right_middle_motor, right_back_motor});

lemlib::Drivetrain_t drivetrain {
    &left_side_motors, // left drivetrain motors
    &right_side_motors, // right drivetrain motors
    11, // track 
    3.25, // wheel diameter
    450 // wheel rpm
};

// inertial sensor
pros::Imu inertial_sensor(1); // port 2
 
// odometry struct
lemlib::OdomSensors_t sensors {
    nullptr, // vertical tracking wheel 1
    nullptr, // vertical tracking wheel 2
    nullptr, // horizontal tracking wheel 1
    nullptr, // we don't have a second tracking wheel, so we set it to nullptr
    &inertial_sensor // inertial sensor
};

// forward/backward PID
lemlib::ChassisController_t lateralController {
    17, // kP
    60, // kD
    1, // smallErrorRange
    300, // smallErrorTimeout
    3, // largeErrorRange
    800, // largeErrorTimeout
    0 // slew rate
};
 
// turning PID
lemlib::ChassisController_t angularController {
    0, // kP
    0, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    0 // slew rate
};

// lemlib::Logger log {lemlib::logger::Level::debug};

lemlib::Chassis chassis(drivetrain, lateralController, angularController, sensors);

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
  chassis.calibrate(); // calibrate the chassis
  // pros::Task screenTask(screen); // create a task to print the position to the screen
  chassis.setPose(65, -35, -90); // X: 0, Y: 0, Heading: 0
  // chassis.setPose(5.2, 10.333, 87); // X: 5.2, Y: 10.333, Heading: 87
  
}


void disabled() {
  // . . .
}

void competition_initialize() {
  // . . .
}





void opcontrol() {
  // lemlib::Drivetrain_t dt {
  //   &left_side_motors, 
  //   &right_side_motors, 
  //   11, // track 
  //   3.25, // wheel diameter
  //   450 // wheel rpm}
  // }; 
  // This is preference to what you like to drive on.

  // chassis.set_drive_brake(MOTOR_BRAKE_BRAKE);
  // chassis.arcade_standard(ez::SPLIT); 

  // Defines components 
  Intake intake = Intake {ports::INTAKE_MOTOR};
  Matchloader cata = Matchloader {ports::BIG_CATAPULT_MOTOR,ports::SMALL_CATAPULT_MOTOR };
  Pneumatics wings = Pneumatics {ports::WING_PORT_BACK, ports::WING_PORT_FRONT, ports::RATCHET};
  Drivetrain dt = Drivetrain {
 
  ports::RIGHT_FRONT_TOP_DT,
  ports::RIGHT_FRONT_BOTTOM_DT,
  ports::RIGHT_BACK_DT,

   ports::LEFT_BACK_DT,
  ports::LEFT_FRONT_BOTTOM_DT, 
  ports::LEFT_FRONT_TOP_DT  };

  Climb climb = Climb { ports::BIG_CATAPULT_MOTOR,ports::SMALL_CATAPULT_MOTOR }; 

  Robot robot = Robot {dt, intake, cata, wings, climb}; 
  int time = 0;
  while (true) { 

    robot.update("TESTING");

    if(time == 129.5 * 100) //when one second is left
    {
      wings.toggle_hang();
    }

    time++;

}

}

void autonomous() {
  Intake intake = Intake {ports::INTAKE_MOTOR};
  Pneumatics wings = Pneumatics {ports::WING_PORT_BACK, ports::WING_PORT_FRONT, ports::RATCHET};
  Matchloader matchloader = Matchloader {ports::BIG_CATAPULT_MOTOR,ports::SMALL_CATAPULT_MOTOR };
  Climb climb = Climb { ports::BIG_CATAPULT_MOTOR,ports::SMALL_CATAPULT_MOTOR }; 

    pros::Task::delay(2000);
  std::printf("delaying..");


  chassis.setPose(0, 0, 0);

  std::printf("move..\n");
  chassis.moveTo(0, 12, 2000); // move to the point (10, 0) with a timeout of 1000 ms, and a maximum speed of 50
  std::printf("Done moving");
  pros::delay(1500);
  chassis.moveTo(0, 0, 2000, false); 
  // pros::delay(500);

  // chassis.turnTo(53, 53, 1000); // turn to the point (53, 53) with a timeout of 1000 ms
  //   pros::delay(1000);
  // chassis.turnTo(0, 0, 1000); // turn to the point (53, 53) with a timeout of 1000 ms

  // 6, 3
  // chassis.moveTo(11, 0, 2000, 50);

  // modified_exit_condition(); 


}