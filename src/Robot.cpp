#include "Robot.hpp"
#include "main.h"

Robot::Robot(Intake intake_in, Catapult cata_in, Wings wingin) :
intake {intake_in},
cata { cata_in},
wings {wingin}
{}; 

std::vector<double> Robot::dampen_turns(int left_velocity, int right_velocity) {
    double total_dampen = constants::DAMPENING; 
    if (std::abs(left_velocity - right_velocity) > (constants::DAMPENING * constants::MAX_DT_VELOCITY * 0.4)) {
        total_dampen *= constants::TURN_DAMPENING; 
    }

    // if left and right velociy are 40% different, dampen both sides by 0.85
    
    // if (wings.get_state()) {
    //     left_velocity *= -1;
    //     right_velocity *= -1; 
    //     int temp = left_velocity; 
    //     left_velocity = right_velocity;
    //     right_velocity = temp; 
    // }
    // dampen_turns(left_velocity, right_velocity); 

    return {left_velocity * total_dampen, right_velocity * total_dampen};
}
void Robot::update_drivetrain() {
    int left_velocity = m_controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) -  m_controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
    int right_velocity = m_controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) +  m_controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
    std::vector<double> dampened_velocities = this->dampen_turns(left_velocity, right_velocity);
    
    chassis.joy_thresh_opcontrol(dampened_velocities[0], dampened_velocities[1]);



}

void Robot::update_intake() {   
    int8_t multiplier = 1; 
    int8_t R1_pressed = m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1);
    int8_t R1_pressing = m_controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1);  
    
    int8_t R2_press = m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2);
    int8_t R2_pressing = m_controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2);

    int8_t B_press = m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B);

    int8_t A_press = m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A);



    if (R1_pressed) {
        // intake.toggle(); 
       intake.set_polarity(1); 
    }
    // switches direction arm spins (intaking vs deintaking)
    if (R2_press) {
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
        
    intake.set_voltage(intake.get_state() * intake.get_level() * intake.get_polarity()); // get state will return 0 or 1; TODO: need to check for get_level

    }

void Robot::update_cata() {
    // TODO: change this to a one button toggle?? and a state tracker or smth (like intake.switch_voltage())
    // TODO: test voltages for low and high range shots 
    if (m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
        cata.toggle();
    } 

}

void Robot::update_wings() {
    if (m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
        std::printf("update_wings");
        wings.toggle_piston();
    } 
}
void Robot::update(std::string info) {
    update_intake();
    update_cata(); 
    update_wings();
    update_drivetrain(); 
}