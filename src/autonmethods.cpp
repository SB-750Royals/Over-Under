#include "main.h"
#include "pros/motors.h"

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

// Auton Functions
void move(double distance, double time)
{
  pros::Motor left_back(1, pros::E_MOTOR_GEAR_600 , false, pros::E_MOTOR_ENCODER_DEGREES); 
  pros::Motor left_front(2, pros::E_MOTOR_GEAR_600 , false, pros::E_MOTOR_ENCODER_DEGREES);
  pros::Motor right_back(9, pros::E_MOTOR_GEAR_600 , true, pros::E_MOTOR_ENCODER_DEGREES);
  pros::Motor right_front(16, pros::E_MOTOR_GEAR_600 , true, pros::E_MOTOR_ENCODER_DEGREES); 

  left_back.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  left_front.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  right_back.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  right_front.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  pros::MotorGroup left_drive({left_back, left_front});
  pros::MotorGroup right_drive({right_back, right_front});
  int target = ROTATION * (distance / (PI * WHEEL_DIAMETER)) * MOVE_CONSTANT;
  left_front.tare_position();
  right_front.tare_position();
  left_back.tare_position();
  right_back.tare_position();
  
  time *= 1000;
  time += pros::millis();
  if(distance > 0)
  {
    while(left_front.get_position() < target && pros::millis() < time)
    {
      int speed = ((MAX_SPEED - MIN_SPEED) / (target)) * double(target - left_front.get_position()) + MIN_SPEED;
      left_drive.move_velocity(speed);
      right_drive.move_velocity(speed);
      pros::delay(2);
    }
  }
  else
  {
    while(left_front.get_position() > target && pros::millis() < time)
    {
      int speed = -(((MAX_SPEED - MIN_SPEED) / (-target)) * double(-target + left_front.get_position()) + MIN_SPEED);
      left_drive.move_velocity(speed);
      right_drive.move_velocity(speed);
      pros::delay(2);
    }
  }
  left_drive.move_velocity(0);
  right_drive.move_velocity(0);
  pros::delay(100);
}

void move(double distance)
{
  int time = 10000;
  pros::Motor left_back(1, pros::E_MOTOR_GEAR_600 , false, pros::E_MOTOR_ENCODER_DEGREES); 
  pros::Motor left_front(2, pros::E_MOTOR_GEAR_600 , false, pros::E_MOTOR_ENCODER_DEGREES);
  pros::Motor right_back(9, pros::E_MOTOR_GEAR_600 , true, pros::E_MOTOR_ENCODER_DEGREES);
  pros::Motor right_front(16, pros::E_MOTOR_GEAR_600 , true, pros::E_MOTOR_ENCODER_DEGREES); 

  left_back.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  left_front.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  right_back.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  right_front.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  pros::MotorGroup left_drive({left_back, left_front});
  pros::MotorGroup right_drive({right_back, right_front});
  int target = ROTATION * (distance / (PI * WHEEL_DIAMETER)) * MOVE_CONSTANT;
  left_front.tare_position();
  right_front.tare_position();
  left_back.tare_position();
  right_back.tare_position();
  
  time *= 1000;
  time += pros::millis();
  if(distance > 0)
  {
    while(left_front.get_position() < target && pros::millis() < time)
    {
      int speed = ((MAX_SPEED - MIN_SPEED) / (target)) * double(target - left_front.get_position()) + MIN_SPEED;
      left_drive.move_velocity(speed);
      right_drive.move_velocity(speed);
      pros::delay(2);
    }
  }
  else
  {
    while(left_front.get_position() > target && pros::millis() < time)
    {
      int speed = -(((MAX_SPEED - MIN_SPEED) / (-target)) * double(-target + left_front.get_position()) + MIN_SPEED);
      left_drive.move_velocity(speed);
      right_drive.move_velocity(speed);
      pros::delay(2);
    }
  }
  left_drive.move_velocity(0);
  right_drive.move_velocity(0);
  pros::delay(100);
}

void turn(double angle) {
  pros::Motor left_back(1, pros::E_MOTOR_GEAR_600 , false, pros::E_MOTOR_ENCODER_DEGREES); 
  pros::Motor left_front(2, pros::E_MOTOR_GEAR_600 , false, pros::E_MOTOR_ENCODER_DEGREES);
  pros::Motor right_back(9, pros::E_MOTOR_GEAR_600 , true, pros::E_MOTOR_ENCODER_DEGREES);
  pros::Motor right_front(16, pros::E_MOTOR_GEAR_600 , true, pros::E_MOTOR_ENCODER_DEGREES); 

  left_back.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  left_front.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  right_back.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  right_front.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  pros::MotorGroup left_drive({left_back, left_front});
  pros::MotorGroup right_drive({right_back, right_front});


  int target = ROTATION * ((BOT_DIAMETER  * PI * angle / 360) / (PI * WHEEL_DIAMETER)) * TURN_CONSTANT;

  left_front.tare_position();
  right_front.tare_position();
  left_back.tare_position();
  right_back.tare_position();


  if(angle > 0)
  {
    while(left_front.get_position() < target)
    {
      int speed = ((TURN_MAX - TURN_MIN) / (target)) * double(target - left_front.get_position()) + TURN_MIN;
      left_drive.move_velocity(speed);
      right_drive.move_velocity(-speed);
      pros::delay(2);
    }
  }
  else
  {
    while(left_front.get_position() > target)
    {
      int speed = -(((TURN_MAX - TURN_MIN) / (-target)) * double(-target + left_front.get_position()) + TURN_MIN);
      left_drive.move_velocity(speed);
      right_drive.move_velocity(-speed);
      pros::delay(2);
    }
  }
  left_drive.move_velocity(0);
  right_drive.move_velocity(0);
  pros::delay(100);
}
