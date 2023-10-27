#include "Flywheel.hpp"

// TODO: only allows speed change if motor is on; change behavior?
// other options include: turning off flywheel sets speed back to high by default, but pressing the speed change 
//   button would turn on the flywheel with the low speed
void Flywheel::speed_change() {
    if (powerState) {
        switch (speed)
        {
        case high:
            speed = low;
            break;
        case low: 
            speed = high;
            break;
        }
    }
    m_left.move_voltage(speed  * polarity);
}

void Flywheel::speed_change(Speed buttonPressed) {
    if (!powerState) {
        powerState = true; 
        speed = buttonPressed;
    }
    else {
        if (buttonPressed == speed) {
            powerState = false;
            speed = high;
        }
        else {
            speed = buttonPressed; 
        }
    }

}

void Flywheel::toggle() {
    
}

void Flywheel::change_direction() {

}
