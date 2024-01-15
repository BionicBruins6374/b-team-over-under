#include "Wings.hpp"


// Constructor 
Wings::Wings(uint8_t port_right, uint8_t port_left, uint8_t arm_port): 
    right_wing {port_right},
    left_wing {port_left},
    arms {arm_port}
    {};

// Changes piston state to off/on
// void Wings::toggle_piston() {
    
//     piston_right.set_value(state); 
//     piston_left.set_value(state);
// }


void Wings::toggle_wings() {
    wing_state = !wing_state; 
    right_wing.set_value(wing_state);
    left_wing.set_value(wing_state); 
    
}

void Wings::toggle_arm() {
    arm_state = !arm_state; 
    arms.set_value(arm_state);
}

// returns wing state
bool Wings::get_state_wings() {
    return wing_state; 
}


bool Wings::get_state_arms() {
    return arm_state; 
}