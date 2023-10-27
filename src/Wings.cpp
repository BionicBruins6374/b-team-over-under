#include "Wings.hpp"

Wings::Wings(int8_t pistonPort):
    piston (pistonPort){ 
    }

void Wings::pistonOut(){
    wingOut = !wingOut;
    piston.set_value(wingOut);
};
