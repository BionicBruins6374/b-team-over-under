#include "Robot.hpp"
#include "main.h"

Robot::Robot(Intake intake_in, Catapult cata_in, Wings wingin) :
intake {intake_in},
cata { cata_in},
wings {wingin}
{}; 

void Robot::update_drivetrain() {
    int left_velocity = m_controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) -  m_controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
    int right_velocity = m_controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) +  m_controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    if (wings.get_state()) {
        left_velocity *= -1;
        right_velocity *= -1; 
        int temp = left_velocity; 
        left_velocity = right_velocity;
        right_velocity = temp; 
    }

    chassis.joy_thresh_opcontrol(left_velocity, right_velocity);



}

void Robot::update_intake() {   
    int8_t multiplier = 1; 
    int8_t R1_pressed = m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1);
    int8_t R1_pressing = m_controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1);  
    
    int8_t R2_press = m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2);
    int8_t R2_pressing = m_controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2);

    int8_t B_press = m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B);

    // <-----------------TODO SECTION------------------>
    // OPTION 1 
    /* intake_pressed_count += R1_pressed; 

    // if R1 was just pressed or just stopped being pressed, switch state
    if (R1_pressed ||( intake_pressed_count % 2 == 1 && !R1_pressing)) { // should it be just one or the other 
        intake.toggle();
    //     intake_pressed_count += 1; 
    } */

    // OPTION 2
    // sets intake power state to the state of the button being pressed--intake is on while button is pressed and held 
    intake.toggle(R1_pressing || R2_pressing); 
    // <--------------END TODO------------------->

    // switches direction arm spins (intaking vs deintaking)
    if (R2_pressing) {
        multiplier = -1; 
    }
     
    // change speed
    if (B_press) {
        intake.move_level();
    }
        
    intake.set_voltage(intake.get_state() * intake.get_level() * multiplier); // get state will return 0 or 1; TODO: need to check for get_level

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