#include "Wings.hpp"


// Constructor 
Wings::Wings(uint8_t port_right, uint8_t port_left): 
    piston_right {port_right},
    piston_left {port_left}
    {};

// Changes piston state to off/on
void Wings::toggle_piston() {
    state = !state;
    piston_right.set_value(state); 
    piston_left.set_value(state);
}

// returns wing state
bool Wings::get_state() {
    return state; 
}


