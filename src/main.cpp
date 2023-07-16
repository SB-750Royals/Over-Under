#include "api.h"
#include "globals.h"
#include "main.h"
#include "driver.h"

// LCD Code
void initialize(){
 
	pros::lcd::initialize();
	pros::lcd::set_text(0, " 750Royals VignESH ");
	pros::lcd::set_text(1, " Vignesh, Esha, Tejas, Abhaya ");
    pros::lcd::set_text(2, " Anika, Rakshna ");
	pros::lcd::set_text(3, " Arjun, Yegna, Vivek, Vihaan ");
	pros::lcd::set_text(4, "  Hari, Nick , Anushree  ");

	start();
	
}


/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When 
 * the robot is enabled, this task will exit.
 */
void disabled() {

	// Clear all lines of the LCD
	pros::lcd::clear_line(0);
	pros::lcd::clear_line(1);
	pros::lcd::clear_line(2);
	pros::lcd::clear_line(3);
	pros::lcd::clear_line(4);
	pros::lcd::clear_line(5);
	pros::lcd::clear_line(6);
	pros::lcd::clear_line(7); 	

	// Make the screen red and the text color black 
	pros::lcd::set_background_color(255, 0, 0);
	pros::lcd::set_text_color(0, 0, 0);

	// Display Game Over
	pros::lcd::set_text(0, "            750Royals           ");
	pros::lcd::set_text(4, "            Disabled            ");
}

/**
 * Autonomous Control Selection Mode & Pregame Setup
 */
void competition_initialize() {
	start();
}


/*
*  Autonomous Code
*/
void autonomous() {}

/
void opcontrol() {
	start();

	while (true){

		drive();     
		lift();
		pros::delay(20);
	}
}
