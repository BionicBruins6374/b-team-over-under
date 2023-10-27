#include "Wings.hpp"

Wings::Wings(uint8_t pistonPort):
    piston (pistonPort){ 
    }

void Wings::pistonOut(){
    wingOut = !wingOut;
    piston.set_value(wingOut);
};
