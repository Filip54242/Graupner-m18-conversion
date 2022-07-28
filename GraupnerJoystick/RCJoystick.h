#ifndef RCJOYSTICK_h
#define RCJOYSTICK_h

#include <Arduino.h>
#include "RCPotentiometer.h"

#define DEFAULT_MAX_AXIS_INPUT 1023
#define DEFAULT_MIN_AXIS_INPUT 0

#define DEFAULT_MAX_TRIM_INPUT 1023
#define DEFAULT_MIN_TRIM_INPUT 0

#define DEFAULT_MAX_AXIS_OUPTUT 255
#define DEFAULT_MIN_AXIS_OUTPUT 0

#define DEFAULT_MAX_TRIM_OUTPUT 255
#define DEFAULT_MIN_TRIM_OUTPUT 0

enum JoystickAxis
{
    X = 0,
    Y = 1,
    X_TRIM = 2,
    Y_TRIM = 3
};

class RCJoystick
{
public:
    RCJoystick(uint8_t xPin = NULL, uint8_t yPin = NULL, uint8_t xTrimPin = NULL, uint8_t yTrimPin = NULL);
    void setAxisInput(JoystickAxis axis, uint16_t min, uint16_t max);

    void setAxisOutput(JoystickAxis axis, int16_t min, int16_t max);

    int16_t getAxis(JoystickAxis axis);
    int16_t getAxisRaw(JoystickAxis axis);

private:
    RCPotentiometer** enabledAxes;
};

#endif
