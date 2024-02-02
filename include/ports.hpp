#include "api.h"

namespace ports {

    constexpr int8_t LEFT_BACK_DT = 8;
    constexpr int8_t LEFT_FRONT_BOTTOM_DT = 16;
    constexpr int8_t LEFT_FRONT_TOP_DT = -5
    ; // needs to be fixed 

    constexpr int8_t RIGHT_BACK_DT = -7;
    constexpr int8_t RIGHT_FRONT_BOTTOM_DT = -6;
    constexpr int8_t RIGHT_FRONT_TOP_DT = 19;

    constexpr int8_t INTAKE_MOTOR = 6; 
    constexpr int8_t BIG_CATAPULT_MOTOR = 7;
    constexpr int8_t SMALL_CATAPULT_MOTOR = 5;

    constexpr uint8_t WING_PORT_RIGHT = 'G'; 
    constexpr uint8_t WING_PORT_LEFT = 'H'; 
    constexpr uint8_t ARM_PORT = 'D';
};

