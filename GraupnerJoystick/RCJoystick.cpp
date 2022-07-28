#include "RCJoystick.h"

RCJoystick::RCJoystick(uint8_t xPin, uint8_t yPin, uint8_t xTrimPin, uint8_t yTrimPin)
{
    enabledAxes = new RCPotentiometer *[4]{NULL};
    if (xPin != NULL)
        enabledAxes[X] = new RCPotentiometer(xPin);

    if (yPin != NULL)
        enabledAxes[Y] = new RCPotentiometer(yPin);

    if (xTrimPin != NULL)
        enabledAxes[X_TRIM] = new RCPotentiometer(xTrimPin);
    
    if (yTrimPin != NULL)
        enabledAxes[Y_TRIM] = new RCPotentiometer(yTrimPin);
    
}

void RCJoystick::setAxisInput(JoystickAxis axis, uint16_t min, uint16_t max)
{
    if(enabledAxes[axis]!=NULL)
        enabledAxes[axis]->setInputInterval(min,max);
}

void RCJoystick::setAxisOutput(JoystickAxis axis, int16_t min, int16_t max)
{
    if(enabledAxes[axis]!=NULL)
        enabledAxes[axis]->setOutputInterval(min,max);
}

int16_t RCJoystick::getAxis(JoystickAxis axis)
{
    if(enabledAxes[axis]!=NULL)
        return enabledAxes[axis]->getNormalized();
    return 0;
}

int16_t RCJoystick::getAxisRaw(JoystickAxis axis)
{
    if(enabledAxes[axis]!=NULL)
        return enabledAxes[axis]->getRaw();
    return 0;
}