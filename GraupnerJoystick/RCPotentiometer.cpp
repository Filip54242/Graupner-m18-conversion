#include "RCPotentiometer.h"


RCPotentiometer::RCPotentiometer(uint8_t pin, uint16_t minIn, uint16_t maxIn, uint8_t minOut, uint8_t maxOut) {
    _pin=pin;
    _minIn=minIn;
    _maxIn=maxIn;
    _minOut=minOut;
    _maxOut=maxOut;

    pinMode(_pin,INPUT);
}

void RCPotentiometer::setInputInterval(uint16_t min, uint16_t max) {
    _minIn=min;
    _maxIn=max;
}

void RCPotentiometer::setOutputInterval(int16_t min, int16_t max) {
     _minOut=min;
    _maxOut=max;
}

uint16_t RCPotentiometer::getRaw() {
    return analogRead(_pin);
}

uint8_t RCPotentiometer::getNormalized() {
    return map(getRaw(),_minIn,_maxIn,_minOut,_maxOut);
}
