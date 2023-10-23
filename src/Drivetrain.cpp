#include "Drivetrain.hpp"
#include "constants.hpp"

static float scale(float const raw)
{
    return std::pow(raw / constants::CONTROLLER_ANALOG_MAX, 3.0f) * constants::DRIVE_MAX_VOLTAGE * constants::DRIVE_DAMPENING;
}

void Drivetrain::update(int32_t forward_backward_axis_int, int32_t left_right_axis_int)
{

    auto forward_backward_axis = static_cast<float>(forward_backward_axis_int);
    auto left_right_axis = static_cast<float>(left_right_axis_int);
	left_right_axis = scale(left_right_axis);
	left_right_axis *= m_drive_turn_sensitivity;


    forward_backward_axis = scale(forward_backward_axis);

    auto const turn_differential = left_right_axis * constants::drive_turn_sensitivity;

    auto const left_voltage = static_cast<int32_t>(forward_backward_axis - turn_differential);
    auto const right_voltage = static_cast<int32_t>(forward_backward_axis + turn_differential);


    m_left_back_motor.move_voltage(left_voltage);
    m_left_front_motor.move_voltage(left_voltage);
    m_left_middle_motor.move_voltage(right_voltage);

    m_right_back_motor.move_voltage(right_voltage);
    m_right_front_motor.move_voltage(right_voltage);
    m_right_middle_motor.move_voltage(left_voltage);
}