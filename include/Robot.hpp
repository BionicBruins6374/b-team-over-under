#pragma once
#include "api.h"
#include "Cata.hpp"
#include "Intake.hpp"
#include "Wings.hpp"
#include "constants.hpp"

class Robot {
    private:
        pros::Controller m_controller {pros::E_CONTROLLER_MASTER}; 

        Intake intake; 
        Catapult cata;
        int8_t intake_pressed_count = 0;  // whether or not the intake button is currently being pressed
        // Wings wings;
        
        void update_intake();
        void update_cata(); // L1 toggles matchloader, L2 switches speed 
        void update_wings(); 
    public: 
        void update(std::string info); 
        // Robot(Catapult cata, Intake intake, Wings wings);
        Robot(Intake intake, Catapult cata);
        
};