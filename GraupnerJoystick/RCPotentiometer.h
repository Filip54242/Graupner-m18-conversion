#ifndef RCPOTENTIOMETER_h
#define RCPOTENTIOMETER_h

#include <Arduino.h>

#define DEFAULT_INPUT_MAX 1023
#define DEFAULT_INPUT_MIN 0

#define DEFAULT_OUTPUT_MAX 255
#define DEFAULT_OUTPUT_MIN 0

class RCPotentiometer
{
    public:
    RCPotentiometer(uint8_t pin, uint16_t minIn = DEFAULT_INPUT_MIN, uint16_t maxIn = DEFAULT_INPUT_MAX, uint8_t minOut = DEFAULT_OUTPUT_MIN, uint8_t maxOut = DEFAULT_OUTPUT_MAX);
    void setInputInterval(uint16_t min, uint16_t max);
    void setOutputInterval(int16_t min, int16_t max);

    uint16_t getRaw();
    uint8_t getNormalized();

    private:
    uint8_t _pin;
    uint16_t _minIn;
    uint16_t _maxIn;
    int16_t _minOut;
    int16_t _maxOut;
};

#endif