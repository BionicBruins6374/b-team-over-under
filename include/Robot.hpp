#include "api.h"
#include "Cata.hpp"
#include "Intake.hpp"
#include "Wings.hpp"
#include "constants.hpp"

class Robot {
    private:
        pros::Controller m_controller {pros::E_CONTROLLER_MASTER}; 

        Intake intake; 
        // Catapult cata;
        // Wings wings;
        
        void update_intake();
        void update_cata(); 
        void update_wings(); 
    public: 
        void update(std::string info); 
        // Robot(Catapult cata, Intake intake, Wings wings);
        Robot(Intake intake);
        
};