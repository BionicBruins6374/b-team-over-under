#include "Wings.hpp"


// Constructor 
Wings::Wings(uint8_t port_right, uint8_t port_left, uint8_t hang_port) : 
    right_wing {port_right},
    left_wing {port_left},
    hang {hang_port}
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

void Wings::toggle_hang() {
    hang_state = !hang_state; 
    hang.set_value(hang_state);
}

// returns wing state
bool Wings::get_state_wings() {
    return wing_state; 
}


bool Wings::get_state_hang() {
    return hang_state; 
}