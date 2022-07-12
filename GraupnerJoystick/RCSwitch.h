#ifndef RCSWITCH_h
#define RCSWITCH_h

#include <Arduino.h>

enum SwitchPosition{
    POS_A,
    POS_B,
    POS_NONE

};

class RCSwitch
{
private:
    uint8_t _posAPin;
    uint8_t _posBPin;
public:
    RCSwitch(uint8_t posAPin,uint8_t posBPin=NULL);
    SwitchPosition getSwitchPosition();
    
};

#endif