#include "intake.hpp"

/* constructor 
*/
Intake::Intake(uint8_t port) 
: Intake{ port } 
{}; 

/* sets voltage to the motor based on input 
*/
void Intake::set_voltage(int voltage) {
    int32_t volt; 
    // TODO: change temperature--check motors during testing for ideal temp
    if (intakeMotor.get_temperature() < 50) {
    volt = voltage * polarity;
    }
    else {
        volt = voltage * 0.90 * polarity; // TODO: change scaler amnt
    }
    intakeMotor.move_voltage(volt);
    current_ideal_voltage = volt;
}

/* switches polarity of bot 
*/
void Intake::switch_polarity() {
    polarity *= -1;
}


