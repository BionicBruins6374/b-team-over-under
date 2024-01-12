#include "Robot.hpp"
#include "main.h"

Robot::Robot(Intake intake_in, Catapult cata_in, Wings wingin) :
intake {intake_in},
cata { cata_in},
wings {wingin}
{}; 

// dampens turn speeds 
std::vector<double> Robot::dampen_turns(int left_velocity, int right_velocity) {
    double total_dampen = constants::DAMPENING; 
    // if left and right velocity are 40% different (aka sharp turn, not just slight drift), dampen both sides by 0.85
    if (std::abs(left_velocity - right_velocity) > (constants::DAMPENING * constants::MAX_DT_VELOCITY * 0.4)) {
        total_dampen *= constants::TURN_DAMPENING; 
    }

    // if (wings.get_state()) {
    //     left_velocity *= -1;
    //     right_velocity *= -1; 
    //     int temp = left_velocity; 
    //     left_velocity = right_velocity;
    //     right_velocity = temp; 
    // }

    return {left_velocity * total_dampen, right_velocity * total_dampen};
}
void Robot::update_drivetrain() {
    // scales joystick inputs for arcade drive 
    int left_velocity = m_controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) -  m_controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
    int right_velocity = m_controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) +  m_controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
    // dampens raw speed 
    std::vector<double> dampened_velocities = this->dampen_turns(left_velocity, right_velocity);
    
    // sets left and right sides of the dt velocity 
    chassis.joy_thresh_opcontrol(dampened_velocities[0], dampened_velocities[1]);


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

// updates all aspects of catapult
void Robot::update_cata() {
    // if L1 is pressed 
    if (m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
        cata.toggle(); // toggle cata 
    } 

}

// updates all aspects of wings 
void Robot::update_wings() {
    // if X is pressed 
    if (m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
        std::printf("update_wings");
        wings.toggle_piston();
    } 
}

// updates all components 
void Robot::update(std::string info) {
    update_intake();
    update_cata(); 
    update_wings();
    update_drivetrain(); 
}