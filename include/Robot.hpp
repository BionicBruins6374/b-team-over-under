#pragma once
#include "api.h"
#include "Matchloader.hpp"
#include "Intake.hpp"
#include "Pneumatics.hpp"
#include "constants.hpp"
#include "Drivetrain.hpp"
#include <vector>

class Robot {
    private:
        pros::Controller m_controller {pros::E_CONTROLLER_MASTER}; 
        // Robot components 
        Intake intake; 
        Matchloader matchloader;
        Pneumatics wings;
        Drivetrain dt; 

        // drivetrain state trackers
        bool ram_lock = false;
        // "lost" as in a motor was lost 
        bool right_lost = false;
        bool left_lost = false; 
        double dampen_mag = 0.8; 


        // Update component functions 
        void update_intake();
        void update_matchloader(); // L1 toggles matchloader, L2 switches speed 
        void update_matchloader_temp(); 
        void update_wings(); 
        void update_drivetrain(); 

        // dampen turns function 
        std::vector<double> dampen_turns(int left_velocity, int right_velocity); 
    public: 

        // overall update function 
        void update(std::string info); 

        // constructor 
        Robot(Drivetrain drive, Intake intake, Matchloader matchloader, Pneumatics wingin);        
};