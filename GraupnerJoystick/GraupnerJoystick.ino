#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "RCJoystick.h"
#define LED_PIN 3
#define BUTTON_PIN 2
#define X_PIN A3
#define Y_PIN A2
#define X_TRIM_PIN A1
#define Y_TRIM_PIN A0

RF24 radio(9,  10);
RCJoystick joystick(X_PIN, Y_PIN, X_TRIM_PIN, Y_TRIM_PIN);


const byte rxAddr[6] = "00001";
const byte rxAddr2[6] = "TV110";

void setup()
{
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);
    radio.begin();
    radio.setRetries(15, 15);
    radio.openWritingPipe(rxAddr2);
    radio.stopListening();
    joystick.setAxisOutput(JoystickAxis::X, 0, 180);
    joystick.setAxisOutput(JoystickAxis::Y, 0, 180);
    joystick.setAxisOutput(JoystickAxis::X_TRIM, 0, 180);
    joystick.setAxisOutput(JoystickAxis::Y_TRIM, 0, 180);
}

void loop()
{
    int16_t axisValue = joystick.getAxis(JoystickAxis::X);
    radio.write(&axisValue, sizeof(axisValue));
    axisValue = joystick.getAxis(JoystickAxis::Y);
    radio.write(&axisValue, sizeof(axisValue));
    axisValue = joystick.getAxis(JoystickAxis::X_TRIM);
    radio.write(&axisValue, sizeof(axisValue));
    axisValue = joystick.getAxis(JoystickAxis::Y_TRIM);
    radio.write(&axisValue, sizeof(axisValue));
    delay(10);
}
