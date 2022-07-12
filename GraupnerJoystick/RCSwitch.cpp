#include "RCSwitch.h"

RCSwitch::RCSwitch(uint8_t posAPin, uint8_t posBPin) {
    _posAPin=posAPin;
    _posBPin=posBPin;
    pinMode(posAPin,INPUT_PULLUP);
    if(posBPin!=NULL)
        pinMode(posBPin,INPUT_PULLUP);
    
}

SwitchPosition RCSwitch::getSwitchPosition() {
    
    if(digitalRead(_posAPin)==LOW)
        return POS_A;

    if(_posBPin!=NULL && digitalRead(_posAPin)==LOW)
        return POS_B;

    return POS_NONE;
        
}
