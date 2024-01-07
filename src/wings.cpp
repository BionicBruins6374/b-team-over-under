#include "Wings.hpp"


Wings::Wings(uint8_t port): 
    piston {port}
    {}

void Wings::toggle_piston() {
    state = !state;
    piston.set_value(state); 
}

bool Wings::get_state() {
    return state; 
}


