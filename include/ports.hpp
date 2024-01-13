#include "api.h"

namespace ports {

    constexpr int8_t LEFT_FRONT_DT = 4;
    constexpr int8_t LEFT_BACK_BOTTOM_DT = 5;
    constexpr int8_t LEFT_BACK_TOP_DT = -6;

    constexpr int8_t RIGHT_FRONT_DT = -1;
    constexpr int8_t RIGHT_BACK_BOTTOM_DT = -2;
    constexpr int8_t RIGHT_BACK_TOP_DT = 3;

    constexpr int8_t INTAKE_MOTOR = 7; 
    constexpr int8_t BIG_CATAPULT_MOTOR = 8;
    constexpr uint8_t WING_PORT_RIGHT = 'G'; 
    constexpr uint8_t WING_PORT_LEFT = 'H'; 
    constexpr uint8_t ARM_PORT = 'D';
};