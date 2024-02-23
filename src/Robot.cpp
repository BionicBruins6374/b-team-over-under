#include "Robot.hpp"
#include "main.h"

Robot::Robot(Drivetrain drive, Intake intake_in, Matchloader matcher_in, Pneumatics wingin) :
dt {drive},
intake {intake_in},
matchloader { matcher_in },
wings {wingin}
{}; 


void Robot::update_drivetrain() {
    dt.op_control(1, 
    m_controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X), 
    m_controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y),
    1,
    1);
}

// updates all aspects of intake
void Robot::update_intake() {   
    int8_t multiplier = 1; 
    // saves variables of different presses/states of the buttons (for more organization )
    int8_t R1_pressed = m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1);
    int8_t R1_pressing = m_controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1);  
    
    int8_t R2_pressed = m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2);
    int8_t R2_pressing = m_controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2);




    // sets intake direction to intake
    if (R1_pressing) {
        intake.set_state(true);
        intake.set_polarity(1); 
    }

    // sets intake to deintake
    else if (R2_pressing) {
        intake.set_state(true);
        intake.set_polarity(-1);
    }
    
    else {
        intake.set_state(false);
    }
    
    // sets the voltage to 0 if state = 0 (off), else sets voltage to the speed dictated by level * polarity (direction)
    intake.set_voltage(intake.get_state() * constants::HIGH_VOLTAGE_INTAKE * intake.get_polarity()); 

    }

// updates all aspects of Matchloader


void Robot::update_matchloader() {
    // if A is pressed 
    if (m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
        matchloader.toggle(); // toggle Matchloader 
        matchloader.set_speed(constants::HIGH_VOLTAGE_CATA); 
    
    } 
    // if B is pressed
    else if (m_controller.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
        // if (!matchloader.get_state() && (matchloader.get_speed() == constants::HIGH_VOLTAGE_CATA)) {
        //     matchloader.toggle(); 
        // }
        matchloader.set_state(true);
        matchloader.set_speed(constants::LOW_VOLTAGE_CATA);
     
    }
    if(matchloader.get_speed() == constants::LOW_VOLTAGE_CATA && !m_controller.get_digital(pros::E_CONTROLLER_DIGITAL_B)){
        matchloader.set_state(false);

    }

    if (m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
        matchloader.move_rel(-200);
    }


    matchloader.set_voltage(matchloader.get_state() * matchloader.get_speed()); 
    
}

void Robot::update_matchloader_temp() {

    if (m_controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
        matchloader.set_voltage(constants::HIGH_VOLTAGE_CATA);
    } 
    else {
        matchloader.set_voltage(0);
    }

}


// updates all aspects of wings 
void Robot::update_wings() {
    // if L1 is pressed 
    if (m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
        wings.toggle_back_wings();
    } 
    // if L2 is pressed 
    if (m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
        wings.toggle_front_wings(); 
    }
    // hang = X
    if (m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
        wings.toggle_hang();    
    }
}

// updates all components 
void Robot::update(std::string info) {
    update_intake();
    // update_matchloader(); 
    update_matchloader(); 
    update_wings();
    update_drivetrain(); 
    
    // printf("motor: %s", dt.get_left_motor_group());
    // master.print(0,0, "loader temp: %f", dt.get_left_motor_group() );
    // master.print(0, 0, "dt v: %d", chassis.get_tick_per_inch()); 
}
