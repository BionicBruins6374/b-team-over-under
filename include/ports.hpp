#include "api.h"

namespace ports {

    constexpr int8_t LEFT_FRONT_DT = 1;
    constexpr int8_t LEFT_BACK_BOTTOM_DT = 2;
    constexpr int8_t LEFT_BACK_TOP_DT = -4
    ; // needs to be fixed 

    constexpr int8_t RIGHT_FRONT_DT = -8;
    constexpr int8_t RIGHT_BACK_BOTTOM_DT = -9;
    constexpr int8_t RIGHT_BACK_TOP_DT = 10;

    constexpr int8_t INTAKE_MOTOR = 6; 
    constexpr int8_t BIG_CATAPULT_MOTOR = 21;
    constexpr int8_t SMALL_CATAPULT_MOTOR = 5;

    constexpr uint8_t WING_PORT_RIGHT = 'G'; 
    constexpr uint8_t WING_PORT_LEFT = 'H'; 
    constexpr uint8_t ARM_PORT = 'D';
};

