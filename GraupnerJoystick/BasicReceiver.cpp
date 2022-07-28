#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

#define DEBUG
#ifdef DEBUG
#include <printf.h>
#endif

#define SERVO_PIN 6
#define ESC_PIN 5
Servo servo;
Servo esc;
RF24 radio(9, 10);
int16_t xValue = 0;
int16_t yValue = 0;

int16_t xTrimValue = 0;
int16_t yTrimValue = 0;

int16_t lastXValue = 0;
int16_t lastYValue = 0;

int16_t lastXTrimValue = 0;
int16_t lastYTrimValue = 0;

const int16_t servoInitial = 40;
const int16_t escOff = 90;
const int16_t valueFilterTreshold = 1;

const byte rxAddr[6] = "TV110";
char message[30];

void setup()
{
    esc.attach(ESC_PIN, 1000, 2000);
    servo.attach(SERVO_PIN);
    radio.begin();
    radio.openReadingPipe(0, rxAddr);
    radio.startListening();
#ifdef DEBUG
    Serial.begin(9600);
    printf_begin();
    radio.printDetails();
#endif
}
void filterValues()
{
    if (abs(lastXValue - xValue) > valueFilterTreshold)
        lastXValue = xValue;
    else
        xValue = lastXValue;

    if (xValue > escOff - 10 && xValue < escOff + 10)
        xValue = escOff;

    if (abs(lastYValue - yValue) > valueFilterTreshold)
        lastYValue = yValue;
    else
        yValue = lastYValue;

    if (abs(lastXTrimValue - xTrimValue) > valueFilterTreshold)
        lastXTrimValue = xTrimValue;
    else
        xTrimValue = lastXTrimValue;

    if (xTrimValue<0)
        xTrimValue=0;

    if (abs(lastYTrimValue - yTrimValue) > valueFilterTreshold)
        lastYTrimValue = yTrimValue;
    else
        yTrimValue = lastYTrimValue;

    yValue += yTrimValue;
    if (xValue > escOff)
    {
        if (xValue > 180 - xTrimValue)
            xValue = 180 - xTrimValue;
    }

    if (xValue < escOff)
    {
        if (xValue < xTrimValue)
            xValue = xTrimValue;
    }

    if (xValue > 179)
        xValue = 179;

    if (xValue < 0)
        xValue = 0;
}
void processMessage(char *data)
{
    char *d = strtok(data, ",");
    xValue = atoi(d);
    d = strtok(NULL, ",");
    yValue = atoi(d);
    d = strtok(NULL, ",");
    xTrimValue = atoi(d);
    d = strtok(NULL, ",");
    yTrimValue = atoi(d);

    xValue = map(xValue, 140, 860, 0, 180);
    yValue = map(yValue, 0, 1023, 20, 60);
    xTrimValue = map(xTrimValue, 650, 1023, 0, 45);
    yTrimValue = map(yTrimValue, 0, 1023, -20, 20);
}

void loop()
{

    if (radio.available())
    {

        radio.read(&message, sizeof(message));
        processMessage(message);
        filterValues();
        servo.write(yValue);
        esc.write(xValue);

#ifdef DEBUG

        Serial.print(xValue);
        Serial.print(',');
        Serial.print(yValue);
        Serial.print(',');
        Serial.print(xTrimValue);
        Serial.print(',');
        Serial.println(yTrimValue);
#endif
    }
    else
    {

        servo.write(servoInitial);
        esc.write(0);
    }
    delay(10);
}
