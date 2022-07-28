#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <math.h>

#define DEBUG
#ifdef DEBUG
#include <printf.h>
#endif

#include "RCJoystick.h"
#define LED_PIN 3
#define BUTTON_PIN 2
#define X_PIN A2
#define Y_PIN A3
#define X_TRIM_PIN A1
#define Y_TRIM_PIN A0

RF24 radio(9, 10);
RCJoystick joystick(X_PIN, Y_PIN, X_TRIM_PIN, Y_TRIM_PIN);
const byte rxAddr[6] = "TV110";
char message[25];
char x[6], y[6], xTrim[6], yTrim[6];

uint16_t xValue, yValue, xTrimValue, yTrimValue, middleAxisValue = 38;

void setup()
{
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);
    radio.begin();
    radio.setRetries(15, 15);
    radio.openWritingPipe(rxAddr);
    radio.stopListening();

#ifdef DEBUG
    Serial.begin(9600);
    printf_begin();
    radio.printDetails();
#endif
}

void loop()
{
    xValue = joystick.getAxisRaw(JoystickAxis::X);
    yValue = joystick.getAxisRaw(JoystickAxis::Y);
    xTrimValue = joystick.getAxisRaw(JoystickAxis::X_TRIM);
    yTrimValue = joystick.getAxisRaw(JoystickAxis::Y_TRIM);

#ifdef DEBUG
    Serial.print(xValue);
    Serial.print(',');
    Serial.print(yValue);
    Serial.print(',');
    Serial.print(xTrimValue);
    Serial.print(',');
    Serial.println(yTrimValue);
#endif
    itoa(xValue, x, 10);
    itoa(yValue, y, 10);
    itoa(xTrimValue, xTrim, 10);
    itoa(yTrimValue, yTrim, 10);
    strcpy(message, x);
    strcat(message, ",");
    strcat(message, y);
    strcat(message, ",");
    strcat(message, xTrim);
    strcat(message, ",");
    strcat(message, yTrim);
    strcat(message, ",");
    radio.write(&message, sizeof(message));
    delay(10);
}
