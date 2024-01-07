#include "main.h"
#include "pros/motors.h"

// Constants
const int TIME_TO_EXTEND_LIFT = 1200;     // TODO: Change Delay
const int TIME_TO_MATCH_LOAD = 32 * 1000; // TODO: Change Delay
const double MOVE_CONSTANT = 4;
const double TURN_CONSTANT = 2.45;
const double PI = 3.1415926;
const double WHEEL_DIAMETER = 3.25;
const double ROTATION = 360.0;
const double BOT_DIAMETER = 9.5;
const double MAX_SPEED = 550.0;
const double MAX_VELOCITY = 12; // Inches per second
const double MAX_ACCELERATION = 10;
const double MIN_SPEED = 250.0;
const double TURN_MAX = 350.0;
const double TURN_MIN = 100.0;

// Motor Encoder Auton Functions
void move(double distance, double time)
{
  pros::Motor left_back(1, pros::E_MOTOR_GEAR_600, false, pros::E_MOTOR_ENCODER_DEGREES);
  pros::Motor left_front(2, pros::E_MOTOR_GEAR_600, false, pros::E_MOTOR_ENCODER_DEGREES);
  pros::Motor right_back(9, pros::E_MOTOR_GEAR_600, true, pros::E_MOTOR_ENCODER_DEGREES);
  pros::Motor right_front(16, pros::E_MOTOR_GEAR_600, true, pros::E_MOTOR_ENCODER_DEGREES);

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
  if (distance > 0)
  {
    while (left_front.get_position() < target && pros::millis() < time)
    {
      int speed = ((MAX_SPEED - MIN_SPEED) / (target)) * double(target - left_front.get_position()) + MIN_SPEED;
      left_drive.move_velocity(speed);
      right_drive.move_velocity(speed);
      pros::delay(2);
    }
  }
  else
  {
    while (left_front.get_position() > target && pros::millis() < time)
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
  pros::Motor left_back(1, pros::E_MOTOR_GEAR_600, false, pros::E_MOTOR_ENCODER_DEGREES);
  pros::Motor left_front(2, pros::E_MOTOR_GEAR_600, false, pros::E_MOTOR_ENCODER_DEGREES);
  pros::Motor right_back(9, pros::E_MOTOR_GEAR_600, true, pros::E_MOTOR_ENCODER_DEGREES);
  pros::Motor right_front(16, pros::E_MOTOR_GEAR_600, true, pros::E_MOTOR_ENCODER_DEGREES);

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
  if (distance > 0)
  {
    while (left_front.get_position() < target && pros::millis() < time)
    {
      int speed = ((MAX_SPEED - MIN_SPEED) / (target)) * double(target - left_front.get_position()) + MIN_SPEED;
      left_drive.move_velocity(speed);
      right_drive.move_velocity(speed);
      pros::delay(2);
    }
  }
  else
  {
    while (left_front.get_position() > target && pros::millis() < time)
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

void turn(double angle)
{
  pros::Motor left_back(1, pros::E_MOTOR_GEAR_600, false, pros::E_MOTOR_ENCODER_DEGREES);
  pros::Motor left_front(2, pros::E_MOTOR_GEAR_600, false, pros::E_MOTOR_ENCODER_DEGREES);
  pros::Motor right_back(9, pros::E_MOTOR_GEAR_600, true, pros::E_MOTOR_ENCODER_DEGREES);
  pros::Motor right_front(16, pros::E_MOTOR_GEAR_600, true, pros::E_MOTOR_ENCODER_DEGREES);

  left_back.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  left_front.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  right_back.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  right_front.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  pros::MotorGroup left_drive({left_back, left_front});
  pros::MotorGroup right_drive({right_back, right_front});

  int target = ROTATION * ((BOT_DIAMETER * PI * angle / 360) / (PI * WHEEL_DIAMETER)) * TURN_CONSTANT;

  left_front.tare_position();
  right_front.tare_position();
  left_back.tare_position();
  right_back.tare_position();

  if (angle > 0)
  {
    while (left_front.get_position() < target)
    {
      int speed = ((TURN_MAX - TURN_MIN) / (target)) * double(target - left_front.get_position()) + TURN_MIN;
      left_drive.move_velocity(speed);
      right_drive.move_velocity(-speed);
      pros::delay(2);
    }
  }
  else
  {
    while (left_front.get_position() > target)
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

// Double Integral Auton
void moveIntegral(double distance)
{

  pros::Motor left_back(1, pros::E_MOTOR_GEAR_600, false, pros::E_MOTOR_ENCODER_DEGREES);
  pros::Motor left_front(2, pros::E_MOTOR_GEAR_600, false, pros::E_MOTOR_ENCODER_DEGREES);
  pros::Motor right_back(9, pros::E_MOTOR_GEAR_600, true, pros::E_MOTOR_ENCODER_DEGREES);
  pros::Motor right_front(16, pros::E_MOTOR_GEAR_600, true, pros::E_MOTOR_ENCODER_DEGREES);

  pros::Imu inertial(3); // Assuming the inertial sensor is connected to port 3, update this accordingly

  double position = 0;
  double velocity = 0;
  double acceleration = 0;

  const double MAX_VELOCITY = 12; // Inches per second
  const double MAX_ACCELERATION = 10;

  const double RAMP_DISTANCE = 12; // Gradual acceleration and deceleration over this distance

  while (position < distance)
  {
    // Get acceleration from the inertial sensor
    acceleration = inertial.get_accel().x;

    // Gradual acceleration and deceleration
    if (position < RAMP_DISTANCE)
    {
      acceleration = std::min(acceleration, MAX_ACCELERATION);
    }
    else if (position > distance - RAMP_DISTANCE)
    {
      acceleration = std::max(acceleration, -MAX_ACCELERATION);
    }

    // Integrate acceleration to get velocity
    velocity += acceleration;

    // Limit velocity to MAX_VELOCITY
    velocity = std::min(velocity, MAX_VELOCITY);

    // Integrate velocity to get position
    position += velocity;

    // Move the motors (adjust as needed for your motor control method)
    left_back.move_velocity(velocity);
    left_front.move_velocity(velocity);
    right_back.move_velocity(velocity);
    right_front.move_velocity(velocity);

    pros::delay(10); // Adjust delay as needed based on your loop speed
  }

  // Stop the motors after reaching the desired distance
  left_back.move_velocity(0);
  left_front.move_velocity(0);
  right_back.move_velocity(0);
  right_front.move_velocity(0);
}

void turnIntegral(double angle)
{

  pros::Motor left_wheel(1, pros::E_MOTOR_GEAR_600, false, pros::E_MOTOR_ENCODER_DEGREES);
  pros::Motor right_wheel(9, pros::E_MOTOR_GEAR_600, true, pros::E_MOTOR_ENCODER_DEGREES);

  pros::Imu inertial(3); // Assuming the inertial sensor is connected to port 3, update this accordingly

  double heading = 0;
  double angular_velocity = 0;
  double angular_acceleration = 0;

  const double MAX_ANGULAR_VELOCITY = 90;     // Degrees per second
  const double MAX_ANGULAR_ACCELERATION = 30; // Degrees per second squared

  const double RAMP_ANGLE = 30; // Gradual acceleration and deceleration over this angle

  while (heading < angle)
  {
    // Get angular acceleration from the inertial sensor
    angular_acceleration = inertial.get_rotation();

    // Gradual acceleration and deceleration
    if (heading < RAMP_ANGLE)
    {
      angular_acceleration = std::min(angular_acceleration, MAX_ANGULAR_ACCELERATION);
    }
    else if (heading > angle - RAMP_ANGLE)
    {
      angular_acceleration = std::max(angular_acceleration, -MAX_ANGULAR_ACCELERATION);
    }

    // Integrate angular acceleration to get angular velocity
    angular_velocity += angular_acceleration;

    // Limit angular velocity to MAX_ANGULAR_VELOCITY
    angular_velocity = std::min(angular_velocity, MAX_ANGULAR_VELOCITY);

    // Integrate angular velocity to get heading
    heading += angular_velocity;

    // Move the motors (adjust as needed for your motor control method)
    left_wheel.move_velocity(-angular_velocity); // Invert for the turning direction
    right_wheel.move_velocity(angular_velocity);

    pros::delay(10); // Adjust delay as needed based on your loop speed
  }

  // Stop the motors after reaching the desired angle
  left_wheel.move_velocity(0);
  right_wheel.move_velocity(0);
}
