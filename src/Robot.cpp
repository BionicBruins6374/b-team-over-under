#include "Robot.hpp"
#include "main.h"

Robot::Robot(Intake intake_in, Matchloader matcher_in, Pneumatics wingin) :
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
    
    return {left_velocity * left_dampen - left_lost * dampen_mag, right_velocity * right_dampen  - right_lost * dampen_mag };

}
void Robot::update_drivetrain() {
    /*
    these two if statements allow to toggle dampening on either side of the drivetrain
    if there's friction or a motor fallout, etc 
    */
    if (m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) {
        left_lost = !left_lost;
    } 
    if (m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) {
        right_lost = !right_lost; 
    } 

    // scales joystick inputs for arcade drive 
    int left_velocity = (m_controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) -  m_controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
    int right_velocity = m_controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) +  m_controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    // dampens raw speed 
    std::vector<double> dampened_velocities = this->dampen_turns(left_velocity, right_velocity);
    
    // updates drivetrain (chassis) speed 
    chassis.joy_thresh_opcontrol(-dampened_velocities[0], -dampened_velocities[1]);
    // chassis.arcade_standard(ez::SPLIT);

    // if up button is pressed, active braking is increased (basically an anti ram button for matchloading)
    if (m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
        ram_lock =  !ram_lock; 
        // sets active braking to 0 (none) or 0.7 if (resistance to ramming) ram_lock mode is on
        chassis.set_active_brake(ram_lock * 5); // ram_lock = false = 0
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
    intake.set_voltage(intake.get_state() * intake.get_level() * intake.get_polarity()); 

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
        matchloader.move_position(150);
    }


    // sets voltage input for matchloader
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
    // master.print(0,0, "loader temp: %f", matchloader.get_temp() );
    master.print(0, 0, "dt v: %d", chassis.get_tick_per_inch()); 
}
