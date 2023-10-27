#include "Flywheel.hpp"

// changes the speed and power state of Flywheel according to the button press 
void Flywheel::speed_change(Speed buttonPressed) {
    // if the flywheel is off or the flywheel speed button different 
    //    from the current speed button is pressed (trying to change the speed)
    if (!powerState || (powerState && buttonPressed!= speed)) {
        powerState = true; 
        speed = buttonPressed;
        m_left.move_voltage(speed  * polarity);
    }
    else {
            powerState = false;
            speed = high; // resets speed to default value, TODO: should I do this or make it = to 0
            m_left.move_voltage(0);
    }
}

void Flywheel::change_direction() {
    polarity *= -1; 
}

void Flywheel::set_voltage(int16_t voltage) {
    m_left.move_voltage(voltage);
}