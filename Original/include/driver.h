#include "main.h"

// Variables
extern const int deadZoneValue;
extern const double drivePowerLimit;

// Methods 
int deadzone(int value, int deadzone);
int curve_controls(int value);

// Subsystems
void start();
void drive();
void lift();
void catapult();
void flaps();
void top_roller();