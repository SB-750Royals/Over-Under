#include "api.h"
#include "main.h"
#include "driver.h"


// Main Controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// Drive Motors
pros::Motor left_back(20, pros::E_MOTOR_GEAR_600 , false, pros::E_MOTOR_ENCODER_COUNTS); 
pros::Motor left_front(11, pros::E_MOTOR_GEAR_600 , false, pros::E_MOTOR_ENCODER_COUNTS);

pros::Motor right_back(4, pros::E_MOTOR_GEAR_600 , true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor right_front(14, pros::E_MOTOR_GEAR_600 , true, pros::E_MOTOR_ENCODER_COUNTS); 

pros::MotorGroup left_drive({left_back, left_front});
pros::MotorGroup right_drive({right_back, right_front});
