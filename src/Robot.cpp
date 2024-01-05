#include "Robot.hpp"

Robot::Robot(Intake intake_in, Catapult cata_in) :
intake {intake_in},
cata { cata_in}
{}; 

void Robot::update_intake() {
    int8_t R1_press = m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1); 
    int8_t R2_press = m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2);
    int8_t B_press = m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B);
        
        // turns intake on/off
        if (R1_press) {
            intake.toggle();
        }
        // switches direction arm spins (intaking vs deintaking)
        if (R2_press) {
            intake.switch_polarity(); 
        }
        // change speed
        if (B_press) {
            intake.move_level();
        }
        
        intake.set_voltage(intake.get_state() * intake.get_level()); // get level will return 0 or 1

    }

void Robot::update_cata() {
    // TODO: change this to a one button toggle?? and a state tracker or smth (like intake.switch_voltage())
    // TODO: test voltages for low and high range shots 
    if (m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
        intake.set_voltage(constants::HIGH_VOLTAGE_CATA);
    } 
    if (m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
        intake.set_voltage(0);
    } 

}
void Robot::update(std::string info) {
    update_intake();
}