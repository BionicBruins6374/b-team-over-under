#include "Robot.hpp"
#include "main.h"

Robot::Robot(Intake intake_in, Matchloader matcher_in, Wings wingin) :
intake {intake_in},
matchloader { matcher_in },
wings {wingin}
{}; 

// dampens turn speeds 
std::vector<double> Robot::dampen_turns(int left_velocity, int right_velocity) {
    // double total_dampen = constants::DAMPENING;
    double total_dampen = 1; 
    double left_dampen = 1; 
    double right_dampen = 1; 
    // if left and right velocity are 40% different (aka sharp turn, not just slight drift), dampen both sides by 0.85
    if (std::abs(left_velocity - right_velocity) > (constants::MAX_DT_VELOCITY * 0.7)) {
        // total_dampen *= constants::TURN_DAMPENING; 
        right_dampen *= constants::TURN_DAMPENING;
        left_dampen *= constants::TURN_DAMPENING;
    }

    // switches direction when wings are expanded--defunct for now
    /*
    if (wings.get_state()) {
        left_velocity *= -1;
        right_velocity *= -1; 
        int temp = left_velocity; 
        left_velocity = right_velocity;
        right_velocity = temp; 
    }
    */
    return {left_velocity * total_dampen, right_velocity * total_dampen};
    // return {left_velocity * left_dampen, right_velocity * right_dampen};

}
void Robot::update_drivetrain() {
    int additive = 0;
    // scales joystick inputs for arcade drive 
    int left_velocity = (m_controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) -  m_controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
    int right_velocity = m_controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) +  m_controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
    std::printf("Left: %d\n", left_velocity);
    std::printf("Right: %d\n\n", right_velocity); 
    pros::Task::delay(50);


    // std::printf("left y joystick: " + m_controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
    // std::printf("left x joystick: " + m_controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));

    // std::printf("left motor: " + chassis.left_velocity());
    // std::printf("right motor: " + chassis.right_velocity());


    // dampens raw speed 
    std::vector<double> dampened_velocities = this->dampen_turns(left_velocity, right_velocity);
    
    // sets left and right sides of the dt velocity 
    // if (std::abs(right_velocity - left_velocity ) < 8) {
    //     additive = 5; 
    // }
    // chassis.joy_thresh_opcontrol(left_velocity+ additive, right_velocity - additive);
    chassis.joy_thresh_opcontrol(dampened_velocities[0], dampened_velocities[1]);

    if (m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
        ram_lock =  !ram_lock; 
        // sets active braking to 0 (none) or 0.7 if (resistance to ramming) ram_lock mode is on
        // chassis.set_active_brake(ram_lock * 0.7); // ram_lock = false = 0
    }


}

// updates all aspects of intake
void Robot::update_intake() {   
    int8_t multiplier = 1; 
    // saves variables of different presses/states of the buttons (for more organization )
    int8_t R1_pressed = m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1);
    int8_t R1_pressing = m_controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1);  
    
    int8_t R2_pressed = m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2);
    int8_t R2_pressing = m_controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2);

    int8_t B_press = m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B);

    int8_t A_press = m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A);


 
    if (R1_pressed) {
        // intake.toggle(); 
       intake.set_polarity(1); 
    }
    // switches direction arm spins (intaking vs deintaking)
    if (R2_pressed) {
    //    intake.switch_polarity(); 
        intake.set_polarity(-1);
    }
     
    // change speed
    if (B_press) {
        intake.move_level();
    }

    if (A_press) {
        intake.toggle(); 
    }
    
    // sets the voltage to 0 if state = 0 (off), else sets voltage to the speed dictated by level * polarity (direction)
    intake.set_voltage(intake.get_state() * intake.get_level() * intake.get_polarity()); 

    }

// updates all aspects of Matchloader


void Robot::update_matchloader() {
    // if L1 is pressed 
    if (m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
        matchloader.toggle(); // toggle Matchloader 
    } 

    if (m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
        matchloader.switch_polarity();
    }
    
    // if (m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)){
    //     matchloader.toggle_arm(); }

    matchloader.bang_set_voltage(matchloader.get_state() * -1 * constants::HIGH_VOLTAGE_CATA);
    
}


// updates all aspects of wings 
void Robot::update_wings() {
    // if X is pressed 
    if (m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
        std::printf("update_wings");
        wings.toggle_wings();
    } 
    if (m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
        wings.toggle_arm(); 
    }
}

// updates all components 
void Robot::update(std::string info) {
    update_intake();
    update_matchloader(); 
    update_wings();
    update_drivetrain(); 
    // master.print(0,0, "loader temp: %f", matchloader.get_temp() );
    master.print(0, 0, "dt v: %d", chassis.get_tick_per_inch()); 
}
