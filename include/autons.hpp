#pragma once
#include "Robot.hpp"

#include "EZ-Template/drive/drive.hpp"

extern Drive chassis;

void drive_example();
void defensive_x2(); 
void turn_example();
void drive_and_turn();
void wait_until_change_speed();
void swing_example();
void combining_movements();
void interfered_example();

void default_constants();
void one_mogo_constants();
void two_mogo_constants();

void modified_exit_condition(); 

void defensive_raw(); 
void offensive_x2();
void offensive_new(Intake intake, Pneumatics pneumatics); 
void alliance_triball(); 
void skills_ez(Matchloader match, Pneumatics pneumatics); 
void defensive_triball(Intake intake, Pneumatics pneumais);
void defence_auton(Pneumatics wings);
void offensive_x3(Intake intake, Pneumatics wings);
void defensive_triballA(Intake intake, Pneumatics wings);

void skills_triball(Pneumatics wings, Matchloader cata);
void awp_diff(Pneumatics wings, Intake intake); 

void drive_to_angle(double angle);

void offensive_4ball(Pneumatics pneumatics, Intake intake);
void hwanseo_offensive(Intake intake, Pneumatics pneumatics);

void auton_skills(Matchloader cata, Pneumatics wings); 
