
#pragma once
#include "main.h"

namespace constants{
constexpr float CONTROLLER_ANALOG_MAX = 127.0f;  // maximum value for an analog axis on the controller
constexpr float DRIVE_DAMPENING = 0.75f;  // relative dampening for the drivetrain. 0.0..=1.0
constexpr float DRIVE_MAX_VELOCITY = 600.0f;  // fastest drivetrain velocity
constexpr int32_t INTAKE_VELOCITY = 250; // intake motor velocity
constexpr int32_t DRIVE_MAX_VOLTAGE = 12000;
constexpr float drive_turn_sensitivity = 0.9f;

}