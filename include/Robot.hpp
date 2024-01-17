#pragma once
#include "api.h"
#include "Matchloader.hpp"
#include "Intake.hpp"
#include "Wings.hpp"
#include "constants.hpp"
#include <vector>

class Robot {
    private:
        pros::Controller m_controller {pros::E_CONTROLLER_MASTER}; 

        Intake intake; 
        Matchloader matchloader;
        int8_t intake_pressed_count = 0;  // whether or not the intake button is currently being pressed
        Wings wings;
        bool ram_lock = false;
        
        void update_intake();
        void update_matchloader(); // L1 toggles matchloader, L2 switches speed 
        void update_wings(); 
        void update_drivetrain(); 
        std::vector<double> dampen_turns(int left_velocity, int right_velocity); 
    public: 
        void update(std::string info); 
        Robot(Intake intake, Matchloader matchloader, Wings wingin);
        // Robot(Intake intake, Matchloaderpult Matchloader);
        
};