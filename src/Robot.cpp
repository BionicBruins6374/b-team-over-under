#include "Robot.hpp"

Robot::Robot(Intake intake_in) :
intake {intake_in}
{}; 

void Robot::update_intake() {
    int8_t R1_press = m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1); 
    int8_t R2_press = m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2);
    int8_t B_press = m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B);
        
        if (R2_press) {
            intake.move_level();
        }
        if (R1_press) {
            if (intake.get_volt() != 0) {
                intake.set_voltage(0);
            }
            else {
                intake.set_voltage(intake.get_level());
            }
        }
        if (B_press) {
            intake.switch_polarity(); 
        }
    }

void Robot::update(std::string info) {
    update_intake();
}