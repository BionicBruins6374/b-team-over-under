#include "Pneumatics.hpp"


// Constructor 
Pneumatics::Pneumatics(uint8_t port_front_right, uint8_t port_front_left, uint8_t port_back, uint8_t hang_port_L1) :
    front_wing_right {port_front_right},
    front_wing_left {port_front_left},
    back_wing {port_back},
    hang_left_1 {hang_port_L1}
    {};


void Pneumatics::toggle_back_wings() {
    back_wings_state = !back_wings_state; // switches wing state 
    back_wing.set_value(back_wings_state);    
}

void Pneumatics::toggle_front_wings() {
    toggle_front_right(); 
    toggle_front_left();
}

void Pneumatics::toggle_front_right() {
    front_wing_right_state = !front_wing_right_state; // switches wing state 
    front_wing_right.set_value(front_wing_right_state); 
}
    

void Pneumatics::toggle_front_left() {
    front_wing_left_state = !front_wing_left_state; // switches wing state 
    front_wing_left.set_value(front_wing_left_state); 
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

// bool Pneumatics::get_state_front_wings() {
//     return front_wings_state; 
// }