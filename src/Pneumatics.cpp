#include "Pneumatics.hpp"


// Constructor 
Pneumatics::Pneumatics(uint8_t port_right, uint8_t port_left, uint8_t hang_port_L1) : 
    front_wing {port_right},
    back_wing {port_left},
    hang_left_1 {hang_port_L1}
    {};


void Pneumatics::toggle_back_wings() {
    back_wings_state = !back_wings_state; // switches wing state 
    back_wing.set_value(back_wings_state);    
}

void Pneumatics::toggle_front_wings() {
    front_wings_state = !front_wings_state; // switches wing state 
    front_wing.set_value(front_wings_state); 
    
}

void Pneumatics::toggle_hang() {
    hang_state = !hang_state; // switches hang piston state 
    hang_left_1.set_value(hang_state);
    
}

// returns wing state
bool Pneumatics::get_state_back_wings() {
    return back_wings_state; 
}


bool Pneumatics::get_state_hang() {
    return hang_state; 
}

bool Pneumatics::get_state_front_wings() {
    return front_wings_state; 
}