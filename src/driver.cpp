#include "main.h"
#include "auton.h"
#include "driver.h"
#include "globals.h"
#include <ostream>
#include <string>
#include <iostream>
#include <cmath>

/*
 * Constants - Can be modified as needed to adjust performance
 */
const int deadZoneValue = 10;

/*
 * Computer Side Variables - Do not modify
 */
bool handBrake = false bool cataOn = false;
bool flapsOut = false;

/**
 * @brief Applies a deadzone to an input value.
 *
 * @param value The input value to apply the deadzone to.
 * @param deadzone The deadzone threshold.
 * @return The input value if it is outside the deadzone, otherwise 0.
 */
int deadzone(int value, int deadzone)
{

    if (abs(value) < deadzone)
    {
        return 0;
    }
    return value;
}

/**
 * Calculates the curve controls for a given input value.
 * Curve Controls Equation: https://www.desmos.com/calculator/yieihantdf
 *
 * @param x The input value.
 * @return The calculated curve controls.
 */
int curve_controls(int x)
{
    return static_cast<int>((1 / 16129.0) * pow(x, 3));
}
// TODO: Modify Turn Curve Controls

/*
 * Drive
 *
 * This function controls the robot's movement using the controller inputs. It modifies the controller inputs using the deadzone method and stores the motor voltages.
 * It also calculates the power and turn values, sets the motor brake mode based on the handbrake state, and displays the power and turn values on the LCD screen.
 *
 */
void drive()
{

    // Modify the controller inputs using the deadzone method and store the motor voltages
    int power = deadzone(-controller.get_analog(ANALOG_LEFT_Y), deadZoneValue);
    int turn = deadzone(-controller.get_analog(ANALOG_RIGHT_X), deadZoneValue);
    int leftVoltage = power + turn;
    int rightVoltage = power - turn;

    // Calculate the power and turn values  using the curve controls method
    int powerCurve = curve_controls(power);
    int turnCurve = curve_controls(turn);
    int leftVoltageCurve = powerCurve + turnCurve;
    int rightVoltageCurve = powerCurve - turnCurve;

    // Set the motor voltages to the calculated values
    right_drive.move(-rightVoltageCurve);
    left_drive.move(-leftVoltageCurve);
}

/*
 * Initializes the motors and sets their modes and default positions.
 *
 * Motor Modes:
 * - right_back, right_front, left_back, left_front, cata: pros::E_MOTOR_BRAKE_COAST
 */
void start()
{

    right_back.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    right_front.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    left_back.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    left_front.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}

/*
 * Controls the lift mechanism based on the input from the controller.
 * If the up button is pressed, the lift moves up at full speed (127).
 * If the down button is pressed, the lift moves down at full speed (-127).
 * If no button is pressed, the lift stops moving (0).
 */
void lift()
{

    if (controller.get_digital(DIGITAL_UP){
        lift.move(127);
    }
    else if (controller.get_digital(DIGITAL_DOWN){
        lift.move(-127);
    }
    else{
        lift.move(0);
    }
}

/*
 * Controls the side roller mechanism based on the input from the controller.
 * If the right button is pressed, the side roller moves inwards at full speed (127).
 * If the left button is pressed, the side roller moves outwards at full speed (-127).
 * If no button is pressed, the side roller stops moving (0).
 */
void top_roller()
{

    if (controller.get_digital(DIGITAL_L1){
        top_roller.move_velocity(200);
    }
    else if (controller.get_digital(DIGITAL_L2){
        top_roller.move_velocity(-200);
    }
    else{
        top_roller.move(0);
    }
}

/*
 * Controls the catapult mechanism based on the input from the controller.
 * If the right button is pressed, the catapult moves inwards at full speed (127).
 * If the left button is pressed, the catapult moves outwards at full speed (-127).
 * If no button is pressed, the catapult stops moving (0).
 */
void catapult()
{

    if (controller.get_digital(DIGITAL_R1){
        cataOn = true;
    }
    else if (controller.get_digital(DIGITAL_R2){
        cataOn = false;
    }

    if (cataOn){
        cata.move_velocity(200);
    }
    else{
        cata.move_velocity(0);
    }
}

/*
 * Controls the flaps mechanism based on the input from the controller.
 * If the X button is pressed, the flaps move outwards at full speed (200).
 * If no button is pressed, the flaps stop moving (0).
 */
void flaps()
{

    if (controller.get_digital(DIGITAL_X){
        flapsOut = !flapsOut;
    }

    if (flapsOut){
        flaps.move_velocity(200);
    }
    else{
        flaps.move_velocity(0);
    }
}
