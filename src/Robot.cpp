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
    chassis.joy_thresh_opcontrol(dampened_velocities[0], dampened_velocities[1]);
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

    int8_t B_press = m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B);

    int8_t A_press = m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A);


    // sets intake direction to intake
    if (R1_pressed) {
       intake.set_polarity(1); 
    }

    // sets intake to deintake
    if (R2_pressed) {
        intake.set_polarity(-1);
    }
     
    // change speed
    if (B_press) {
        intake.move_level();
    }

    // toggles (on and off intake)
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

    // if L2 is pressed, direction is switched 
    if (m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
        matchloader.switch_polarity();
        // zoya note: technically this doesn't do anything rn lmfao
    }
    

    // sets voltage input for matchloader--
    matchloader.set_voltage(matchloader.get_state() * -1 * constants::HIGH_VOLTAGE_CATA);
    
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
    // if X is pressed 
    if (m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
        wings.toggle_wings();
    } 
    // if Y is pressed 
    if (m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
        wings.toggle_hang(); 
    }
}

// updates all components 
void Robot::update(std::string info) {
    update_intake();
    // update_matchloader(); 
    update_matchloader_temp(); 
    update_wings();
    update_drivetrain(); 
    // master.print(0,0, "loader temp: %f", matchloader.get_temp() );
    master.print(0, 0, "dt v: %d", chassis.get_tick_per_inch()); 
}
