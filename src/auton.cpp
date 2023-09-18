#include "main.h"
#include "pros/motors.h"
#include "autonmethods.h"


// Constants
const int TIME_TO_EXTEND_LIFT = 1200;  //TODO: Change Delay
const int TIME_TO_MATCH_LOAD = 32 * 1000;  //TODO: Change Delay
const double MOVE_CONSTANT = 4;
const double TURN_CONSTANT = 2.45;
const double PI = 3.1415926;
const double WHEEL_DIAMETER = 3.25;
const double ROTATION = 360.0;
const double BOT_DIAMETER = 9.5;
const double MAX_SPEED = 550.0;
const double MIN_SPEED = 250.0;
const double TURN_MAX = 350.0;
const double TURN_MIN = 100.0;

// Routes
void tuning() {
  move(36.0, 3);
  pros::delay(2000);
  turn(90.0);
}

void programming_skills() {

  // Declarations
  pros::Motor left_lift(13, pros::E_MOTOR_GEAR_100 , false, pros::E_MOTOR_ENCODER_COUNTS);
  pros::Motor right_lift(20, pros::E_MOTOR_GEAR_100 , true, pros::E_MOTOR_ENCODER_COUNTS);
  pros::Motor catapult(14, pros::E_MOTOR_GEAR_100 , true,   pros::E_MOTOR_ENCODER_COUNTS);
  pros::Motor roller(11, pros::E_MOTOR_GEAR_600 , true, pros::E_MOTOR_ENCODER_COUNTS);

  // Hold Motors
  left_lift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  right_lift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  roller.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  // Move top down and cata
  left_lift.move(127);
  right_lift.move(127);

  // Hold positions
  pros::delay(TIME_TO_EXTEND_LIFT);
  left_lift.move(20);
  right_lift.move(20);

  int initialTime = pros::millis();
  // Move Catapult for Match Loading
  while(pros::millis() < TIME_TO_MATCH_LOAD + initialTime) {
     catapult.move(127);
  }

  // Stop Catapult and Lower Lift
  catapult.move(0); 
  right_lift.move(-127);
  left_lift.move(-127);
  pros::delay(TIME_TO_EXTEND_LIFT);

  // Stop Lift
  right_lift.move(0);
  left_lift.move(0);

  // Move away from wall
  move(7.5, 1.5);
  
  // Turn to face the wall
  turn(110);
  
  // Move to the wall
  move(9.0, 1.5);

  // Move away from the wall
  move(-1.5, 1.0);

  // Turn to face the other side
  turn(-110.0);

  // Move to the other side of the field
  move(37.5, 4.0);

   // Turn to face the goal
  turn(-20);

  // Move forward to align with goal
  move(8.0, 1.0);

  // Score Triballs
  move(12.5, 1.5);  

  turn(-40);

  move(10, 1.5);

}

void close_autonomous_1(){


  // Declarations
  pros::Motor left_lift(13, pros::E_MOTOR_GEAR_100 , false, pros::E_MOTOR_ENCODER_COUNTS);
  pros::Motor right_lift(20, pros::E_MOTOR_GEAR_100 , true, pros::E_MOTOR_ENCODER_COUNTS);
  pros::Motor catapult(16, pros::E_MOTOR_GEAR_100 , true,   pros::E_MOTOR_ENCODER_COUNTS);
  pros::Motor roller(11, pros::E_MOTOR_GEAR_600 , true, pros::E_MOTOR_ENCODER_COUNTS);


  move(-12.0);
  turn(-45.0);
  move(-36.0);
  move(24.0);
  turn(45.0);
  move(10.0);
  move(14.0);
  turn(80);

  // Move away from wall
  move(15.0);
  
  turn(-90.0);

  move(24.0);

  move(-2.0);

  turn(80.0);

  move(35.0);

  left_lift.move(127);
  right_lift.move(127);
  pros::delay(TIME_TO_EXTEND_LIFT);
}

void far_autonomous_1(){

  // Delcare Lift/Roller Motors + Piston
  pros::Motor right_lift(13, pros::E_MOTOR_GEAR_600 , true, pros::E_MOTOR_ENCODER_COUNTS);
  pros::Motor left_lift(20, pros::E_MOTOR_GEAR_600 , false, pros::E_MOTOR_ENCODER_COUNTS);
  pros::MotorGroup lift_motors({left_lift, right_lift});
  pros::Motor left_roller(3, pros::E_MOTOR_GEAR_600 , false, pros::E_MOTOR_ENCODER_COUNTS);
  pros::Motor right_roller(8, pros::E_MOTOR_GEAR_600 , true, pros::E_MOTOR_ENCODER_COUNTS);
  pros::MotorGroup roller_motors({left_roller, right_roller});

  // TODO: Code AWP far autonomous here. Use move(), turn(), and above motors

  // Pushes the triball in front of the Alliance goal
  move(35.0);

  // Turns the bot so top down can intake triball
  turn(-88.0);

  // Moves forward to intake triball
  move(-43.0);

  // Intakes triball
  roller_motors.move(127);

  // Turns to face the goal
  move(10.0);
  turn(-140.0);

  // Moves forward toward the goal & releases triball
  move(-28.0);
  roller_motors.move(-127);
  pros::delay(500);
  roller_motors.move(0);

  // Moves back to prepare to align with triball on the barrier
  move(28.0);

  // Turns to face the triball
  turn(70.0);

  // Moves toward the triball and intakes it
  move(-31.0);
  roller_motors.move(127);

  // Moves forward a tiny bit
  turn(-28.0);
  move(-10.0);

  // Turns to face middle triball and pushes i tin
  turn(-100.0);
  move(-30.0);

  // Moves back and turns around so it can use side flaps
  move(-15.0);
  turn(180.0);

  // Pushes triballs into goal with side flaps
  move(20.0);

}
