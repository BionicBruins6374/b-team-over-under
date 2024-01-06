#include "Robot.hpp"

Robot::Robot(Intake intake_in, Catapult cata_in) :
intake {intake_in},
cata { cata_in}
{}; 

void Robot::update_intake() {   
    int8_t R1_pressed = m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1);
    int8_t R1_pressing = m_controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1);  
    int8_t R2_press = m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2);
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
    intake.toggle(R1_pressing); 
    // <--------------END TODO------------------->

    // switches direction arm spins (intaking vs deintaking)
    if (R2_press) {
        intake.switch_polarity(); 
    }
    // change speed
    if (B_press) {
        intake.move_level();
    }
        
        intake.set_voltage(intake.get_state() * intake.get_level()); // get state will return 0 or 1; TODO: need to check for get_level

    }

void Robot::update_cata() {
    // TODO: change this to a one button toggle?? and a state tracker or smth (like intake.switch_voltage())
    // TODO: test voltages for low and high range shots 
    if (m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
        intake.toggle();
    } 

}
void Robot::update(std::string info) {
    update_intake();
}