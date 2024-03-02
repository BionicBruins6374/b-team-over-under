#include "main.h"
#include "autons.hpp"
#include "ports.hpp"
#include "lemlib/api.hpp"



pros::Motor left_front_motor(1, pros::E_MOTOR_GEARSET_06, false); // port 1, blue gearbox, not reversed
pros::Motor left_back_motor(2, pros::E_MOTOR_GEARSET_18, false); // port 2, green gearbox, not reversed
pros::Motor right_front_motor(3, pros::E_MOTOR_GEARSET_36, true); // port 3, red gearbox, reversed
pros::Motor right_back_motor(4, pros::E_MOTOR_GEARSET_36, true); // port 4, red gearbox, reversed

pros::MotorGroup left_side_motors({left_front_motor, left_back_motor});
pros::MotorGroup right_side_motors({right_front_motor, right_back_motor});

lemlib::Drivetrain_t drivetrain {
    &left_side_motors, // left drivetrain motors
    &right_side_motors, // right drivetrain motors
    11, // track 
    3.25, // wheel diameter
    450 // wheel rpm
};

// inertial sensor
pros::Imu inertial_sensor(2); // port 2
 
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
    8, // kP
    30, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    5 // slew rate
};
 
// turning PID
lemlib::ChassisController_t angularController {
    4, // kP
    40, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    0 // slew rate
};

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
  pros::Task screenTask(screen); // create a task to print the position to the screen
  
  chassis.setPose(0, 0, 0); // X: 0, Y: 0, Heading: 0
  // chassis.setPose(5.2, 10.333, 87); // X: 5.2, Y: 10.333, Heading: 87
  
}


void disabled() {
  // . . .
}

void competition_initialize() {
  // . . .
}



void autonomous() {
  

  Intake intake = Intake {ports::INTAKE_MOTOR};
  Pneumatics wings = Pneumatics {ports::WING_PORT_BACK, ports::WING_PORT_FRONT, ports::RATCHET};
  Matchloader matchloader = Matchloader {ports::BIG_CATAPULT_MOTOR,ports::SMALL_CATAPULT_MOTOR };
  Climb climb = Climb { ports::BIG_CATAPULT_MOTOR,ports::SMALL_CATAPULT_MOTOR }; 

  std::printf("delaying..");
  pros::Task::delay(500);

  // modified_exit_condition(); 

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
  // beginning_match(climb); 
  // awp_short(wings, intake); 
  // close_disrupt(wings);
  // alliance_triball(); 

  //offensive_4ball(wings, intake);

}

void opcontrol() {
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

void test_motor(int8_t port_num) {
    pros::Motor mot = pros::Motor{port_num}; 
    mot.move_voltage(12000);
} 

void timer() {
  int count = 0; 
  while (true) {
  pros::Task::delay(1);
  }
}
