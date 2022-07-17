//#include <SPI.h>
//#include <nRF24L01.h>
//#include <RF24.h>
//
//RF24 radio(9, 10);
//int16_t axisValue = 0;
//const byte rxAddr[6] = "TV110";
//
//void setup()
//{
//  radio.begin();
//  radio.openReadingPipe(0, rxAddr);
//  
//  radio.startListening();
//}
//
//void loop()
//{
//
//  if (radio.available())
//  {
//    radio.read(&axisValue, sizeof(axisValue));
//    Serial.print(axisValue);
//    Serial.print(',');
//    radio.read(&axisValue, sizeof(axisValue));
//    Serial.print(axisValue);
//    Serial.print(',');
//    radio.read(&axisValue, sizeof(axisValue));
//    Serial.print(axisValue);
//    Serial.print(',');
//    radio.read(&axisValue, sizeof(axisValue));
//    Serial.println(axisValue);
//  }
//  delay(10);
//}
