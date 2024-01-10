#include "intake.hpp"
#include "constants.hpp"

/* constructor 
*/
Intake::Intake(int8_t port) 
: intakeMotor{ port } 
{}; 

/* sets voltage to the motor based on input and dampens the voltage if motor is at risk of overheating
*/
// void Intake::set_voltage(int8_t voltage) {
//     int32_t volt; 
//     // TODO: change temperature--check motors during testing for ideal temp
//     // temperature in Celsius 
//     if (intakeMotor.get_temperature() < 50) {
//     volt = voltage * polarity;
//     }
//     // dampens voltage supply if motor is near threshold of overheating
//     else {
//         volt = voltage * 0.90 * polarity; // TODO: change scaler amnt
//     }
//     intakeMotor.move_voltage(volt);
//     current_ideal_voltage = volt;
// }

void Intake::set_voltage(int32_t voltage) {
    intakeMotor.move_voltage(voltage);
}

/* switches polarity of bot 
*/
void Intake::switch_polarity() {
    polarity *= -1;
}

void Intake::set_polarity(int polar) {
    polarity = polar;
}

int8_t Intake::get_polarity() {
    return polarity; 
}

/* returns current voltage level of intake--high or low
*/
Intake::level Intake::get_level() {
    return level_state;
}

/* switches voltage level
*/
void Intake::move_level() {
    if (level_state == high) {
        level_state = low;
    }
    else {
        level_state = high;
    }
}

/* returns current toggled status of the bot (1 = on, 0 = off)
*/
int8_t Intake::get_state() {
    return intake_on ? 1 : 0;
}

/* switches state of intake between being on and off 
*/
void Intake::toggle() {
    intake_on = !intake_on;
}

void Intake::toggle(bool state) {
    intake_on = state;
}