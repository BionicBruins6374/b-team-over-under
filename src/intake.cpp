#include "intake.hpp"

/* constructor 
*/
Intake::Intake(uint8_t port) 
: Intake{ port } 
{}; 

/* sets voltage to the motor based on input 
*/
void Intake::set_voltage(int voltage) {
    // TODO: change temperature--check motors during testing for ideal temp
    if (intakeMotor.get_temperature() < 50) {
    intakeMotor.move_voltage(voltage * polarity );
    }
    else {
        intakeMotor.move_voltage(voltage * 0.90 * polarity); // TODO: change scaler amnt
    }
}

/* switches polarity of bot 
*/
void Intake::switch_polarity() {
    polarity *= -1;
}


