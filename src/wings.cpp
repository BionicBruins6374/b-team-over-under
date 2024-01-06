#include "Wings.hpp"


Wings::Wings(int8_t port): 
    piston {port}
    {};

void Wings::toggle_piston() {
    state = !state;
    piston.set_value(state); 
}


