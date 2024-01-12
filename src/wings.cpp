#include "Wings.hpp"


// Constructor 
Wings::Wings(uint8_t port): 
    piston {port}
    {}

// Changes piston state to off/on
void Wings::toggle_piston() {
    state = !state;
    piston.set_value(state); 
}

// returns wing state
bool Wings::get_state() {
    return state; 
}


