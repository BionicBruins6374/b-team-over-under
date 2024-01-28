#include "Pneumatics.hpp"


// Constructor 
Pneumatics::Pneumatics(uint8_t port_right, uint8_t port_left, uint8_t hang_port) : 
    right_wing {port_right},
    left_wing {port_left},
    hang {hang_port}
    {};


void Pneumatics::toggle_wings() {
    wing_state = !wing_state; // switches wing state 
    right_wing.set_value(wing_state);
    left_wing.set_value(wing_state); 
    
}

void Pneumatics::toggle_hang() {
    hang_state = !hang_state; // switches hang piston state 
    hang.set_value(hang_state);
}

// returns wing state
bool Pneumatics::get_state_wings() {
    return wing_state; 
}


bool Pneumatics::get_state_hang() {
    return hang_state; 
}