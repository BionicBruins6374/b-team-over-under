#include "Robot.hpp"
#include "main.h"

Robot::Robot(Drivetrain drive, Intake intake_in, Matchloader matcher_in, Pneumatics wingin, Climb climb_in) :
dt {drive},
intake {intake_in},
matchloader { matcher_in },
wings {wingin},
climb {climb_in}
{}; 


void Robot::update_drivetrain() {

     // scales joystick inputs for arcade drive 
    int left_velocity = (m_controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) -  m_controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
    int right_velocity = m_controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) +  m_controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    // dampens raw speed 
    std::vector<double> dampened_velocities = {left_velocity * 200.0/127.0, right_velocity * 200.0/127.0};
    
    // updates drivetrain (chassis) speed 
    // chassis.joy_thresh_opcontrol(dampened_velocities[1], dampened_velocities[0]);
    // chassis.arcade_standard(ez::SPLIT);

    dt.op_control(0, 
    m_controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y), 
    m_controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X),
    1,
    1,
    1);
    
}


// updates all aspects of intake
void Robot::update_intake() {   
    int8_t multiplier = 1; 
    // saves variables of different presses/states of the buttons (for more organization )
    int8_t A_pressed = m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A);
    int8_t R1_pressing = m_controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1);  
    
    int8_t R2_pressed = m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2);
    int8_t R2_pressing = m_controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2);

    if (A_pressed) {
        intake.toggle();
    }

    // sets intake to deintake
    if (R2_pressing) {
        intake.set_polarity(-1);
    }

    else {
        intake.set_polarity(1);
    }
    
    // sets the voltage to 0 if state = 0 (off), else sets voltage to the speed dictated by level * polarity (direction)
    intake.set_voltage(intake.get_state() * constants::HIGH_VOLTAGE_INTAKE * intake.get_polarity()); 

    }

// updates all aspects of Matchloader


void Robot::update_climb() {
    // if up is pressed 
    if (m_controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
        climb.toggle(); // toggle Matchloader 
        climb.set_speed(constants::HIGH_VOLTAGE_CATA); 
    
    } 
    // if down is pressed
    if (m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {

        climb.toggle();
        climb.set_speed(-constants::HIGH_VOLTAGE_CATA);
     
    }
    // if(climb.get_speed() == constants::HIGH_VOLTAGE_CATA && !m_controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)){
    //     climb.set_state(false);

    // }
    //   if(climb.get_speed() == constants::HIGH_VOLTAGE_CATA && !m_controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)){
    //     climb.set_state(false);

    // }

    // if (m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
    //      pros::Task task{[=] {
    //         climb.move_position(1000);
    // }};
    // }

    // else{
    // climb.set_voltage(climb.get_state() * climb.get_speed()); 
    // }
    
    climb.set_voltage(climb.get_state() * climb.get_speed()); 
}

void Robot::update_matchloader() {
    if (m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
        matchloader.toggle(); // toggle Matchloader 
        if (matchloader.get_state()) {
            matchloader.set_voltage( constants::HIGH_VOLTAGE_CATA); 
        }

        if (!matchloader.get_state()) {
            matchloader.set_voltage( 0); 
        }

    }
    
}


// updates all aspects of wings 
void Robot::update_pneumatics() {
    // if L1 is pressed 
    if (m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
        wings.toggle_front_left();
        // wings.toggle_front_right();
        wings.toggle_back_wings(); 

        // front left
    }  
    // if L2 is pressed 
    if (m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
        wings.toggle_front_right(); 
    }
    // hang = X
    if (m_controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) {
        wings.toggle_hang();    
    }
}

// void Robot::update_climb(){
//     if(m_controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)){
//         climb.toggle();
//         climb.set_speed(constants::HIGH_VOLTAGE_CATA);
//     }
//     else if(m_controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)){
//         climb.toggle();
//         climb.set_speed(constants::HIGH_VOLTAGE_CATA);
//     }

// }

// updates all components 
void Robot::update(std::string info) {
    update_intake();
    // update_matchloader(); 
    update_pneumatics();
    update_drivetrain(); 
    update_climb();

    
    // printf("motor: %s", dt.get_left_motor_group());
    // master.print(0,0, "loader temp: %f", dt.get_left_motor_group() );
    // m_controller.print(0, 0, "arm pos: %d", climb.pot.get_value()); 
}